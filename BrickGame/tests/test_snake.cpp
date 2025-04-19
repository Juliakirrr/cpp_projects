#include "test_snake.h"

TEST(StartGame, Constructor_Default) {
  userInput(NoAction, 0);
  updateGame();
  EXPECT_EQ(GetGameController()->state, Start_);
  userInput(Start, 0);
  updateGame();
  EXPECT_EQ(GetGameController()->state, Game_);
  userInput(Pause, 0);
  updateGame();
  EXPECT_EQ(GetGameController()->state, Pause_);
  userInput(Pause, 0);
  updateGame();
  EXPECT_EQ(GetGameController()->state, Game_);
}

TEST(ShiftingSnake, Constructor_Default) {
  userInput(Left, 0);
  updateGame();
  EXPECT_EQ(GetGameController()->state, Game_);
  EXPECT_EQ(GetGameController()->course, Left);
  EXPECT_EQ(GetGameController()->snake_body[0].first, 9);
  EXPECT_EQ(GetGameController()->snake_body[0].second, 4);

  userInput(Down, 0);
  updateGame();
  EXPECT_EQ(GetGameController()->state, Game_);
  EXPECT_EQ(GetGameController()->course, Down);
  EXPECT_EQ(GetGameController()->snake_body[0].first, 10);
  EXPECT_EQ(GetGameController()->snake_body[0].second, 4);

  userInput(Down, 0);
  updateGame();
  userInput(Right, 0);
  updateGame();
  EXPECT_EQ(GetGameController()->state, Game_);
  EXPECT_EQ(GetGameController()->course, Right);
  EXPECT_EQ(GetGameController()->snake_body[0].first, 11);
  EXPECT_EQ(GetGameController()->snake_body[0].second, 5);

  userInput(Up, 0);
  updateGame();
  EXPECT_EQ(GetGameController()->state, Game_);
  EXPECT_EQ(GetGameController()->course, Up);
  EXPECT_EQ(GetGameController()->snake_body[0].first, 10);
  EXPECT_EQ(GetGameController()->snake_body[0].second, 5);

  userInput(Action, 0);
  updateGame();
  EXPECT_EQ(GetGameController()->state, Game_);
  EXPECT_EQ(GetGameController()->course, Up);
  EXPECT_EQ(GetGameController()->snake_body[0].first, 9);
  EXPECT_EQ(GetGameController()->snake_body[0].second, 5);
}

TEST(PauseSnake, Constructor_Default) {
  GameInfo_t data = updateCurrentState();
  EXPECT_EQ(GetGameController()->data.high_score, data.high_score);
  EXPECT_EQ(GetGameController()->data.score, data.score);
  EXPECT_EQ(GetGameController()->data.level, data.level);
  EXPECT_EQ(GetGameController()->data.speed, data.speed);
}

TEST(WinLoss, Constructor_Default) {
  GetGameController()->action = Start;
  bool a = GetGameController()->GameLoss();
  EXPECT_EQ(GetGameController()->state, Exit_);
  EXPECT_EQ(a, false);

  GetGameController()->action = Start;
  a = GetGameController()->GameWin();
  EXPECT_EQ(GetGameController()->state, Exit_);
  EXPECT_EQ(a, false);
}

TEST(Update, Constructor_Default) {
  GetGameController()->data.high_score = 0;
  GetGameController()->data.level = 1;
  GetGameController()->data.score = 0;
  GetGameController()->data.speed = 100;
  GetGameController()->maxtick = 150;
  GetGameController()->UpdataeLvlScoreHScoreSpeed();
  EXPECT_EQ(GetGameController()->data.high_score, 0);
  EXPECT_EQ(GetGameController()->data.level, 1);
  EXPECT_EQ(GetGameController()->data.score, 0);
  EXPECT_EQ(GetGameController()->data.speed, 100);
}
