/*
** Stechec project is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** The complete GNU General Public Licence Notice can be found as the
** `NOTICE' file in the root directory.
**
** Copyright (C) 2016 Prologin
*/

#include <stdlib.h>

#include "actions.hh"
#include "api.hh"

// global used in interface.cc
Api* api;

Api::Api(GameState* game_state, rules::Player_sptr player)
    : game_state_(game_state), player_(player) {
  api = this;
}

/// Attack or Defend a position with a given amount of stock.
action_error Api::play_mur(mur_position position, int amount) {
  rules::IAction_sptr action(new ActionPlayMur(position, amount, player_->id));

  action_error err;
  if ((err = static_cast<action_error>(action->check(game_state_))) != OK)
    return err;

  actions_.add(action);
  game_state_set(action->apply(game_state_));
  DEBUG("[ME-%d] used stock: %d", me(), game_state()->get_mur_used_stock(me()));
  return OK;
}

/// Remove squares with position >= to the given square.
action_error Api::play_nose(int x, int y) {
  rules::IAction_sptr action(new ActionPlayNose(x, y, player_->id));

  action_error err;
  if ((err = static_cast<action_error>(action->check(game_state_))) != OK)
    return err;

  actions_.add(action);
  game_state_set(action->apply(game_state_));
  return OK;
}

/// Your identifier (not always in {0, 1}).
int Api::me() { return player_->id; }

/// Your opponent's identifier (not always in {0, 1}).
int Api::opponent() { return game_state()->opponent(me()); }

/// The current score of the specified player.
int Api::score(int player) { return game_state()->get_score(player); }

/// MUR role (attacker/defender) of the specified player.
mur_role Api::mur_role_of_player(int player) {
  return game_state()->get_mur_role(player);
}

/// Current amount of stock remaining for the specified player.
int Api::mur_stock(int player) { return game_state()->get_mur_stock(player); }

/// Amount of stock lost considering both players' moves.
mur_losses Api::mur_compute_stock_loss(mur_position attacker,
                                       mur_position defender, int atk_amount,
                                       int dfd_amount) {
  auto losses =
      mur_compute_stock_loss_(attacker, defender, atk_amount, dfd_amount);

  return {losses.first, losses.second};
}

/// Last MUR position played by the specified player.
mur_position Api::mur_last_pos(int player) {
  return game_state()->get_mur_last_position(player);
}

/// Last stock amount used by the specified player.
int Api::mur_last_used_stock(int player) {
  return game_state()->get_mur_last_used_stock(player);
}

/// Position of the last played square in the NOSE game.
nose_position Api::nose_last_played_square() {
  return game_state()->get_nose_last_played_square();
}

/// Number of remaining squares in the NOSE game.
int Api::nose_remaining_squares() {
  return game_state()->get_remaining_square();
}

int Api::nose_squares_taken(int x, int y) {
  return squares_taken(game_state()->get_nose_grid(), {x, y});
}
/// Minimum number of squares to take. Returns -1 if the MUR game of the current
/// turn is not over.
int Api::nose_squares_to_take() {
  return game_state()->get_nose_squares_to_take();
}
