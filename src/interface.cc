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

#include "api.hh"

#include <iostream>
#include <sstream>
#include <vector>

// from api.cc
extern Api* api;

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& arr) {
  os << "[";
  typename std::vector<T>::const_iterator it;
  for (it = arr.begin(); it != arr.end(); ++it) {
    if (it != arr.begin())
      os << ", ";
    os << *it;
  }
  os << "]";
  return os;
}

// todo avoir un ostringstream a la place de std::string

std::string convert_to_string(int i) {
  std::ostringstream s;
  s << i;
  std::string result = s.str();
  return result;
}
std::string convert_to_string(double i) {
  std::ostringstream s;
  s << i;
  std::string result = s.str();
  return result;
}
std::string convert_to_string(std::string i) { return i; }
std::string convert_to_string(bool i) { return i ? "true" : "false"; }
std::string convert_to_string(std::vector<int> in) {
  if (in.size()) {
    std::string s = "[" + convert_to_string(in[0]);
    for (int i = 1, l = in.size(); i < l; i++) {
      s = s + ", " + convert_to_string(in[i]);
    }
    return s + "]";
  } else {
    return "[]";
  }
}
std::string convert_to_string(mur_position in) {
  switch (in) {
  case POS_N:
    return "\"pos_n\"";
  case POS_O:
    return "\"pos_o\"";
  case POS_S:
    return "\"pos_s\"";
  case POS_E:
    return "\"pos_e\"";
  case POS_INVALID:
    return "\"pos_invalid\"";
  }
  return "bad value";
}
std::string convert_to_string(std::vector<mur_position> in) {
  if (in.size()) {
    std::string s = "[" + convert_to_string(in[0]);
    for (int i = 1, l = in.size(); i < l; i++) {
      s = s + ", " + convert_to_string(in[i]);
    }
    return s + "]";
  } else {
    return "[]";
  }
}
std::string convert_to_string(mur_role in) {
  switch (in) {
  case ATTACKER:
    return "\"attacker\"";
  case DEFENDER:
    return "\"defender\"";
  }
  return "bad value";
}
std::string convert_to_string(std::vector<mur_role> in) {
  if (in.size()) {
    std::string s = "[" + convert_to_string(in[0]);
    for (int i = 1, l = in.size(); i < l; i++) {
      s = s + ", " + convert_to_string(in[i]);
    }
    return s + "]";
  } else {
    return "[]";
  }
}
std::string convert_to_string(action_error in) {
  switch (in) {
  case OK:
    return "\"ok\"";
  case INVALID_ARGUMENT:
    return "\"invalid_argument\"";
  case INVALID_NOSE_PLAYER:
    return "\"invalid_nose_player\"";
  case WRONG_GAME:
    return "\"wrong_game\"";
  case LACK_RESOURCES:
    return "\"lack_resources\"";
  case NOT_ENOUGH_SQUARES_TAKEN:
    return "\"not_enough_squares_taken\"";
  case ALREADY_CALLED:
    return "\"already_called\"";
  }
  return "bad value";
}
std::string convert_to_string(std::vector<action_error> in) {
  if (in.size()) {
    std::string s = "[" + convert_to_string(in[0]);
    for (int i = 1, l = in.size(); i < l; i++) {
      s = s + ", " + convert_to_string(in[i]);
    }
    return s + "]";
  } else {
    return "[]";
  }
}
std::string convert_to_string(nose_position in) {
  std::string x = convert_to_string(in.x);
  std::string y = convert_to_string(in.y);
  std::string out = "{";
  out += "x:" + x;
  out += ", ";
  out += "y:" + y;
  return out + "}";
}

std::string convert_to_string(std::vector<nose_position> in) {
  if (in.size()) {
    std::string s = "[" + convert_to_string(in[0]);
    for (int i = 1, l = in.size(); i < l; i++) {
      s = s + ", " + convert_to_string(in[i]);
    }
    return s + "]";
  } else {
    return "[]";
  }
}

std::string convert_to_string(mur_losses in){
  std::string defender = convert_to_string(in.defender);
  std::string attacker = convert_to_string(in.attacker);
  std::string out = "{";
  out += "defender:" + defender;
  out += ", ";
  out += "attacker:" + attacker;
  return out + "}";
}

