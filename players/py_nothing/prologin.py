# coding: utf-8
# This file has been generated, if you wish to
# modify it in a permanent way, please refer
# to the script file : gen/generator_python.rb

from api import *

# Function called at the start of the game. You can use it to initialize your data structures.
def game_init():
    print('GAME_INIT')
    pass

# Function called during a phase (MUR turn). If you never call the ``play_mur`` function, you will defend or attack a random position with a random portion of your remaining stock.
def mur_turn():
    print('MUR_TURN')
    pass

# Function called when a MUR game is over.
def mur_end():
    print('MUR_END')
    pass

# Function called during the NOSE turn. If you never call the ``play_nose`` function, you will choose a random square from the remaining squares.
def nose_turn():
    print('NOSE_TURN')
    pass

# Function called at the end of the game. You can use it to free your data structures.
def game_end():
    print('GAME_END')
    pass

