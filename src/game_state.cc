#include <algorithm>

#include "action_play_mur.hh"
#include "action_play_nose.hh"
#include "constant.hh"
#include "game_state.hh"
#include "losses.hh"

// Player with smallest ID is alsways attacker
// Apparently pn vs pm means pn will get the smallest ID
GameState::GameState(rules::Players_sptr players)
    : rules::GameState(), players_(players), nose_player_(0),
      nose_squares_to_take_(0), is_finished_(false) {

  current_played_game_ = MUR;

  for (size_t i = 0; i < grid_.size(); ++i)
    std::fill(grid_[i].begin(), grid_[i].end(), true);

  unsigned pi = 0;
  for (auto& p : players_->players) {
    if (p->type != rules::PLAYER)
      continue;

    p->score = 0;
    player_info_[p->id] = {
        MUR_INITIAL_STOCK, ATTACKER, POS_INVALID, POS_INVALID, -1, -1,
        {-1, -1},          {-1, -1}, &p->score,   false};

    p_[pi++] = p->id;
  }

  std::sort(p_.begin(), p_.end());

  player_info_[p_[0]].mur_current_role = ATTACKER;
  player_info_[p_[1]].mur_current_role = DEFENDER;
}

rules::GameState* GameState::copy() const { return new GameState(*this); }

void GameState::init_mur() {
  for (auto& pi : player_info_)
    pi.second.mur_stock = MUR_INITIAL_STOCK;
}

void GameState::init_mur_turn() {
  DEBUG("INIT MUR");
  nose_player_ = 0;
  for (auto& pi : player_info_) {
    pi.second.mur_last_pos = pi.second.mur_pos;
    pi.second.mur_last_used_stock = pi.second.mur_used_stock;
    pi.second.nose_last_played_square = pi.second.nose_played_square;

    pi.second.mur_used_stock = -1;
    pi.second.mur_pos = POS_INVALID;
    pi.second.nose_played_square = {-1, -1};
  }
}

int GameState::get_mur_loser() {
  auto at = get_attacker();
  auto df = get_defender();

  auto at_mur = at.mur_stock;
  auto df_mur = df.mur_stock;

  if (at_mur <= 0 && df_mur <= 0)
    return -1;

  if (at_mur <= 0)
    return get_attacker_id();

  if (df_mur <= 0)
    return get_defender_id();

  return -1;
}

int GameState::resolve_mur() {
  auto& at = get_attacker();
  auto& df = get_defender();

  // compute losses
  int at_loss, df_loss;
  std::tie(at_loss, df_loss) = mur_compute_stock_loss_(
      at.mur_pos, df.mur_pos, at.mur_used_stock, df.mur_used_stock);

  // update stocks
  at.mur_stock -= at_loss;
  df.mur_stock -= df_loss;

  int ret = get_mur_loser();
  DEBUG("[GAMESTATE][RESOLVE] used: (%d, %d), losses: (%d, %d), stocks: (%d, "
        "%d), ret: %d",
        at.mur_used_stock, df.mur_used_stock, at_loss, df_loss, at.mur_stock,
        df.mur_stock, ret);

  if (at.mur_stock <= 0 && df.mur_stock <= 0) {
    is_finished_ = true;

    auto points = squares_left(grid_);
    *at.score -= points;
    *df.score -= points;

    return ret;
  }

  if (ret == -1)
    return ret;

  nose_squares_to_take_ = player_info_.at(opponent(ret)).mur_stock;
  nose_player_ = ret;

  return ret;
}

void GameState::resolve_nose() {
  auto taken = fill_squares();

  auto& p = player_info_.at(nose_player_);
  auto pos_played = p.nose_played_square;

  if ((pos_played.x | pos_played.y) != 0)
    return;

  is_finished_ = true;

  auto score = 0;
  if (taken >= nose_squares_to_take_)
    score = *p.score - taken;
  else
    score = *p.score - (nose_squares_to_take_ - taken + 1);

  *p.score = score;
}

std::pair<int, int> mur_compute_stock_loss_(mur_position ap, mur_position dp,
                                            int k, int l) {
  kl_pair akl = attacker_losses[ap][dp];
  kl_pair dkl = defender_losses[ap][dp];

  auto al = k * akl.k + l * akl.l;
  auto dl = k * dkl.k + l * dkl.l;

  return std::make_pair<int, int>(al, dl);
}

int GameState::fill_squares() {
  auto before = squares_left(grid_);

  fill_grid(grid_, player_info_.at(nose_player_).nose_played_square);

  auto after = squares_left(grid_);

  return before - after;
}
