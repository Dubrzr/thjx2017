#pragma once

#include <rules/rules.hh>
#include <utils/log.hh>

#include <rules/action.hh>
#include <rules/actions.hh>
#include <rules/client-messenger.hh>
#include <rules/options.hh>
#include <rules/player.hh>
#include <rules/server-messenger.hh>

#define SDEBUG(S, args...) DEBUG("[SERVER] " S, ##args)
#define CDEBUG(S, args...) DEBUG("[CLIENT-%d] " S, opt_.player->id, ##args)
#define PDEBUG(S, a...)                                                        \
  if (opt_.player)                                                             \
    CDEBUG(S, ##a);                                                            \
  else                                                                         \
  SDEBUG(S, ##a)
// These rules are designed for games where players play on different turns
// The player pool is reset at every turn and should be populated in
// start_of_round
class PoolBasedRules : public rules::Rules {
public:
  explicit PoolBasedRules(const rules::Options opt);
  ~PoolBasedRules() override {}

  // Called each time a client starts its turn
  virtual void start_of_turn(uint32_t) {}
  virtual void start_of_player_turn(uint32_t) {}

  // Called each time a client has finished its turn
  virtual void end_of_turn(uint32_t) {}
  virtual void end_of_player_turn(uint32_t) {}
  virtual void handle_timeout(uint32_t) {}

  void server_loop(rules::ServerMessenger_sptr msgr) final;
  void player_loop(rules::ClientMessenger_sptr msgr) final;
  void spectator_loop(rules::ClientMessenger_sptr) {}

  void add_player_to_pool(rules::Player_sptr p);

private:
  rules::Players_sptr pool_;

  void apply_actions(rules::Actions* actions, bool apply);
  rules::Actions* run_player(rules::ServerMessenger_sptr msgr, uint32_t id);
  rules::Actions* run_player(rules::ClientMessenger_sptr msgr, uint32_t id,
                             bool me);
};
