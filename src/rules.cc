#include "rules.hh"
#include "actions.hh"

Rules::Rules(const rules::Options opt)
  : TurnBasedRules(opt), nose_player_(0), sandbox_(opt.time)
{
  if (!opt.champion_lib.empty())
  {
    champ_dll_ = std::make_unique<utils::DLL>(opt.champion_lib);

    champ_game_init_ = champ_dll_->get<f_champ_game_init>("game_init");
    champ_play_mur_ = champ_dll_->get<f_champ_play_mur>("play_mur");
    champ_play_nose_ = champ_dll_->get<f_champ_play_nose>("play_nose");
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
  api_->actions()->register_action(ID_ACTION_PLAY_NOSE, []() -> rules::IAction* {
                                   return new ActionPlayNose(); });
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
  // Execute the correct game for the correct player
  played_game game = api_->game_state()->get_current_played_game();
  switch (game)
  {
    case MUR:
      sandbox_.execute(champ_play_mur_);
      break;
    case NOSE:
      if (nose_player_ != api_->player()->id)
          return;

      sandbox_.execute(champ_play_nose_);
      break;
  }
}

void Rules::at_player_start(rules::ClientMessenger_sptr msgr)
{
  (void) msgr;
  sandbox_.execute(champ_game_init_);
}

void Rules::at_player_end(rules::ClientMessenger_sptr msgr)
{
  (void) msgr;
  sandbox_.execute(champ_game_end_);
}

void Rules::start_of_round()
{
  // We should not init NOSE since it keeps it's state during the whole game
  played_game game = api_->game_state()->get_current_played_game();
  if (game == MUR)
      api_->game_state()->init_mur();
}

void Rules::end_of_round()
{
  // Solve the games when both players played
  played_game game = api_->game_state()->get_current_played_game();
  switch (game)
  {
    case MUR:
      nose_player_ = api_->game_state()->resolve_mur();
      break;
    case NOSE:
      api_->game_state()->resolve_nose();
      break;
  }
}

void Rules::end_of_player_turn(unsigned player_id)
{
  // Auto play if player did not return a correct action
  played_game game = api_->game_state()->get_current_played_game();
  switch (game)
  {
    case MUR:
      api_->game_state()->auto_mur(player_id);
      break;
    case NOSE:
      api_->game_state()->auto_nose(player_id);
      break;
  }
}

void Rules::dump_state(std::ostream& out)
{
  (void) out;
  // dump_game_state(out, *api_->game_state());
}
