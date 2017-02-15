# coding: utf-8
# This file has been generated, if you wish to
# modify it in a permanent way, please refer
# to the script file : gen/generator_python.rb

import random
from collections import defaultdict

from api import *

class Stats:

  def __init__(self):
    self.freqs = defaultdict(int)
    self.total = 0

  def update_stats(self, position: mur_position):
    self.freqs[position] += 1
    self.total += 1

  @property
  def most_frequent(self):
    if len(self.freqs) == 0:
      return mur_position(random.randint(0, 3))

    max_pos, max_freq = (None, 0)
    for pos, freq in self.freqs.items():
      if max_pos is None or freq > max_freq:
        max_pos, max_freq = (pos, freq)

    return max_pos

  @property
  def less_frequent(self):
    if len(self.freqs) == 0:
      return mur_position(random.randint(0, 3))

    min_pos, min_freq = (None, 293805809)
    for pos, freq in self.freqs.items():
      if min_pos is None or freq < min_freq:
        min_pos, min_freq = (pos, freq)

    return min_pos

opponent_atk_stats = Stats()
opponent_def_stats = Stats()

def game_init():
  pass

def mur_turn():
  global opponent_atk_stats
  global opponent_def_stats
  my_id = me()
  my_role = mur_role_of_player(my_id)
  my_stock = mur_stock(my_id)

  if my_role == mur_role.ATTACKER:
    play_mur(opponent_def_stats.most_frequent, 1)
  else:
    play_mur(opponent_atk_stats.less_frequent, my_stock)

def mur_end():
  global opponent_atk_stats
  global opponent_def_stats
  op = opponent()
  op_role = mur_role_of_player(op)
  op_last_played_pos = mur_last_pos(op)
  if op_role is mur_role.ATTACKER:
    opponent_atk_stats.update_stats(op_last_played_pos)
  else:
    opponent_def_stats.update_stats(op_last_played_pos)

def nose_turn():
  last_played = nose_last_played_square()

  if nose_remaining_squares() == 1:
    play_nose(2, 0)
  else:
    if last_played.x == 0:
      play_nose(last_played.x, last_played.y - 1)
    elif (
      nose_squares_taken(last_played.x - 1, last_played.y) <
      nose_squares_taken(last_played.x, last_played.y - 1)
    ):
      play_nose(last_played.x - 1, last_played.y)
    else:
      play_nose(last_played.x, last_played.y - 1)

def game_end():
  pass
