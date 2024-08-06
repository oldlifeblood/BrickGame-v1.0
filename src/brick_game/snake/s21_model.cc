#include "s21_model.h"

namespace s21 {

s21_model::s21_model(s21_controller *ctrl) : control(ctrl) {}

s21_model::~s21_model() {}

void s21_model::initGame(GameInfo_t *game, Snake *snake) {
  game->field = new int *[HEIGHT + 1];
  for (int i = -1; i < HEIGHT + 1; i++) {
    game->field[i] = new int[WIDTH];
  }

  snake->snake = new int *[4];
  for (int i = 0; i < 4; ++i) {
    snake->snake[i] = new int[2];
  }
  snake->xHead = 4;
  snake->yHead = 0;
  snake->length = 4;
  control->direction = s21_controller::Right;

  for (int i = 0; i < snake->length; ++i) {
    snake->snake[i][0] = snake->xHead - i;
    snake->snake[i][1] = snake->yHead;
  }
  newFruit(game, snake);
  game->score = 0;
  game->high_score = readHighScore();
  game->level = 1;
  game->speed = 200000;
  game->pause = 0;
}

void s21_model::moveSnake(Snake *snake) {
  int prevX = snake->xHead;
  int prevY = snake->yHead;

  if (control->direction == s21_controller::Right)
    snake->xHead++;
  else if (control->direction == s21_controller::Left)
    snake->xHead--;
  else if (control->direction == s21_controller::Up)
    snake->yHead--;
  else if (control->direction == s21_controller::Down)
    snake->yHead++;

  for (int i = 1; i < snake->length; ++i) {
    int tempX = snake->snake[i][0];
    int tempY = snake->snake[i][1];
    snake->snake[i][0] = prevX;
    snake->snake[i][1] = prevY;
    prevX = tempX;
    prevY = tempY;
  }
}

void s21_model::newFruit(GameInfo_t *game, Snake *snake) {
  int x, y;

  do {
    x = rand() % WIDTH;
    y = rand() % HEIGHT;
  } while (isSnakeCell(snake, x, y));
  game->field[y][x] = 2;
}

void s21_model::addBody(Snake *snake) {
  int **newSnake = new int *[snake->length + 1];
  for (int i = 0; i < snake->length + 1; i++) {
    newSnake[i] = new int[2];
  }

  for (int i = 0; i < snake->length; i++) {
    newSnake[i][0] = snake->snake[i][0];
    newSnake[i][1] = snake->snake[i][1];
  }

  newSnake[snake->length][0] = snake->snake[snake->length - 1][0];
  newSnake[snake->length][1] = snake->snake[snake->length - 1][1];

  for (int i = 0; i < snake->length; i++) {
    delete[] snake->snake[i];
  }
  delete[] snake->snake;

  snake->snake = newSnake;
  snake->length++;
}

void s21_model::eatFruit(GameInfo_t *game, Snake *snake) {
  if (game->field[snake->yHead][snake->xHead] == 2) {
    addBody(snake);
    game->field[snake->yHead][snake->xHead] = 0;
    updateInfo(game);
    newFruit(game, snake);
  }
}

int s21_model::gameOverCheck(Snake *snake) {
  for (int i = 1; i < snake->length; ++i) {
    if ((snake->xHead == snake->snake[i][0] &&
         snake->yHead == snake->snake[i][1]) ||
        snake->xHead == -1 || snake->xHead == WIDTH || snake->yHead == -1 ||
        snake->yHead == HEIGHT) {
      return true;
    }
  }
  return false;
}

void s21_model::updateInfo(GameInfo_t *game) {
  game->score += 1;
  if (game->score > game->high_score) {
    game->high_score = game->score;
    writeHighScore(game->score);
  }
  if (game->level < 10) game->level = game->score / 5 + 1;
  game->speed = 215000 - game->level * 15000;
}

bool s21_model::isSnakeCell(Snake *snake, int x, int y) {
  for (int i = 0; i < snake->length; ++i) {
    if (snake->snake[i][0] == x && snake->snake[i][1] == y) {
      return true;
    }
  }
  return false;
}

int s21_model::readHighScore() {
  int high_score = 0;
  std::ifstream inputFile("high_score_snake.txt");
  inputFile >> high_score;
  inputFile.close();
  return high_score;
}
void s21_model::writeHighScore(int high_score) {
  std::ofstream outputFile("high_score_snake.txt");
  outputFile << high_score << std::endl;
  outputFile.close();
}

bool s21_model::winGame(Snake snake) {
  if (snake.length == 200) return true;
  return false;
}

void s21_model::free_memory(GameInfo_t *game, Snake *snake) {
  if (game->field != nullptr) {
    for (int i = 0; i < HEIGHT + 1; i++) {
      delete[] game->field[i];
    }
    delete[] game->field;
  }

  if (snake->snake != nullptr) {
    for (int i = 0; i < 4; ++i) {
      delete[] snake->snake[i];
    }
    delete[] snake->snake;
  }
}
}  // namespace s21