std::string convert_to_string(std::vector<mur_losses> in){
  if (in.size()){
    std::string s = "[" + convert_to_string(in[0]);
    for (int i = 1, l = in.size(); i < l; i++){
      s = s + ", " + convert_to_string(in[i]);
    }
    return s + "]";
  }else{
    return "[]";
  }
}
/// Attack or Defend a position with a given amount of stock.
extern "C" action_error api_play_mur(mur_position position, int amount) {
  return api->play_mur(position, amount);
}

/// Remove squares with position >= to the given square.
extern "C" action_error api_play_nose(int x, int y) {
  return api->play_nose(x, y);
}

/// Your identifier (not always in {0, 1}).
extern "C" int api_me() { return api->me(); }

/// Your opponent's identifier (not always in {0, 1}).
extern "C" int api_opponent() { return api->opponent(); }

/// The current score of the specified player.
extern "C" int api_score(int player) { return api->score(player); }

/// MUR role (attacker/defender) of the specified player.
extern "C" mur_role api_mur_role_of_player(int player) {
  return api->mur_role_of_player(player);
}

/// Current amount of stock remaining for the specified player.
extern "C" int api_mur_stock(int player) { return api->mur_stock(player); }

/// Amount of stock lost considering both players' moves.
extern "C" mur_losses api_mur_compute_stock_loss(mur_position attacker,
                                          mur_position defender,
                                          int atk_amount, int dfd_amount) {
  return api->mur_compute_stock_loss(attacker, defender, atk_amount,
                                     dfd_amount);
}

/// Last MUR position played by the specified player.
extern "C" mur_position api_mur_last_pos(int player) {
  return api->mur_last_pos(player);
}

/// Last stock amount used by the specified player.
extern "C" int api_mur_last_used_stock(int player) {
  return api->mur_last_used_stock(player);
}

/// Position of the last played square in the NOSE game.
extern "C" nose_position api_nose_last_played_square() {
  return api->nose_last_played_square();
}

/// Number of remaining squares in the NOSE game.
extern "C" int api_nose_remaining_squares() {
  return api->nose_remaining_squares();
}

/// Minimum number of squares to take. Returns -1 if the MUR game of the current
/// turn is not over.
extern "C" int api_nose_squares_to_take() {
  return api->nose_squares_to_take();
}

/// count number of squares taken for a specific move
extern "C" int api_nose_squares_taken(int x, int y) {
  return api->nose_squares_taken(x, y);
}

/// Affiche le contenu d'une valeur de type mur_position
std::ostream& operator<<(std::ostream& os, mur_position v) {
  switch (v) {
  case POS_N:
    os << "POS_N";
    break;
  case POS_O:
    os << "POS_O";
    break;
  case POS_S:
    os << "POS_S";
    break;
  case POS_E:
    os << "POS_E";
    break;
  case POS_INVALID:
    os << "POS_INVALID";
    break;
  }
  return os;
}
extern "C" void api_print_mur_position(mur_position v) {
  std::cerr << v << std::endl;
}

/// Affiche le contenu d'une valeur de type mur_role
std::ostream& operator<<(std::ostream& os, mur_role v) {
  switch (v) {
  case ATTACKER:
    os << "ATTACKER";
    break;
  case DEFENDER:
    os << "DEFENDER";
    break;
  }
  return os;
}
extern "C" void api_print_mur_role(mur_role v) {
  std::cerr << v << std::endl;
}

/// Affiche le contenu d'une valeur de type action_error
std::ostream& operator<<(std::ostream& os, action_error v) {
  switch (v) {
  case OK:
    os << "OK";
    break;
  case INVALID_ARGUMENT:
    os << "INVALID_ARGUMENT";
    break;
  case INVALID_NOSE_PLAYER:
    os << "INVALID_NOSE_PLAYER";
    break;
  case WRONG_GAME:
    os << "WRONG_GAME";
    break;
  case LACK_RESOURCES:
    os << "LACK_RESOURCES";
    break;
  case NOT_ENOUGH_SQUARES_TAKEN:
    os << "NOT_ENOUGH_SQUARES_TAKEN";
    break;
  case ALREADY_CALLED:
    os << "ALREADY_CALLED";
    break;
  }
  return os;
}
extern "C" void api_print_action_error(action_error v) {
  std::cerr << v << std::endl;
}

/// Affiche le contenu d'une valeur de type nose_position
std::ostream& operator<<(std::ostream& os, nose_position v) {
  os << "{ ";
  os << "x"
     << "=" << v.x;
  os << ", ";
  os << "y"
     << "=" << v.y;
  os << " }";
  return os;
}
extern "C" void api_print_nose_position(nose_position v) {
  std::cerr << v << std::endl;
}
