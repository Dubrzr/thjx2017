#include "actions.hh"
#include <algorithm>

int ActionPlayNose::check(const GameState* st) const {

  if (st->get_current_played_game() != NOSE)
    return WRONG_GAME;

  auto last_move = st->get_nose_played_square(player_id_);
  if (last_move.x != -1 || last_move.y != -1)
    return ALREADY_CALLED;

  if (st->get_nose_player_id() != static_cast<unsigned>(player_id_))
    return INVALID_NOSE_PLAYER;

  if (x_ < 0 || y_ < 0)
    return INVALID_ARGUMENT;

  auto taken = squares_taken(st->get_nose_grid(), {x_, y_});
  auto min = st->get_nose_min_value_to_be_played();

  if (taken < min && ((x_ | y_) != 0))
    return NOT_ENOUGH_SQUARES_TAKEN;

  return OK;
}

void ActionPlayNose::apply_on(GameState* st) const {
  st->set_nose_played_square(player_id_, {x_, y_});
}

int squares_left(const nose_grid& g) {
  int sum = 0;

  for (size_t i = 0; i < g.size(); ++i)
    sum += std::count(g[i].begin(), g[i].end(), true);

  return sum;
}

int squares_taken(const nose_grid& g, const nose_position& p) {
  auto before = squares_left(g);
  nose_grid fill;
  std::copy(g.begin(), g.end(), fill.begin());

  fill_grid(fill, p);

  auto after = squares_left(fill);

  return before - after;
}

void fill_grid(nose_grid& grid, const nose_position& p) {
  for (size_t i = 0; i < grid.size(); ++i)
    for (size_t j = 0; j < grid[i].size(); ++j) {
      if (i >= static_cast<size_t>(p.y) && j >= static_cast<size_t>(p.x))
        grid[i][j] = false;
    }
}
