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

#ifndef API_HH_
#define API_HH_

#include <vector>
#include <rules/game-state.hh>
#include <rules/player.hh>
#include <rules/actions.hh>

#include "game_state.hh"
#include "constant.hh"

/*!
** The methods of this class are exported through 'interface.cc'
** to be called by the clients
*/
class Api
{

public:
    Api(GameState* game_state, rules::Player_sptr player);
    virtual ~Api() { }

    const rules::Player_sptr player() const { return player_; }
    void player_set(rules::Player_sptr player) { player_ = player; }

    rules::Actions* actions() { return &actions_; }

    const GameState* game_state() const { return game_state_; }
    GameState* game_state() { return game_state_; }
    void game_state_set(rules::GameState* gs) {
        game_state_ = dynamic_cast<GameState*>(gs);
    }

private:
    GameState* game_state_;
    rules::Player_sptr player_;
    rules::Actions actions_;

public:

    /// Attack or Defend a position with a given amount of stock.
    action_error play_mur(mur_position position, int amount);

    /// Remove squares with position >= to the given square.
    action_error play_nose(int x, int y);

    /// Your identifier (not always in {0, 1}).
    int me();

    /// Your opponent's identifier (not always in {0, 1}).
    int opponent();

    /// The current score of the specified player.
    int score(int player);

    /// MUR role (attacker/defender) of the specified player.
    mur_role mur_role_of_player(int player);

    /// Current amount of stock remaining for the specified player.
    int mur_stock(int player);

    /// Amount of stock lost considering both players' moves.
    int mur_compute_stock_loss(mur_position your_position, mur_position their_position, int your_amount, int their_amount);

    /// Last MUR position played by the specified player.
    mur_position mur_last_pos(int player);

    /// Last stock amount used by the specified player.
    int mur_last_played_amount(int player);

    /// Position of the last played square in the NOSE game.
    nose_position nose_last_played_square();

    /// Number of remaining squares in the NOSE game.
    int nose_remaining_squares();

    /// Minimum number of squares to take. Returns -1 if the MUR game of the current turn is not over.
    int nose_squares_to_take();

};


#endif /* !API_HH_ */
