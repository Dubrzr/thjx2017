#include "pool_based_rules.hh"
#include <chrono>
#include <ctime>

using namespace rules;

PoolBasedRules::PoolBasedRules(const Options opt) : Rules(opt) {
  pool_ = Players_sptr(new Players());
}

void PoolBasedRules::add_player_to_pool(Player_sptr p) {
  if (opt_.player) // not server
    return;

  pool_->players.push_back(p);

  PDEBUG("Adding P%d", p->id);
}

void PoolBasedRules::server_loop(ServerMessenger_sptr msgr) {
  at_start();
  at_server_start(msgr);

  while (!is_finished()) {

    pool_->players.clear();
    start_of_round();

    msgr->push_id(pool_->players.back()->id);

    for (auto& p : pool_->players)
      SDEBUG("On this turn we have P%d", p->id);

    for (auto& p : pool_->players) {
      std::chrono::time_point<std::chrono::system_clock> start, end;
      start = std::chrono::system_clock::now();

      Actions* actions = run_player(msgr, p->id);

      if (!actions) {
        end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        SDEBUG("Handling Timeout after %fs for player %d...",
               elapsed_seconds.count(), p->id);
        handle_timeout(p->id);

        actions = get_actions();
        actions->clear();
      }

      apply_actions(actions, true);
      msgr->push_actions(*actions);

      end_of_player_turn(p->id);
      end_of_turn(p->id);

      if (is_finished())
        goto end;
    }

    SDEBUG("End of round!");

    dump_state_stream();
    end_of_round();
  }

end:
  SDEBUG("Game ended!");
  dump_state_stream();
  at_end();
  at_server_end(msgr);
}

void PoolBasedRules::player_loop(ClientMessenger_sptr msgr) {
  uint32_t last_player_id;
  msgr->pull_id(&last_player_id);

  at_start();
  at_player_start(msgr);
  start_of_round();

  while (!is_finished()) {
    uint32_t playing_id;

    bool me = !msgr->wait_for_turn(opt_.player->id, &playing_id);
    Actions* actions = run_player(msgr, playing_id, me);
    apply_actions(actions, !me);

    end_of_player_turn(playing_id);
    end_of_turn(playing_id);

    if (playing_id == last_player_id) {
      CDEBUG("End of round!");
      end_of_round();

      if (!is_finished()) {
        msgr->pull_id(&last_player_id);
        start_of_round();
      }
    }
  }

  CDEBUG("End of game!");
  at_end();
  at_player_end(msgr);
}

void PoolBasedRules::apply_actions(Actions* actions, bool apply) {
  if (!apply)
    return;

  for (auto action : actions->actions())
    apply_action(action);
}

Actions* PoolBasedRules::run_player(ServerMessenger_sptr msgr, uint32_t id) {
  start_of_player_turn(id);
  start_of_turn(id);

  SDEBUG("Turn for player %d", id);
  msgr->push_id(id);

  Actions* actions = get_actions();
  actions->clear();

  if (!msgr->poll(timeout_))
    return NULL;

  SDEBUG("Getting actions...");
  msgr->recv_actions(actions);
  SDEBUG("Got %u actions", actions->size());

  SDEBUG("Acknowledging...");
  msgr->ack();

  return actions;
}

Actions* PoolBasedRules::run_player(ClientMessenger_sptr msgr, uint32_t id,
                                    bool me) {
  start_of_player_turn(id);
  start_of_turn(id);

  CDEBUG("Turn for player %d", id);

  get_actions()->clear();

  if (me)
    player_turn();

  Actions* actions = get_actions();

  if (me) {
    CDEBUG("Sending %u actions...", actions->size());
    msgr->send_actions(*actions);
    CDEBUG("Waiting for acknowledgement...");
    msgr->wait_for_ack();
  }

  CDEBUG("Getting actions...");
  msgr->pull_actions(actions);

  return actions;
}
