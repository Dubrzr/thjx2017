/// This file has been generated, if you wish to
/// modify it in a permanent way, please refer
/// to the script file : gen/generator_python.rb

#ifndef INTERFACE_HH_
#define INTERFACE_HH_

#include <Python.h>
#include <string>
#include <vector>

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

extern "C" {

/// Attack or Defend a position with a given amount of stock.
action_error api_play_mur(mur_position position, int amount);

/// Remove squares with position >= to the given square.
action_error api_play_nose(int x, int y);

/// Your identifier (not always in {0, 1}).
int api_me();

/// Your opponent's identifier (not always in {0, 1}).
int api_opponent();

/// The current score of the specified player.
int api_score(int player);

/// MUR role (attacker/defender) of the specified player.
mur_role api_mur_role_of_player(int player);

/// Current amount of stock remaining for the specified player.
int api_mur_stock(int player);

/// Amount of stock lost considering both players' moves.
int api_mur_compute_stock_loss(mur_position your_position,
                               mur_position their_position, int your_amount,
                               int their_amount);

/// Last MUR position played by the specified player.
mur_position api_mur_last_pos(int player);

/// Last stock amount used by the specified player.
int api_mur_last_used_stock(int player);

/// Position of the last played square in the NOSE game.
nose_position api_nose_last_played_square();

/// Number of remaining squares in the NOSE game.
int api_nose_remaining_squares();

/// Minimum number of squares to take. Returns -1 if the MUR game of the current
/// turn is not over.
int api_nose_squares_to_take();

/// Affiche le contenu d'une valeur de type mur_position
void api_afficher_mur_position(mur_position v);

/// Affiche le contenu d'une valeur de type mur_role
void api_afficher_mur_role(mur_role v);

/// Affiche le contenu d'une valeur de type action_error
void api_afficher_action_error(action_error v);

/// Affiche le contenu d'une valeur de type nose_position
void api_afficher_nose_position(nose_position v);
}

#endif // !INTERFACE_HH_
