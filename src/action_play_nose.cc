#include "actions.hh"
#include <algorithm>

void fill_grid(nose_grid& grid, nose_position p) {
  for (size_t i = 0; i < grid.size(); ++i)
    for (size_t j = 0; j < grid[i].size(); ++j) {
      if (i >= static_cast<size_t>(p.y) && j >= static_cast<size_t>(p.x))
        grid[i][j] = false;
    }
}

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
  auto& grid = st->get_nose_grid_ref();

  auto taken = squares_taken(grid, {x_, y_});
  st->set_nose_played_square(player_id_, {x_, y_});

  fill_grid(grid, {x_, y_});

  if ((x_ | y_) != 0)
    return;

  auto min = st->get_nose_min_value_to_be_played();
  auto score = st->get_score(player_id_) - (min - taken + 1);

  st->set_score(player_id_, score);
}

int squares_left(nose_grid g) {
  int sum = 0;

  for (size_t i = 0; i < g.size(); ++i)
    sum += std::count(g[i].begin(), g[i].end(), true);

  return sum;
}

int ActionPlayNose::squares_taken(nose_grid g, nose_position p) const {
  auto before = squares_left(g);

  fill_grid(g, p);

  auto after = squares_left(g);

  return before - after;
}
