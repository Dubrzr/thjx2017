#include "../api.hh"
#include "../constant.hh"
#include "test-helpers.hh"

TEST_F(ApiTest, Api_RetrievePlayerIdentifiers) {
  EXPECT_EQ(PLAYER_ID_1, players[0].api->me());
  EXPECT_EQ(PLAYER_ID_2, players[0].api->opponent());
  EXPECT_EQ(PLAYER_ID_2, players[1].api->me());
  EXPECT_EQ(PLAYER_ID_1, players[1].api->opponent());
}

TEST_F(ApiTest, Api_MUR_RoleOfPlayer) {
  EXPECT_EQ(DEFENDER, players[0].api->mur_role_of_player(PLAYER_ID_1));
  EXPECT_EQ(ATTACKER, players[0].api->mur_role_of_player(PLAYER_ID_2));
  EXPECT_EQ(DEFENDER, players[1].api->mur_role_of_player(PLAYER_ID_1));
  EXPECT_EQ(ATTACKER, players[1].api->mur_role_of_player(PLAYER_ID_2));
}

TEST_F(ApiTest, Api_MUR_ComputeStockLoss) {
  mur_losses stock_loss;
  stock_loss = players[0].api->mur_compute_stock_loss(POS_N, POS_N, 42, 57);
  EXPECT_EQ(stock_loss.attacker, 2 * (57 + 42));
  EXPECT_EQ(stock_loss.defender, 0);

  stock_loss = players[0].api->mur_compute_stock_loss(POS_N, POS_O, 42, 57);
  EXPECT_EQ(stock_loss.attacker, 57);
  EXPECT_EQ(stock_loss.defender, 42);
}

TEST_F(ApiTest, Api_Actions_leak) {
  for (size_t i = 0; i < 10000; ++i) {
    players[0].api->play_mur(POS_O, 1);
    players[1].api->play_mur(POS_O, 1);

    rules::Actions *a = players[0].api->actions();
    a->clear();

    rules::Actions *a2 = players[1].api->actions();
    a2->clear();

    st->resolve_mur();
  }
}
