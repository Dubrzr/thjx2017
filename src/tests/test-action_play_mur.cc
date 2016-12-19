#include "../action_play_mur.hh"
#include "test-helpers.hh"

// All the tests below are methods coming from the ActionTest class (see
// test-helpers.hh).  This is where the "st" GameState is coming from.

// Test that we are in the correct game
TEST_F(ActionTest, ActionMUR_correct_game)
{
  get_player_info(PLAYER_1).mur_stock = 30;
  ActionPlayMur action({ POS_N }, 1, PLAYER_1);

  get_game_phase() = NOSE;
  EXPECT_EQ(WRONG_GAME, action.check(st));

  get_game_phase() = MUR;
  EXPECT_EQ(OK, action.check(st));
}

// Test repeat_play
TEST_F(ActionTest, ActionPlayMur_repeat)
{
  get_game_phase() = MUR;

  for (int player : {PLAYER_1, PLAYER_2})
  {
    get_player_info(player).mur_stock = 30;
    ActionPlayMur action({ POS_N }, 25, player);

    EXPECT_EQ(OK, action.check(st));
    action.apply_on(st);
    EXPECT_EQ(ALREADY_CALLED, action.check(st));
  }
}

// Test that amount is positive
TEST_F(ActionTest, ActionMUR_amount_positive)
{
  get_game_phase() = MUR;

  for (int player : {PLAYER_1, PLAYER_2})
  {
    ActionPlayMur action({ POS_N }, -40, player);
    EXPECT_EQ(INVALID_ARGUMENT, action.check(st));
  }
}

// Test that position is valid
TEST_F(ActionTest, ActionMUR_valid_position)
{
  get_game_phase() = MUR;

  for (int player : {PLAYER_1, PLAYER_2})
  {
    ActionPlayMur action({ POS_INVALID }, -40, player);
    EXPECT_EQ(INVALID_ARGUMENT, action.check(st));
  }
}
// Test that player has sufficient resources for the bid
TEST_F(ActionTest, ActionMUR_enough_resources)
{
  for (int player : {PLAYER_1, PLAYER_2})
  {
    get_player_info(player).mur_stock = 30;
    ActionPlayMur action({ POS_N }, 40, player);

    EXPECT_EQ(LACK_RESOURCES, action.check(st));

    get_player_info(player).mur_stock = 50;
    EXPECT_EQ(OK, action.check(st));
  }
}

// Test wrong player
TEST_F(ActionTest, ActionMUR_wrong_player)
{
  get_game_phase() = MUR;

  for (int player : {PLAYER_1, PLAYER_2})
  {
    get_player_info(player).mur_stock = 30;
    ActionPlayMur action({ POS_N }, 25, player);
    EXPECT_EQ(OK, action.check(st));
  }

  for (int player = 2; player < 5; ++player)
  {
    ActionPlayMur action({ POS_N }, 25, player);
    try
    {
      EXPECT_EQ(INVALID_ARGUMENT, action.check(st));
    }
    catch(...)
    {
      // OK
    }
  }
}

