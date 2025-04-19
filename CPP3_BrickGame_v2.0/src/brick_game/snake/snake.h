#ifndef BRICK_GAME_SNAKE
#define BRICK_GAME_SNAKE

#include <fstream>
#include <random>
#include <utility>
#include <vector>

typedef enum {
  Start_,
  Game_,
  Pause_,
  Win_,
  Loss_,
  Exit_,

} GameState;

typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action,
  NoAction
} UserAction_t;

typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

namespace s21 {
class Controller {
 public:
  Controller();
  ~Controller();

  GameInfo_t data;
  std::vector<std::pair<int, int>> snake_body;
  UserAction_t action;
  GameState state;
  std::pair<int, int> apple;
  UserAction_t course;
  int tick;
  int maxtick;

  void FreeField();
  int GetHighScore();
  void PutHighScore();
  std::pair<int, int> GenerateApple();

  bool StartState();
  bool GameStateS();
  bool GamePause();
  bool MoveLeft();
  bool MoveRight();
  bool MoveUp();
  bool MoveDown();
  bool GameLoss();
  bool GameWin();
  bool MoveCourse();
  void ClearField();
  void PaintApple();
  void PaintSnake();
  void UpdataeLvlScoreHScoreSpeed();
  void Restart();
  bool CheckСoordinates(int i, int j);
};
};  // namespace s21

void userInput(UserAction_t action, bool hold);
GameInfo_t updateCurrentState();
s21::Controller *GetGameController();
bool updateGame();
int RandomNum(int max);

#endif