#ifndef ACTION_PLAY_MUR_HH
#define ACTION_PLAY_MUR_HH

#include <rules/action.hh>

#include "actions.hh"
#include "game_state.hh"
#include "constant.hh"

class ActionPlayMur : public rules::Action<GameState>
{
public:
    ActionPlayMur(mur_position position, int amount, int player_id)
        : position_(position)
        , amount_(amount)
        , player_id_(player_id) {}
    ActionPlayMur() {} // for register_action()

    int check(const GameState* st) const override;
    void apply_on(GameState* st) const override;

    void handle_buffer(utils::Buffer& buf) override
    {
        buf.handle(position_);
        buf.handle(amount_);
        buf.handle(player_id_);
    }

    uint32_t player_id() const override { return player_id_; };
    uint32_t id() const override { return ID_ACTION_PLAY_MUR; }

private:
    mur_position position_;
    int amount_;
    int player_id_;
};

#endif // !ACTION_PLAY_MUR_HH
