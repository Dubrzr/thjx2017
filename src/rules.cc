#include "rules.hh"
#include "actions.hh"

Rules::Rules(const rules::Options opt)
  : TurnBasedRules(opt), sandbox_(opt.time)
{
  if (!opt.champion_lib.empty())
  {
    champion_dll_ = std::make_unique<utils::DLL>(opt.champion_lib);

    champ_game_init_ = champ_dll_->get<f_champ_game_init>("game_init");
    champ_play_mur_ = champ_dll_->get<f_champ_bidding_phase>("play_mur");
    champ_play_nose = champ_dll_->get<f_champ_outbidding_phase>("play_nose");
    champ_game_end_ = champ_dll_->get<f_champ_game_end>("game_end");
  }

  GameState* game_state = new GameState(opt.players);
  api_ = std::make_unique<Api>(game_state, opt.player);
  register_actions();
}

void Rules::register_actions()
{
  api_->actions()->register_action(ID_ACTION_PLAY_MUR, []() -> rules::IAction* {
                                   return new ActionPlayMur(); });
  api_->actions()->register_action(
                                   ID_ACTION_PLAY_NOSE,
                                   []() -> rules::IAction* { return new ActionPlayNose(); }
                                  );
}

rules::Actions* Rules::get_actions()
{
  return api_->actions();
}

void Rules::apply_action(const rules::IAction_sptr& action)
{
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

bool Rules::is_finished()
{
  return api_->game_state()->is_finished();
}

void Rules::player_turn()
{
  played_game game = api_->game_state()->get_current_played_game();
  switch (game)
  {
    case MUR:
      sandbox_.execute(champ_play_mur_);
      break;
    case NOSE:
      sandbox_.execute(champ_play_nose_);
      break;
  }
}

void Rules::at_server_start(rules::ServerMessenger_sptr msgr)
{
  // FIXME
}

void Rules::at_player_start(rules::ClientMessenger_sptr msgr)
{
  // FIXME
}

void Rules::at_player_end(rules::ClientMessenger_sptr)
{
  // FIXME
}

void Rules::start_of_round()
{
  // FIXME
}

void Rules::end_of_round()
{
  // FIXME
}

void Rules::end_of_player_turn(unsigned player_id)
{
  // FIXME
}

void Rules::dump_state(std::ostream& out)
{
  dump_game_state(out, *api_->game_state());
}
