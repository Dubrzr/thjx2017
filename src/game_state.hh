// FIXME License notice

#ifndef GAME_STATE_HH
#define GAME_STATE_HH

#include <random>

#include <rules/game-state.hh>
#include <rules/player.hh>

#include "constant.hh"

class ActionTest;

enum played_game
{
  MUR,
  NOSE,
};

struct player_info
{
  // MUR specific
  int mur_remaining_stock;
  mur_role mur_current_role;

  mur_position mur_played_position;
  mur_position mur_last_played_position;

  int mur_used_stock_amount;
  int mur_last_used_stock_amount;

  // NOSE specific
  nose_position nose_last_played_square;

  int *score; // reference to stechec score for convenience
};

class GameState : public rules::GameState
{
public:
  GameState(rules::Players_sptr players);
  virtual rules::GameState* copy() const;

  played_game get_current_played_game() const { return current_played_game_; }

  const rules::Players_sptr& get_players() const { return players_; }

  unsigned opponent(unsigned player) const
  { return (p_[0] == player) ? p_[1] : p_[0]; }

  int get_score(unsigned player) const
  { return *player_info_.at(player).score; }

  // MUR
  int get_mur_remaining_stock(unsigned player) const
  { return player_info_.at(player).mur_remaining_stock; }
  mur_role get_mur_current_role(unsigned player) const
  { return player_info_.at(player).mur_current_role; }
  int get_mur_used_stock_amount(unsigned player) const
  { return player_info_.at(player).mur_used_stock_amount; }
  int get_mur_last_used_stock_amount(unsigned player) const
  { return player_info_.at(player).mur_last_used_stock_amount; }
  mur_position get_mur_played_position(unsigned player) const
  { return player_info_.at(player).mur_played_position; }
  mur_position get_mur_last_played_position(unsigned player) const
  { return player_info_.at(player).mur_last_played_position; }
  unsigned mur_winner() const { /* FIXME */ }

  // NOSE
  nose_position get_nose_last_played_square(unsigned player) const
  { return player_info_.at(player).nose_last_played_square; }

  // general
  // -------
  // called to initialize the MUR game
  void init_mur();
  // called when both players chose (position, stock_amount)
  // returns the id of the winner
  int resolve_mur();
  int resolve_nose();
  // returns whether the game is over
  bool is_finished() const;

  // tests
  friend class ActionTest;

private:
  // Global state
  rules::Players_sptr players_;
  unsigned p_[2];
  played_game current_played_game_; // either MUR or NOSE
  std::unordered_map<unsigned, player_info> player_info_;
  // MUR specific
  unsigned mur_winner_;
  // NOSE specific
  nose_position nose_last_played_square_;

  void set_current_played_game(played_game g) { current_played_game_ = g; }
};

#endif /* !GAME_STATE_HH */
