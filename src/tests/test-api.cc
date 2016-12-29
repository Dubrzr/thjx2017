#include "../api.hh"
#include "test-helpers.hh"

TEST_F(ApiTest, Api_RetrievePlayerIdentifiers) {
  EXPECT_EQ(PLAYER_ID_1, players[0].api->me());
  EXPECT_EQ(PLAYER_ID_2, players[0].api->opponent());
  EXPECT_EQ(PLAYER_ID_2, players[1].api->me());
  EXPECT_EQ(PLAYER_ID_1, players[1].api->opponent());
}
