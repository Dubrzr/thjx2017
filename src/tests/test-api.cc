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
  int stock_loss;
  stock_loss = players[0].api->mur_compute_stock_loss(POS_N, POS_N, 42, 57);
  EXPECT_EQ(stock_loss, 0);
  stock_loss = players[1].api->mur_compute_stock_loss(POS_N, POS_N, 57, 42);
  EXPECT_EQ(stock_loss, 2 * (57 + 42));
  stock_loss = players[0].api->mur_compute_stock_loss(POS_N, POS_O, 42, 57);
  EXPECT_EQ(stock_loss, 42);
  stock_loss = players[1].api->mur_compute_stock_loss(POS_N, POS_O, 57, 42);
  EXPECT_EQ(stock_loss, 42);
}
