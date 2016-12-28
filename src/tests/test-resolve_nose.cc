#include "../action_play_nose.hh"
#include "test-helpers.hh"
#include <algorithm>
#include <iostream>

// All the tests below are methods coming from the ActionTest class (see
// test-helpers.hh).  This is where the "st" GameState is coming from.

// Normal Nose turn, not taking the last square
TEST_F(ActionTest, ActionNose_continue) {
  get_game_phase() = NOSE;
  get_nose_player() = PLAYER_1;
  *get_player_info(PLAYER_1).score = 30;

  auto& g = get_nose_grid();
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

// Test nose end forced (by minimum number of square to take)
TEST_F(ActionTest, ActionNose_end_forced) {
  auto min_val = 100;
  get_game_phase() = NOSE;
  get_nose_player() = PLAYER_1;

  get_player_info(PLAYER_2).mur_stock = 1;
  get_nose_squares_to_take() = min_val;
  *get_player_info(PLAYER_1).score = 0;

  auto& g = get_nose_grid();
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

// Test nose end, last square taken willfully
TEST_F(ActionTest, ActionNose_end_willfull) {
  auto min_val = 1;
  get_game_phase() = NOSE;
  get_nose_player() = PLAYER_1;

  get_player_info(PLAYER_2).mur_stock = 1;
  get_nose_squares_to_take() = min_val;
  *get_player_info(PLAYER_1).score = 0;

  auto& g = get_nose_grid();
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
  EXPECT_EQ(-left, st->get_score(PLAYER_1));
  EXPECT_EQ(true, st->is_finished());
}
