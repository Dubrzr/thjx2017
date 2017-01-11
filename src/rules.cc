#include "rules.hh"
#include "actions.hh"
#include "dumper.hh"

#define PDEBUG_GAME(X) PDEBUG(X " %s", (game == MUR ? "MUR" : "NOSE"))

Rules::Rules(const rules::Options opt)
    : PoolBasedRules(opt), nose_player_(0), sandbox_(opt.time) {
  if (!opt.champion_lib.empty()) {
    champ_dll_ = std::make_unique<utils::DLL>(opt.champion_lib);

    champ_game_init_ = champ_dll_->get<f_champ_game_init>("game_init");
    champ_play_mur_ = champ_dll_->get<f_champ_play_mur>("mur_turn");
    champ_play_nose_ = champ_dll_->get<f_champ_play_nose>("nose_turn");
    champ_game_end_ = champ_dll_->get<f_champ_game_end>("game_end");
  }

  GameState* game_state = new GameState(opt.players);
  api_ = std::make_unique<Api>(game_state, opt.player);
  register_actions();
}

void Rules::register_actions() {
  api_->actions()->register_action(ID_ACTION_PLAY_MUR, []() -> rules::IAction* {
    return new ActionPlayMur();
  });
  api_->actions()->register_action(
      ID_ACTION_PLAY_NOSE,
      []() -> rules::IAction* { return new ActionPlayNose(); });
}

rules::Actions* Rules::get_actions() { return api_->actions(); }

void Rules::apply_action(const rules::IAction_sptr& action) {
  // When receiving an action, the API should have already checked that it
  // is valid. We recheck that for the current gamestate here to avoid weird
  // client/server desynchronizations and make sure the gamestate is always
  // consistent across the clients and the server.

  int err = action->check(api_->game_state());
  if (err)
    FATAL("Synchronization error: received action %d from player %d, but "
          "check() on current gamestate returned %d.",
          action->id(), action->player_id(), err);
  api_->game_state_set(action->apply(api_->game_state()));
}

bool Rules::is_finished() {
  auto state = api_->game_state();
  auto timeout = false;

  for (auto& player : players_->players)
    timeout |= state->get_timed_out(player->id);

  return state->is_finished() || timeout;
}

void Rules::start_of_round() {
  auto state = api_->game_state();
  played_game game = state->get_current_played_game();

  PDEBUG_GAME("Starting");

  if (game == NOSE) {
    for (auto& player : players_->players)
      if (player->id == nose_player_)
        add_player_to_pool(player);

    return;
  }

  state->init_mur_turn();

  for (auto& player : players_->players)
    add_player_to_pool(player);
}

void Rules::at_player_start(rules::ClientMessenger_sptr) {
  sandbox_.execute(champ_game_init_);
}

void Rules::at_player_end(rules::ClientMessenger_sptr) {
  sandbox_.execute(champ_game_end_);
}

// This function will never be called in the case NOSE game and
// non-NOSE player
void Rules::player_turn() {
  auto state = api_->game_state();
  played_game game = state->get_current_played_game();
  PDEBUG_GAME("Starting");

  switch (game) {
  case MUR:
    sandbox_.execute(champ_play_mur_);
    break;
  case NOSE:
    sandbox_.execute(champ_play_nose_);
    break;
  }
}

// Solve the games when both players played
void Rules::end_of_round() {
  if (is_finished())
    return;

  auto state = api_->game_state();
  played_game game = state->get_current_played_game();

  switch (game) {
  case MUR: {

    // if looser is -1 then game state isn't changed
    // so we don't care about the absurd value
    auto looser = state->resolve_mur();
    nose_player_ = static_cast<unsigned>(looser);

    if (looser == -1)
      return;

    state->set_current_played_game(NOSE);
    break;
  }
  case NOSE:
    state->resolve_nose();
    state->set_current_played_game(MUR);
    state->init_mur();
    break;
  }

  PDEBUG_GAME("Resolved");
}

void Rules::end_of_player_turn(unsigned player) {
  auto state = api_->game_state();
  played_game g = state->get_current_played_game();

  if (g == MUR && state->get_mur_used_stock(player) == -1)
    handle_timeout(player);
  else if (g == NOSE && state->get_nose_played_square(player).x == -1)
    handle_timeout(player);
}

void Rules::dump_state(std::ostream& out) {
  SDEBUG("Dumping state!");
  dump_game_state(out, *api_->game_state());
}

void Rules::handle_timeout(uint32_t player) {
  PDEBUG("Timeout for player %d", player);
  api_->game_state()->set_timed_out(player);
}
