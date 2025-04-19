#include "snake.h"

using namespace s21;
////////////////get///////////////////////////
Controller* GetGameController() {
  static Controller controller;
  return &controller;
}

GameInfo_t updateCurrentState() {
  Controller* controller = GetGameController();
  GameInfo_t result;
  result.field = controller->data.field;
  result.high_score = controller->data.high_score;
  result.level = controller->data.level;
  result.next = nullptr;
  result.pause = controller->data.pause;
  result.score = controller->data.score;
  result.speed = controller->data.speed;
  return result;
}

void Controller::PutHighScore() {
  std::string filePath = "../game_score/snake.txt";
  std::ofstream outFile(filePath, std::ios::trunc);
  outFile << data.high_score;
  outFile.close();
}

int Controller::GetHighScore() {
  std::string filePath = "../game_score/snake.txt";
  std::ifstream inFile(filePath);

  std::string line;
  std::getline(inFile, line);

  inFile.close();

  int result = 0;
  int ten = 1;

  for (int i = line.size() - 1; i > -1; i--) {
    result = result + (line[i] - 48) * ten;
    ten = ten * 10;
  }
  return result;
}
/////////////////////////////////////////

/////////////construct///////////////
Controller::Controller() {
  data.field = new int*[20];
  for (int i = 0; i < 20; i++) {
    data.field[i] = new int[10];
  }

  Restart();
}

Controller::~Controller() {
  for (int i = 0; i < 20; i++) {
    delete[] data.field[i];
  }
  delete[] data.field;
}
////////////////////////////

bool Controller::StartState() {  // может еще чето надо дописать
  bool end = true;

  if (action == Start) {
    state = Game_;

  } else if (action == Terminate) {
    state = Exit_;
    end = false;
  }
  return end;
}

bool Controller::GameLoss() {
  bool end = true;

  if (action == Start || action == Terminate) {
    state = Exit_;
    end = false;
  }
  return end;
}

bool Controller::GameWin() {
  bool end = true;

  if (action == Start || action == Terminate) {
    state = Exit_;
    end = false;
  }
  return end;
}

void Controller::Restart() {
  data.next = nullptr;

  data.score = 0;
  data.high_score = GetHighScore();
  data.level = 1;
  data.speed = 100;
  data.pause = 0;

  snake_body.clear();
  snake_body.emplace_back(9, 5);
  snake_body.emplace_back(10, 5);
  snake_body.emplace_back(11, 5);
  snake_body.emplace_back(12, 5);

  action = NoAction;

  state = Start_;

  apple = GenerateApple();

  course = Up;

  ClearField();
  PaintSnake();
  PaintApple();

  tick = 0;
  maxtick = 140;
}

bool Controller::GamePause() {
  bool end = true;

  if (action == Pause) {  // обработать паузу
    state = Game_;

  } else if (action == Terminate) {
    state = Exit_;
    end = false;
  }
  return end;
}

bool Controller::GameStateS() {
  tick++;

  bool end = true;

  if (action == Pause) {
    state = Pause_;

  } else if (action == Terminate) {
    state = Exit_;
    end = false;

  } else if (action == Left && course != Right) {
    end = MoveLeft();
    tick = 0;

  } else if (action == Right && course != Left) {
    end = MoveRight();
    tick = 0;

  } else if (action == Up && course != Down) {
    end = MoveUp();
    tick = 0;

  } else if (action == Down && course != Up) {
    end = MoveDown();
    tick = 0;

  } else if (action == Action) {
    end = MoveCourse();

  } else if (tick > maxtick && end == true) {
    end = MoveCourse();
    tick = 0;
  }

  return end;
}

bool Controller::MoveCourse() {
  bool end = true;
  if (course == Right) {
    end = MoveRight();
  } else if (course == Left) {
    end = MoveLeft();
  } else if (course == Up) {
    end = MoveUp();
  } else if (course == Down) {
    end = MoveDown();
  }
  return end;
}

bool Controller::MoveLeft() {
  bool end = CheckСoordinates(snake_body[0].first, snake_body[0].second - 1);
  if (end == true) {
    course = Left;
  }
  return end;
}

bool Controller::MoveRight() {
  bool end = CheckСoordinates(snake_body[0].first, snake_body[0].second + 1);
  if (end == true) {
    course = Right;
  }
  return end;
}

bool Controller::MoveUp() {
  bool end = CheckСoordinates(snake_body[0].first - 1, snake_body[0].second);
  if (end == true) {
    course = Up;
  }
  return end;
}

bool Controller::MoveDown() {
  bool end = CheckСoordinates(snake_body[0].first + 1, snake_body[0].second);
  if (end == true) {
    course = Down;
  }
  return end;
}

bool Controller::CheckСoordinates(int i, int j) {
  bool end = true;
  if (i == apple.first && j == apple.second) {
    if (snake_body.size() == 199) {
      state = Win_;
    } else {
      snake_body.insert(snake_body.begin(), apple);
      apple = GenerateApple();
      data.score++;
      PaintApple();
      PaintSnake();
      UpdataeLvlScoreHScoreSpeed();
    }

  } else if (i < 0 || i > 19 || j < 0 || j > 9 || data.field[i][j] == 1) {
    state = Loss_;
  } else {
    snake_body.insert(snake_body.begin(), std::make_pair(i, j));
    snake_body.pop_back();
    ClearField();
    PaintApple();
    PaintSnake();
  }
  return end;
}

void Controller::UpdataeLvlScoreHScoreSpeed() {
  if (data.score > data.high_score) {
    data.high_score = data.score;
    PutHighScore();
  }
  if (data.level < 10) {
    data.level = data.score / 5 + 1;
  }
  if (data.speed < 1000) {
    data.speed = data.level * 100;
  }
  maxtick = 150 - data.level * 10;
}

void Controller::PaintSnake() {
  for (size_t i = 1; i < snake_body.size(); i++) {
    data.field[snake_body[i].first][snake_body[i].second] = 1;
  }
  data.field[snake_body[0].first][snake_body[0].second] = 2;
}

void Controller::PaintApple() { data.field[apple.first][apple.second] = 3; }

void Controller::ClearField() {
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 10; j++) {
      data.field[i][j] = 0;
    }
  }
}

void userInput(UserAction_t action, bool hold) {
  if (hold == 0) {
    Controller* controller = GetGameController();
    controller->action = action;
  }
}

std::pair<int, int> Controller::GenerateApple() {  // генерируем яблоко
  int count = RandomNum(200 - snake_body.size());
  int error = 0;
  std::pair<int, int> apple(0, 0);

  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 10; j++) {
      count--;

      if (count == 0) {
        for (size_t k = 0; k < snake_body.size(); k++) {
          if (snake_body[k].first == i && snake_body[k].second == j) {
            error++;
            count = 1;
            break;
          }
        }

        if (error > 0) {
          error = 0;
        } else {
          apple = std::make_pair(i, j);
          error = 3;
          break;
        }
      }
    }
    if (error == 3) {
      break;
    }
  }

  return apple;
}

int RandomNum(int max) {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib(0, max);
  return distrib(gen);
}

bool updateGame() {  // обновлять игру
  bool end = true;
  Controller* controller = GetGameController();
  if (controller->state == Start_) {
    end = controller->StartState();
  } else if (controller->state == Game_) {
    end = controller->GameStateS();
  } else if (controller->state == Pause_) {
    end = controller->GamePause();
  } else if (controller->state == Win_) {
    end = controller->GameWin();
  } else if (controller->state == Loss_) {
    end = controller->GameLoss();
  }
  return end;
}
