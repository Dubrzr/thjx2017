/*
** Stechec project is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** The complete GNU General Public Licence Notice can be found as the
** `NOTICE' file in the root directory.
**
** Copyright (C) 2016 Prologin
*/

#ifndef CONSTANT_HH_
#define CONSTANT_HH_

/// Initial stock given to each player at the start of a MUR game.
#define MUR_INITIAL_STOCK 1024

/// Position a player can defend during a phase
typedef enum mur_position {
  POS_N,       /* <- N */
  POS_O,       /* <- O */
  POS_S,       /* <- S */
  POS_E,       /* <- E */
  POS_INVALID, /* <- Invalid position */
} mur_position;

/// Role played during a MUR game (attacker or defender)
typedef enum mur_role {
  ATTACKER, /* <- Attacker */
  DEFENDER, /* <- Defender */
} mur_role;

/// Errors returned by the actions
typedef enum action_error {
  OK,                  /* <- The action was performed successfully. */
  INVALID_ARGUMENT,    /* <- Invalid argument received. */
  INVALID_NOSE_PLAYER, /* <- Player should not play NOSE. */
  WRONG_GAME,     /* <- This action cannot be performed during this game. */
  LACK_RESOURCES, /* <- You need more resources to perform this action. */
  NOT_ENOUGH_SQUARES_TAKEN, /* <- You need to take more squares. */
  ALREADY_CALLED,           /* <- You cannot call this action multiple times. */
} action_error;

/// Position on the NOSE grid.
typedef struct nose_position {
  int x; /* <- x coordinate (row index) */
  int y; /* <- y coordinate (column index) */
} nose_position;

#endif // !CONSTANT_HH_
