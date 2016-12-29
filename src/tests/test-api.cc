#include "../api.hh"
#include "test-helpers.hh"
#include "../constant.hh"

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
