# coding: utf-8
# This file has been generated, if you wish to
# modify it in a permanent way, please refer
# to the script file : gen/generator_python.rb

from api import *
from random import randint

# Function called at the start of the game. You can use it to initialize your data structures.
def game_init():
    print_mur_role(mur_role_of_player(me()))
    pass

# Function called during a phase (MUR turn). If you never call the ``play_mur`` function, you will defend or attack a random position with a random portion of your remaining stock.
def mur_turn():
    s = randint(0, mur_stock(me()))
    pos = mur_position(randint(0, 3))

    print('ID: %s, POS: %s, stock: %s, total: %s' % (me(), pos, s, mur_stock(me())))
    play_mur(pos, s)

# Function called when a MUR game is over.
def mur_end():
    print("MUR END")
    pass

# Function called during the NOSE turn. If you never call the ``play_nose`` function, you will choose a random square from the remaining squares.
def nose_turn():
    print('NOSE for player: %s' % me())
    for y in reversed(range(NOSE_YMAX)):
        for x in reversed(range(NOSE_XMAX)):
            if nose_squares_taken(x, y) >= nose_squares_to_take():
                play_nose(x, y)
                return
    pass

# Function called at the end of the game. You can use it to free your data structures.
def game_end():
    print(mur_stock(me()))
    pass

