#ifndef RULES_RULES_HH_
#define RULES_RULES_HH_

#include <memory>

#include <rules/actions.hh>
#include <rules/client-messenger.hh>
#include <rules/options.hh>
#include <rules/player.hh>
#include <rules/rules.hh>
#include <rules/server-messenger.hh>
#include <utils/dll.hh>
#include <utils/sandbox.hh>

#include "api.hh"
#include "pool_based_rules.hh"

typedef void (*f_champ_game_init)();
typedef void (*f_champ_play_mur)();
typedef void (*f_champ_mur_end)();
typedef void (*f_champ_play_nose)();
typedef void (*f_champ_game_end)();

class Rules : public PoolBasedRules {
public:
  explicit Rules(const rules::Options opt);
  virtual ~Rules() {}

  virtual rules::Actions* get_actions();
  virtual void apply_action(const rules::IAction_sptr& action);
  virtual bool is_finished();

protected:
  void at_player_start(rules::ClientMessenger_sptr msgr);
  void at_player_end(rules::ClientMessenger_sptr msgr);

  void player_turn();

  void start_of_round();
  void end_of_round();

  void end_of_player_turn(unsigned player_id);

  void dump_state(std::ostream& out);

  void handle_timeout(uint32_t player);

  f_champ_game_init champ_game_init_;
  f_champ_play_mur champ_play_mur_;
  f_champ_mur_end champ_mur_end_;
  f_champ_play_nose champ_play_nose_;
  f_champ_game_end champ_game_end_;

private:
  void register_actions();
  unsigned nose_player_;

  std::unique_ptr<utils::DLL> champ_dll_;
  std::unique_ptr<Api> api_;
  utils::Sandbox sandbox_;
};

#endif // !RULES_RULES_HH_
