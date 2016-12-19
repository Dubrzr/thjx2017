#include "../action_play_nose.hh"
#include "test-helpers.hh"

// All the tests below are methods coming from the ActionTest class (see
// test-helpers.hh).  This is where the "st" GameState is coming from.

// Test that we are in the correct game
TEST_F(ActionTest, ActionNOSE_correct_game)
{
  ActionPlayNose action(1, 1, PLAYER_1);

  get_game_phase() = MUR;
  EXPECT_EQ(WRONG_GAME, action.check(st));

  get_game_phase() = NOSE;
  EXPECT_EQ(OK, action.check(st));
}

// Test repeat_play
TEST_F(ActionTest, ActionPlayNose_repeat)
{
  get_game_phase() = NOSE;
  for (int player : {PLAYER_1, PLAYER_2})
  {
    st->set_nose_player_id(player);
    ActionPlayNose action(1, 1, player);

    EXPECT_EQ(OK, action.check(st));
    action.apply_on(st);
    EXPECT_EQ(ALREADY_CALLED, action.check(st));
  }
}

// Test that amount is positive
TEST_F(ActionTest, ActionNOSE_negative_position)
{
  get_game_phase() = NOSE;
  for (int player : {PLAYER_1, PLAYER_2})
  {
    st->set_nose_player_id(player);

    ActionPlayNose actionx(-1, 1, player);
    EXPECT_EQ(INVALID_ARGUMENT, actionx.check(st));

    ActionPlayNose actiony(1, -1, player);
    EXPECT_EQ(INVALID_ARGUMENT, actiony.check(st));

    ActionPlayNose actionxy(-1, -1, player);
    EXPECT_EQ(INVALID_ARGUMENT, actionxy.check(st));
  }
}

// Test invalid player
TEST_F(ActionTest, ActionNOSE_invalid_player)
{
  st->set_nose_player_id(PLAYER_2);
  ActionPlayNose action(1, 1, PLAYER_1);

  EXPECT_EQ(INVALID_NOSE_PLAYER, action.check(st));
}
