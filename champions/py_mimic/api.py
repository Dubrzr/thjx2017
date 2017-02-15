# coding: iso-8859-1
from _api import *

# Initial stock given to each player at the start of a MUR game.
MUR_INITIAL_STOCK = 1024

# Grid XMAX
NOSE_XMAX = 1024

# Grid YMAX
NOSE_YMAX = 3


from enum import IntEnum

# Position a player can defend during a phase
class mur_position(IntEnum):
    POS_N = 0  # <- N
    POS_O = 1  # <- O
    POS_S = 2  # <- S
    POS_E = 3  # <- E
    POS_INVALID = 4  # <- Invalid position


# Role played during a MUR game (attacker or defender)
class mur_role(IntEnum):
    ATTACKER = 0  # <- Attacker
    DEFENDER = 1  # <- Defender


# Errors returned by the actions
class action_error(IntEnum):
    OK = 0  # <- The action was performed successfully.
    INVALID_ARGUMENT = 1  # <- Invalid argument received.
    INVALID_NOSE_PLAYER = 2  # <- Player should not play NOSE.
    WRONG_GAME = 3  # <- This action cannot be performed during this game.
    LACK_RESOURCES = 4  # <- You need more resources to perform this action.
    NOT_ENOUGH_SQUARES_TAKEN = 5  # <- You need to take more squares.
    ALREADY_CALLED = 6  # <- You cannot call this action multiple times.


from collections import namedtuple

# Position on the NOSE grid.

# losses of a game of NOSE for both roles.

