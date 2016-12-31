#include <iostream>

#include "constant.hh"
#include "dumper.hh"
#include "game_state.hh"

/* Put some binary content as a JSON string in the output stream. */
static void dump_binary(std::ostream& ss, const uint8_t bytes[],
                        unsigned size) {
  const char* hextable = "0123456789ABCDEF";

  ss << "\"";
  for (unsigned i = 0; i < size; ++i) {
    if (bytes[i] == '"')
      ss << "\\\"";
    else if (bytes[i] == '\\')
      ss << "\\\\";
    else if (0x20 <= bytes[i] && bytes[i] <= 0x7e)
      ss << (char)bytes[i];
    else
      ss << "\\u00" << hextable[bytes[i] >> 4] << hextable[bytes[i] & 0x0f];
  }
  ss << "\"";
}

/* Dump everything that describe players: score and position on the map.  */

static void dump_players(std::ostream& ss, const GameState& st) {
  auto& players = st.get_players()->players;
  bool is_first = true;

  ss << "{";
  for (unsigned i = 0; i < players.size(); ++i) {
    const int id = players[i]->id;

    if (players[i]->type != rules::PLAYER)
      continue;

    if (!is_first)
      ss << ", ";

    is_first = false;

    ss << "\"" << id << "\": {"
       << "\"name\": ";
    dump_binary(ss, reinterpret_cast<const uint8_t*>(players[i]->name.c_str()),
                players[i]->name.size());

    auto np = st.get_nose_played_square(id);

    ss << ", "
       << "\"mur_stock\": " << st.get_mur_stock(id) << ","
       << "\"mur_role\": " << st.get_mur_role(id) << ","
       << "\"mur_used_stock\": " << st.get_mur_used_stock(id) << ","
       << "\"mur_position\": " << st.get_mur_position(id) << ","
       << "\"nose_played_square\": [" << np.x << ", " << np.y << "],"
       << "\"timed_out\": " << st.get_timed_out(id) << ","
       << "\"score\": " << players[i]->score << "}";
  }
  ss << "}";
}

void dump_game_state(std::ostream& out, const GameState& st) {
  out << "{";

  out << "\"game\": ";
  switch (st.get_current_played_game()) {
  case NOSE:
    out << "\"NOSE\"";
    break;
  case MUR:
    out << "\"MUR\"";
    break;
  }
  out << ", ";

  out << "\"nose_player_id\": " << st.get_nose_player_id() << ", ";
  out << "\"players\": ";
  dump_players(out, st);

  out << "}\n";
}
