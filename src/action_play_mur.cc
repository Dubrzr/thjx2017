#include "actions.hh"

int ActionPlayMur::check(const GameState* st) const
{
  if(amount_ < 0)
    return INVALID_ARGUMENT;
}

void ActionPlayMur::apply_on(GameState* st) const
{
  // FIXME
}
