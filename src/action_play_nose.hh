#ifndef ACTION_PLAY_NOSE_HH
#define ACTION_PLAY_NOSE_HH

#include <rules/action.hh>

#include "actions.hh"
#include "constant.hh"
#include "game_state.hh"

class ActionPlayNose : public rules::Action<GameState> {
public:
  ActionPlayNose(int x, int y, int player_id)
      : x_(x), y_(y), player_id_(player_id) {}
  ActionPlayNose() {} // for register_action()

  int check(const GameState* st) const override;
  void apply_on(GameState* st) const override;

  void handle_buffer(utils::Buffer& buf) override {
    buf.handle(x_);
    buf.handle(y_);
    buf.handle(player_id_);
  }

  uint32_t player_id() const override { return player_id_; };
  uint32_t id() const override { return ID_ACTION_PLAY_NOSE; }

private:
  int x_;
  int y_;
  int player_id_;
};

#endif // !ACTION_PLAY_NOSE_HH
