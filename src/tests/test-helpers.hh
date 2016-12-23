#ifndef TEST_HELPERS_HH
#define TEST_HELPERS_HH

#include <sstream>

#include <gtest/gtest.h>

#include "../constant.hh"
#include "../game_state.hh"

class ActionTest : public ::testing::Test {
protected:
  virtual void SetUp() {
    utils::Logger::get().level() = utils::Logger::DEBUG_LEVEL;

    /* Create two players (no spectator).  */
    rules::Players_sptr players(
        new rules::Players{std::vector<rules::Player_sptr>{
            rules::Player_sptr(new rules::Player(0, rules::PLAYER)),
            rules::Player_sptr(new rules::Player(1, rules::PLAYER)),
        }});

    st = new GameState(players);
  }

  virtual void TearDown() { delete st; }

  GameState* st;

  const unsigned int PLAYER_1 = 0;
  const unsigned int PLAYER_2 = 1;

  player_info& get_player_info(unsigned player) {
    return st->player_info_.at(player);
  }

  played_game& get_game_phase() { return st->current_played_game_; }
  unsigned& get_nose_player() { return st->nose_player_; }
  nose_grid& get_nose_grid() { return st->grid_; }
  int& get_min_value() { return st->min_value_to_be_taken; }
};

#endif /* !TESTHELPERS_HH_ */
