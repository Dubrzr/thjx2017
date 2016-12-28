#include "../action_play_mur.hh"
#include "../losses.hh"
#include "test-helpers.hh"

// All the tests below are methods coming from the ActionTest class (see
// test-helpers.hh).  This is where the "st" GameState is coming from.

// Test normal action
TEST_F(ActionTest, ActionMUR_continue) {
  get_game_phase() = MUR;

  kl_pair akl = attacker_losses[POS_N][POS_N];
  kl_pair dkl = defender_losses[POS_N][POS_N];

  auto start_res = 100;
  auto mur_res = 10;

  int p1_res = start_res - akl.k * mur_res - akl.l * mur_res;
  int p2_res = start_res - dkl.k * mur_res - dkl.l * mur_res;

  for (int player : {PLAYER_1, PLAYER_2}) {
    get_player_info(player).mur_stock = start_res;

    ActionPlayMur action({POS_N}, mur_res, player);
    EXPECT_EQ(OK, action.check(st));
    action.apply_on(st);
  }

  EXPECT_EQ(-1, st->resolve_mur());
  EXPECT_EQ(p1_res, st->get_mur_stock(PLAYER_1));
  EXPECT_EQ(p2_res, st->get_mur_stock(PLAYER_2));
}

// P1 Looses
TEST_F(ActionTest, ActionMUR_resolve_looser_P1) {
  get_game_phase() = MUR;

  get_player_info(PLAYER_1).mur_stock = 30;
  get_player_info(PLAYER_2).mur_stock = 50;

  ActionPlayMur action1({POS_S}, 30, PLAYER_1);
  ActionPlayMur action2({POS_S}, 30, PLAYER_2);

  EXPECT_EQ(OK, action1.check(st));
  EXPECT_EQ(OK, action2.check(st));
  action1.apply_on(st);
  action2.apply_on(st);

  EXPECT_EQ(static_cast<int>(PLAYER_1), st->resolve_mur());
  EXPECT_EQ(PLAYER_1, st->get_nose_player_id());

  EXPECT_EQ(get_player_info(PLAYER_1).mur_stock, 30 - 8 * (30 + 30));
  EXPECT_EQ(get_player_info(PLAYER_2).mur_stock, 50 - 30);

  EXPECT_EQ(50 - 30, st->get_nose_squares_to_take());
}

// P2 Looses
TEST_F(ActionTest, ActionMUR_resolve_looser_P2) {
  get_game_phase() = MUR;

  get_player_info(PLAYER_1).mur_stock = 50;
  get_player_info(PLAYER_2).mur_stock = 30;

  ActionPlayMur action1({POS_N}, 30, PLAYER_1);
  ActionPlayMur action2({POS_S}, 30, PLAYER_2);

  EXPECT_EQ(OK, action1.check(st));
  EXPECT_EQ(OK, action2.check(st));
  action1.apply_on(st);
  action2.apply_on(st);

  EXPECT_EQ(static_cast<int>(PLAYER_2), st->resolve_mur());
  EXPECT_EQ(PLAYER_2, st->get_nose_player_id());

  EXPECT_EQ(get_player_info(PLAYER_1).mur_stock, 50);
  EXPECT_EQ(get_player_info(PLAYER_2).mur_stock, 30 - 8 * 30);

  EXPECT_EQ(50, st->get_nose_squares_to_take());
}

// Both Loose
TEST_F(ActionTest, ActionMUR_resolve_both_looser) {
  get_game_phase() = MUR;
  get_player_info(PLAYER_1).mur_stock = 30;
  get_player_info(PLAYER_2).mur_stock = 30;

  auto& grid = get_nose_grid();
  for (size_t i = 0; i < grid.size(); ++i)
    std::fill(grid[i].begin(), grid[i].end(), false);

  grid[0][0] = true;
  grid[1][0] = true;
  grid[0][1] = true;

  ActionPlayMur action1({POS_S}, 30, PLAYER_1);
  ActionPlayMur action2({POS_S}, 30, PLAYER_2);

  EXPECT_EQ(OK, action1.check(st));
  EXPECT_EQ(OK, action2.check(st));
  action1.apply_on(st);
  action2.apply_on(st);

  EXPECT_EQ(-1, st->resolve_mur());
  EXPECT_EQ(-3, st->get_score(PLAYER_1));
  EXPECT_EQ(-3, st->get_score(PLAYER_2));
}
