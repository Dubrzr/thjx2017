#include "../action_play_nose.hh"
#include "test-helpers.hh"
#include <algorithm>
#include <iostream>

// All the tests below are methods coming from the ActionTest class (see
// test-helpers.hh).  This is where the "st" GameState is coming from.

// Test cancelled auction
TEST_F(ActionTest, ActionNose_continue)
{
  get_game_phase() = NOSE;
  st->set_nose_player_id(PLAYER_1);
  st->set_score(PLAYER_1, 0);

  auto& g = st->get_nose_grid_ref();
  for (size_t i = 0; i < g.size(); ++i)
    std::fill(g[i].begin(), g[i].end(), false);

  for (size_t i = 0; i < 3; ++i)
    for (size_t j = 0; j < 5; ++j)
      g[i][j] = true;

  ActionPlayNose action(1, 1, PLAYER_1);
  EXPECT_EQ(OK, action.check(st));
  action.apply_on(st);

  st->resolve_nose();
  EXPECT_EQ(7, squares_left(g));
  ASSERT_TRUE(!(st->is_finished()));
}

// Test not cancelled auction
TEST_F(ActionTest, ActionNose_end)
{
  auto min_val = 100;
  get_game_phase() = NOSE;
  st->set_nose_player_id(PLAYER_1);
  get_player_info(PLAYER_2).mur_stock = 1;
  st->set_nose_min_value_to_be_played(min_val);

  st->set_score(PLAYER_1, 0);

  auto& g = st->get_nose_grid_ref();
  for (size_t i = 0; i < g.size(); ++i)
    std::fill(g[i].begin(), g[i].end(), false);

  for (size_t i = 0; i < 3; ++i)
    for (size_t j = 0; j < 5; ++j)
      g[i][j] = true;

  auto left = squares_left(g);
  std::cout << "left: " << left << std::endl;

  ActionPlayNose action(0, 0, PLAYER_1);
  EXPECT_EQ(OK, action.check(st));
  action.apply_on(st);

  st->resolve_nose();
  EXPECT_EQ(-(min_val - left + 1), st->get_score(PLAYER_1));
  EXPECT_EQ(true, st->is_finished());
}
