// FIXME License notice

#include <algorithm>
#include "game_state.hh"


// Player with smallest ID is alsways attacker
// Apparently pn vs pm means pn will get the smallest ID
GameState::GameState(rules::Players_sptr players)
    : rules::GameState(),
      players_(players),
      nose_player_(0),
      min_value_to_be_taken(0),
      is_finished_(false)
{
  for (size_t i = 0; i < grid_.size(); ++i)
    std::fill(grid_[i].begin(), grid_[i].end(), true);

  unsigned pi = 0;
  for (auto& p: players_->players)
  {
    if (p->type != rules::PLAYER)
      continue;

    p->score = 0;
    player_info_[p->id] = { MUR_INITIAL_STOCK, ATTACKER, POS_INVALID,
                            POS_INVALID, 0, 0, {-1, -1}, {-1, -1}, &p->score };
    p_[pi++] = p->id;
  }

  std::sort(p_.begin(), p_.end());

  player_info_[p_[ATTACKER]].mur_current_role = ATTACKER;
  player_info_[p_[DEFENDER]].mur_current_role = DEFENDER;
}

rules::GameState* GameState::copy() const
{
    return new GameState(*this);
}
