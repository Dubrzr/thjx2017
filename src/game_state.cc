// FIXME License notice

#include <algorithm>
#include "game_state.hh"
#include "action_play_mur.hh"
#include "action_play_nose.hh"
#include "losses.hh"


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

void GameState::init_mur()
{
  for (auto& pi: player_info_)
  {
    pi.second.mur_stock = MUR_INITIAL_STOCK;

    pi.second.mur_last_pos = pi.second.mur_pos;
    pi.second.mur_last_used_stock = pi.second.mur_used_stock;
    pi.second.nose_last_played_square = pi.second.nose_played_square;

    pi.second.mur_used_stock = 0;
    pi.second.mur_pos = POS_INVALID;
    pi.second.nose_played_square = { -1, -1 };
  }
}

int GameState::get_mur_loser()
{
  auto at = player_info_.at(p_[ATTACKER]);
  auto df = player_info_.at(p_[DEFENDER]);

  auto at_mur = at.mur_stock;
  auto df_mur = df.mur_stock;

  if (at_mur <= 0 && df_mur <= 0)
    return -1;

  if (at_mur <= 0)
    return p_[ATTACKER];

  if (at_mur <= 0)
    return p_[DEFENDER];

  return -1;
}

int GameState::resolve_mur()
{
  compute_losses();

  auto& at = player_info_.at(p_[ATTACKER]);
  auto& df = player_info_.at(p_[DEFENDER]);

  auto at_mur = at.mur_stock;
  auto df_mur = df.mur_stock;

  int ret = get_mur_loser();

  if (at_mur <= 0 && df_mur <= 0) {
    is_finished_ = true;

    auto points = squares_left(grid_);
    *at.score -= points;
    *df.score -= points;

    return ret;
  }

  if (ret == -1)
    return ret;

  set_current_played_game(NOSE);
  min_value_to_be_taken = player_info_.at(opponent(ret)).mur_stock;
  nose_player_ = ret;

  return ret;
}

void GameState::resolve_nose()
{
  auto& p = player_info_.at(nose_player_);
  auto pos_played = p.nose_played_square;

  if ((pos_played.x | pos_played.y) == 0)
    is_finished_ = true;
}

void GameState::compute_losses()
{
  auto& at = player_info_.at(p_[ATTACKER]);
  auto& df = player_info_.at(p_[DEFENDER]);

  auto& at_mur = at.mur_used_stock;
  auto& df_mur = df.mur_used_stock;

  kl_pair akl = attacker_losses[at.mur_pos][df.mur_pos];
  kl_pair dkl = defender_losses[at.mur_pos][df.mur_pos];

  auto at_losses = at_mur * akl.k + df_mur * akl.l;
  auto df_losses = at_mur * dkl.k + df_mur * dkl.l;

  std::cout << "Att: " << at_losses << std::endl;
  std::cout << "Def: " << df_losses << std::endl;

  at.mur_stock -= at_losses;
  df.mur_stock -= df_losses;
}

void GameState::auto_mur(unsigned player_id)
{
  auto& p = player_info_[player_id];

  if (p.mur_pos != POS_INVALID && p.mur_used_stock != -1)
    return;

  p.mur_pos = POS_INVALID;
  p.mur_used_stock = -1;

  ActionPlayMur a{POS_N, p.mur_stock, static_cast<int>(player_id)};
  a.check(this);
  a.apply_on(this);
}

void GameState::auto_nose(unsigned player_id)
{
  auto& p = player_info_[player_id];

  if (player_id != nose_player_)
    return;

  if (p.nose_played_square.x != -1 && p.nose_played_square.y != -1)
    return;

  p.nose_last_played_square = { -1, -1 };

  ActionPlayNose a{0, 0, static_cast<int>(player_id)};
  a.check(this);
  a.apply_on(this);
}
