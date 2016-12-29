#ifndef TEST_HELPERS_HH
#define TEST_HELPERS_HH

#include <sstream>

#include <gtest/gtest.h>

#include "../api.hh"
#include "../constant.hh"
#include "../game_state.hh"

static rules::Players_sptr make_test_players(int id1, int id2) {
  return rules::Players_sptr(
    new rules::Players{std::vector<rules::Player_sptr>{
      rules::Player_sptr(new rules::Player(id1, rules::PLAYER)),
      rules::Player_sptr(new rules::Player(id2, rules::PLAYER)),
  }});
}

class ActionTest : public ::testing::Test {
protected:
  virtual void SetUp() {
    utils::Logger::get().level() = utils::Logger::DEBUG_LEVEL;

    auto players_ptr = make_test_players(0, 1);
    st = new GameState(players_ptr);
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
  int& get_nose_squares_to_take() { return st->nose_squares_to_take_; }
};

class ApiTest : public ::testing::Test
{
protected:
  virtual void SetUp()
  {
	// Players values are not 0 and 1, because that would be too simple
	utils::Logger::get().level() = utils::Logger::DEBUG_LEVEL;
	auto players_ptr = make_test_players(PLAYER_ID_1, PLAYER_ID_2);
	st = new GameState(players_ptr);
	players[0].id = PLAYER_ID_1;
	players[0].api = new Api(st, players_ptr->players[0]);
	players[1].id = PLAYER_ID_2;
	players[1].api = new Api(st, players_ptr->players[1]);
  }

  virtual void TearDown()
  {
	delete players[0].api;
	delete players[1].api;
    delete st;
  }

  const int PLAYER_ID_1 = 1337;
  const int PLAYER_ID_2 = 42;

  GameState* st;

  struct Player
  {
	int id;
	Api* api;
  };
  std::array<Player, 2> players;
};

#endif /* !TESTHELPERS_HH_ */
