# coding: utf-8
# This file has been generated, if you wish to
# modify it in a permanent way, please refer
# to the script file : gen/generator_python.rb

import random

from api import *

def game_init():
  pass

def mur_turn():
  opponent_id = api_opponent()
  last_opponent_position = api_mur_last_pos(opponent_id)
  if last_opponent_position == mur_position.POS_INVALID:
    position = mur_position[random.randint(0, 3)]
  else:
    position = last_opponent_position
    return position

def mur_end():
  pass

def nose_turn():
  for y in reversed(range(NOSE_YMAX)):
    for x in reversed(range(NOSE_XMAX)):
      if nose_squares_taken(x, y) >= nose_squares_to_take():
        play_nose(x, y)
  play_nose(0, 0)

def game_end():
  pass
