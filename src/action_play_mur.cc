#include "actions.hh"

int ActionPlayMur::check(const GameState* st) const {
  if (st->get_current_played_game() != MUR)
    return WRONG_GAME;

  if (st->get_mur_used_stock(player_id_) > 0)
    return ALREADY_CALLED;

  if (amount_ <= 0)
    return INVALID_ARGUMENT;

  if (position_ >= POS_INVALID || position_ < 0)
    return INVALID_ARGUMENT;

  if (amount_ > st->get_mur_stock(player_id_))
    return LACK_RESOURCES;

  return OK;
}

void ActionPlayMur::apply_on(GameState* st) const {
  DEBUG("[ACTION] Spending %d stock for player %d with stock %d", amount_,
        player_id_, st->get_mur_stock(player_id_));

  st->set_mur_used_stock(player_id_, amount_);
  st->set_mur_position(player_id_, position_);
}
