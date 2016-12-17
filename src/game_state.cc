// FIXME License notice

#include "game_state.hh"

GameState::GameState(rules::Players_sptr players)
    : rules::GameState(),
      players_(players)
{
    // FIXME
}

rules::GameState* GameState::copy() const
{
    return new GameState(*this);
}
