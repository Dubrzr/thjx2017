// FIXME License notice

#ifndef GAME_STATE_HH
#define GAME_STATE_HH

#include <array>
#include <memory>
#include <unordered_map>

#include <rules/game-state.hh>
#include <rules/player.hh>

#include "constant.hh"

class ActionTest;

using nose_grid = std::array<std::array<bool, NOSE_XMAX>, NOSE_YMAX>;

enum played_game {
  MUR,
  NOSE,
  END,
};

struct player_info {

  // MUR specific
  int mur_stock;
  mur_role mur_current_role;

  mur_position mur_pos;
  mur_position mur_last_pos;

  int mur_used_stock;
  int mur_last_used_stock;

  // NOSE specific
  nose_position nose_played_square;
  nose_position nose_last_played_square;

  int* score;
  bool timed_out;
};

int squares_left(const nose_grid& g);
int squares_taken(const nose_grid& g, const nose_position& p);
void fill_grid(nose_grid& grid, const nose_position& p);

std::pair<int, int> mur_compute_stock_loss_(mur_position attacker_pos,
                                            mur_position defender_pos,
                                            int attacker_stock,
                                            int defender_stock);

class GameState : public rules::GameState {
public:
  // Note: when initializing a gamestate, player 1 is given the DEFENDER MUR
  // role while player 2 is given the ATTACKER MUR role
  GameState(rules::Players_sptr players);
  virtual rules::GameState* copy() const;

  played_game get_current_played_game() const { return current_played_game_; }
  void set_current_played_game(played_game g) { current_played_game_ = g; }

  const rules::Players_sptr& get_players() const { return players_; }

  unsigned opponent(unsigned player) const {
    return (p_[0] == player) ? p_[1] : p_[0];
  }

  int get_score(unsigned player) const {
    return *player_info_.at(player).score;
  }

  // MUR
  int get_mur_stock(unsigned player) const {
    return player_info_.at(player).mur_stock;
  }

  mur_role get_mur_role(unsigned player) const {
    return player_info_.at(player).mur_current_role;
  }

  void set_mur_role(unsigned player, mur_role r) {
    player_info_.at(player).mur_current_role = r;
  }

  int get_mur_used_stock(unsigned player) const {
    return player_info_.at(player).mur_used_stock;
  }

  void set_mur_used_stock(unsigned player, unsigned amount) {
    player_info_.at(player).mur_used_stock = amount;
  }

  int get_mur_last_used_stock(unsigned player) const {
    return player_info_.at(player).mur_last_used_stock;
  }

  mur_position get_mur_position(unsigned player) const {
    return player_info_.at(player).mur_pos;
  }

  void set_mur_position(unsigned player, mur_position pos) {
    player_info_.at(player).mur_pos = pos;
  }

  mur_position get_mur_last_position(unsigned player) const {
    return player_info_.at(player).mur_last_pos;
  }

  // NOSE
  nose_position get_nose_last_played_square(unsigned player) const {
    return player_info_.at(player).nose_last_played_square;
  }

  nose_position get_nose_last_played_square() const {
    return nose_last_played_square_;
  }

  nose_position get_nose_played_square(unsigned player) const {
    return player_info_.at(player).nose_played_square;
  }

  void set_nose_played_square(unsigned player, nose_position pos) {
    DEBUG("[SET] (%d, %d) for player %d", pos.x, pos.y, player);
    player_info_.at(player).nose_played_square = pos;
  }

  unsigned get_nose_player_id() const { return nose_player_; }

  int get_nose_squares_to_take() const { return nose_squares_to_take_; }

  nose_grid get_nose_grid() const { return grid_; }

  int get_remaining_square() { return squares_left(grid_); }

  // general
  // -------

  bool get_timed_out(unsigned player) const {
    return player_info_.at(player).timed_out;
  }

  void set_timed_out(unsigned player) {
    player_info_.at(player).timed_out = true;
  }

  // called to initialize the MUR and NOSE game
  void init_mur();
  void init_mur_turn();

  int resolve_mur(); // returns -1 or the ID of the player who lost
  void resolve_nose();

  // returns whether the game is over
  bool is_finished() const { return is_finished_; }

  // tests
  friend class ActionTest;

private:
  // Global state
  rules::Players_sptr players_;
  std::array<unsigned, 2> p_;
  played_game current_played_game_; // either MUR or NOSE
  std::unordered_map<unsigned, player_info> player_info_;

  // MUR specific
  int fill_squares();
  int get_mur_loser();

  // NOSE specific
  unsigned nose_player_;
  int nose_squares_to_take_;

  nose_position nose_last_played_square_;
  nose_grid grid_;

  bool is_finished_;
};

#endif /* !GAME_STATE_HH */
