#include <gtest/gtest.h>

#include "../brick_game/snake/s21_controller.h"
#include "../brick_game/snake/s21_model.h"

TEST(MoveSnake, case1) {
  s21::s21_controller ctrl;
  s21::s21_model m(&ctrl);
  ctrl.direction = s21::s21_controller::Right;
  s21::s21_model::Snake snake;
  s21::s21_model::GameInfo_t game;
  m.initGame(&game, &snake);
  snake.xHead = 5;
  snake.yHead = 5;
  snake.length = 3;
  snake.snake[0][0] = 5;
  snake.snake[0][1] = 5;
  snake.snake[1][0] = 4;
  snake.snake[1][1] = 5;
  snake.snake[2][0] = 3;
  snake.snake[2][1] = 5;

  m.moveSnake(&snake);

  EXPECT_EQ(snake.xHead, 6);
  EXPECT_EQ(snake.yHead, 5);
}

TEST(MoveSnake, case2) {
  s21::s21_controller ctrl;
  s21::s21_model m(&ctrl);
  s21::s21_model::Snake snake;
  s21::s21_model::GameInfo_t game;
  m.initGame(&game, &snake);
  ctrl.direction = s21::s21_controller::Left;
  snake.xHead = 5;
  snake.yHead = 5;
  snake.length = 3;
  snake.snake[0][0] = 5;
  snake.snake[0][1] = 5;
  snake.snake[1][0] = 6;
  snake.snake[1][1] = 5;
  snake.snake[2][0] = 7;
  snake.snake[2][1] = 5;

  m.moveSnake(&snake);

  EXPECT_EQ(snake.xHead, 4);
  EXPECT_EQ(snake.yHead, 5);
}

TEST(MoveSnake, case3) {
  s21::s21_controller ctrl;
  s21::s21_model m(&ctrl);
  s21::s21_model::Snake snake;
  s21::s21_model::GameInfo_t game;
  m.initGame(&game, &snake);
  ctrl.direction = s21::s21_controller::Up;
  snake.xHead = 5;
  snake.yHead = 5;
  snake.length = 3;
  snake.snake[0][0] = 5;
  snake.snake[0][1] = 5;
  snake.snake[1][0] = 5;
  snake.snake[1][1] = 6;
  snake.snake[2][0] = 5;
  snake.snake[2][1] = 7;

  m.moveSnake(&snake);

  EXPECT_EQ(snake.xHead, 5);
  EXPECT_EQ(snake.yHead, 4);
}

TEST(MoveSnake, case4) {
  s21::s21_controller ctrl;
  s21::s21_model m(&ctrl);
  s21::s21_model::Snake snake;
  s21::s21_model::GameInfo_t game;
  m.initGame(&game, &snake);
  ctrl.direction = s21::s21_controller::Down;
  snake.xHead = 5;
  snake.yHead = 5;
  snake.length = 3;
  snake.snake[0][0] = 5;
  snake.snake[0][1] = 5;
  snake.snake[1][0] = 5;
  snake.snake[1][1] = 4;
  snake.snake[2][0] = 5;
  snake.snake[2][1] = 3;

  m.moveSnake(&snake);

  EXPECT_EQ(snake.xHead, 5);
  EXPECT_EQ(snake.yHead, 6);
}

TEST(MoveSnake, case5) {
  s21::s21_controller ctrl;
  s21::s21_model m(&ctrl);
  s21::s21_model::Snake snake;
  s21::s21_model::GameInfo_t game;
  m.initGame(&game, &snake);
  ctrl.direction = s21::s21_controller::Right;
  snake.xHead = 5;
  snake.yHead = 5;
  snake.length = 3;
  snake.snake[0][0] = 5;
  snake.snake[0][1] = 5;
  snake.snake[1][0] = 4;
  snake.snake[1][1] = 5;
  snake.snake[2][0] = 3;
  snake.snake[2][1] = 5;

  m.moveSnake(&snake);

  EXPECT_EQ(snake.snake[0][0], 5);
  EXPECT_EQ(snake.snake[0][1], 5);
  EXPECT_EQ(snake.snake[1][0], 5);
  EXPECT_EQ(snake.snake[1][1], 5);
  EXPECT_EQ(snake.snake[2][0], 4);
  EXPECT_EQ(snake.snake[2][1], 5);
}

TEST(eatFruit, case1) {
  s21::s21_controller ctrl;
  s21::s21_model m(&ctrl);
  s21::s21_model::Snake snake;
  s21::s21_model::GameInfo_t game;
  m.initGame(&game, &snake);
  snake.xHead = 5;
  snake.yHead = 5;
  snake.length = 3;
  snake.snake[0][0] = 5;
  snake.snake[0][1] = 5;
  snake.snake[1][0] = 4;
  snake.snake[1][1] = 5;
  snake.snake[2][0] = 3;
  snake.snake[2][1] = 5;

  game.field[5][5] = 2;

  m.eatFruit(&game, &snake);

  EXPECT_EQ(snake.length, 4);
  EXPECT_EQ(game.field[5][5], 0);
}

TEST(gameOver, case1) {
  s21::s21_controller ctrl;
  s21::s21_model m(&ctrl);
  s21::s21_model::Snake snake;
  s21::s21_model::GameInfo_t game;
  m.initGame(&game, &snake);
  snake.xHead = 5;
  snake.yHead = 5;
  snake.length = 3;
  snake.snake[0][0] = 5;
  snake.snake[0][1] = 5;
  snake.snake[1][0] = 4;
  snake.snake[1][1] = 5;
  snake.snake[2][0] = 3;
  snake.snake[2][1] = 5;

  snake.xHead = 4;
  snake.yHead = 5;

  EXPECT_TRUE(m.gameOverCheck(&snake));
}

TEST(gameOver, case2) {
  s21::s21_controller ctrl;
  s21::s21_model m(&ctrl);
  s21::s21_model::Snake snake;
  s21::s21_model::GameInfo_t game;
  m.initGame(&game, &snake);
  snake.xHead = WIDTH;
  snake.yHead = 5;
  snake.length = 3;
  snake.snake[0][0] = 5;
  snake.snake[0][1] = 5;
  snake.snake[1][0] = 4;
  snake.snake[1][1] = 5;
  snake.snake[2][0] = 3;
  snake.snake[2][1] = 5;

  EXPECT_TRUE(m.gameOverCheck(&snake));
}

TEST(gameOver, case3) {
  s21::s21_controller ctrl;
  s21::s21_model m(&ctrl);
  s21::s21_model::Snake snake;
  s21::s21_model::GameInfo_t game;
  m.initGame(&game, &snake);
  snake.xHead = 5;
  snake.yHead = 5;
  snake.length = 3;
  snake.snake[0][0] = 5;
  snake.snake[0][1] = 5;
  snake.snake[1][0] = 4;
  snake.snake[1][1] = 5;
  snake.snake[2][0] = 3;
  snake.snake[2][1] = 5;

  EXPECT_FALSE(m.gameOverCheck(&snake));
}

TEST(newFruit, case1) {
  s21::s21_controller ctrl;
  s21::s21_model m(&ctrl);
  s21::s21_model::Snake snake;
  s21::s21_model::GameInfo_t game;
  m.initGame(&game, &snake);
  snake.length = 3;
  snake.snake[0][0] = 5;
  snake.snake[0][1] = 5;
  snake.snake[1][0] = 4;
  snake.snake[1][1] = 5;
  snake.snake[2][0] = 3;
  snake.snake[2][1] = 5;

  int initialFoodCount = 0;
  for (int i = 0; i < HEIGHT; ++i) {
    for (int j = 0; j < WIDTH; ++j) {
      if (game.field[i][j] == 2) {
        ++initialFoodCount;
      }
    }
  }

  m.newFruit(&game, &snake);

  int foodCount = 0;
  for (int i = 0; i < HEIGHT; ++i) {
    for (int j = 0; j < WIDTH; ++j) {
      if (game.field[i][j] == 2) {
        ++foodCount;
      }
    }
  }

  EXPECT_EQ(foodCount, initialFoodCount + 1);
}

TEST(addBody, case1) {
  s21::s21_controller ctrl;
  s21::s21_model m(&ctrl);
  s21::s21_model::Snake snake;
  s21::s21_model::GameInfo_t game;
  m.initGame(&game, &snake);
  snake.length = 3;
  snake.snake = new int *[snake.length];
  for (int i = 0; i < snake.length; ++i) {
    snake.snake[i] = new int[2];
    snake.snake[i][0] = i;
    snake.snake[i][1] = i;
  }

  m.addBody(&snake);

  EXPECT_EQ(snake.length, 4);
}

TEST(updateInfo, case1) {
  s21::s21_controller ctrl;
  s21::s21_model m(&ctrl);
  s21::s21_model::Snake snake;
  s21::s21_model::GameInfo_t game;
  m.initGame(&game, &snake);
  game.score = 0;

  m.updateInfo(&game);

  EXPECT_EQ(game.score, 1);
}

TEST(updateInfo, case2) {
  s21::s21_controller ctrl;
  s21::s21_model m(&ctrl);
  s21::s21_model::Snake snake;
  s21::s21_model::GameInfo_t game;
  m.initGame(&game, &snake);
  game.score = 20;
  game.level = 1;

  m.updateInfo(&game);

  EXPECT_EQ(game.level, 5);
}

TEST(isSnakeCell, case1) {
  s21::s21_controller ctrl;
  s21::s21_model m(&ctrl);
  s21::s21_model::Snake snake;
  s21::s21_model::GameInfo_t game;
  m.initGame(&game, &snake);
  snake.length = 3;
  snake.snake = new int *[snake.length];
  for (int i = 0; i < snake.length; ++i) {
    snake.snake[i] = new int[2];
    snake.snake[i][0] = i;
    snake.snake[i][1] = i;
  }

  EXPECT_TRUE(m.isSnakeCell(&snake, 1, 1));
}

TEST(isSnakeCell, case2) {
  s21::s21_controller ctrl;
  s21::s21_model m(&ctrl);
  s21::s21_model::Snake snake;
  s21::s21_model::GameInfo_t game;
  m.initGame(&game, &snake);
  snake.length = 3;
  snake.snake = new int *[snake.length];
  for (int i = 0; i < snake.length; ++i) {
    snake.snake[i] = new int[2];
    snake.snake[i][0] = i;
    snake.snake[i][1] = i;
  }

  EXPECT_FALSE(m.isSnakeCell(&snake, 5, 5));
}

TEST(readHighScore, case1) {
  std::ofstream outputFile("high_score_snake.txt");
  outputFile << "100" << std::endl;
  outputFile.close();

  s21::s21_controller ctrl;
  s21::s21_model m(&ctrl);
  int highScore = m.readHighScore();

  EXPECT_EQ(highScore, 100);
}

TEST(writeHighScore, case1) {
  s21::s21_controller ctrl;
  s21::s21_model m(&ctrl);

  m.writeHighScore(100);

  std::ifstream inputFile("high_score_snake.txt");
  int highScore = 0;
  inputFile >> highScore;
  inputFile.close();

  EXPECT_EQ(highScore, 100);
}

TEST(winGame, case1) {
  s21::s21_controller ctrl;
  s21::s21_model m(&ctrl);
  s21::s21_model::Snake snake;
  snake.length = 200;
  bool win = m.winGame(snake);

  EXPECT_TRUE(win);
}

TEST(winGame, case2) {
  s21::s21_controller ctrl;
  s21::s21_model m(&ctrl);
  s21::s21_model::Snake snake;
  snake.length = 199;
  bool win = m.winGame(snake);

  EXPECT_FALSE(win);
}

TEST(s21_ControllerTest, case1) {
  s21::s21_controller ctrl;
  bool hold = false;
  ctrl.direction = s21::s21_controller::Right;

  ctrl.userInput(s21::s21_controller::Left, &hold);

  EXPECT_EQ(ctrl.direction, s21::s21_controller::Right);
}

TEST(s21_ControllerTest, case2) {
  s21::s21_controller ctrl;
  bool hold = false;
  ctrl.direction = s21::s21_controller::Left;

  ctrl.userInput(s21::s21_controller::Right, &hold);

  EXPECT_EQ(ctrl.direction, s21::s21_controller::Left);
}

TEST(s21_ControllerTest, case3) {
  s21::s21_controller ctrl;
  bool hold = false;
  ctrl.direction = s21::s21_controller::Down;

  ctrl.userInput(s21::s21_controller::Up, &hold);

  EXPECT_EQ(ctrl.direction, s21::s21_controller::Down);
}

TEST(s21_ControllerTest, case4) {
  s21::s21_controller ctrl;
  bool hold = false;
  ctrl.direction = s21::s21_controller::Up;

  ctrl.userInput(s21::s21_controller::Down, &hold);

  EXPECT_EQ(ctrl.direction, s21::s21_controller::Up);
}

TEST(s21_ControllerTest, case5) {
  s21::s21_controller ctrl;
  bool hold = false;
  ctrl.pause = 0;

  ctrl.userInput(s21::s21_controller::Pause, &hold);
  EXPECT_EQ(ctrl.pause, 1);

  ctrl.userInput(s21::s21_controller::Pause, &hold);
  EXPECT_EQ(ctrl.pause, 0);
}

TEST(s21_ControllerTest, case6) {
  s21::s21_controller ctrl;
  bool hold = false;
  ctrl.direction = s21::s21_controller::Right;

  ctrl.userInput(s21::s21_controller::Down, &hold);

  EXPECT_EQ(ctrl.direction, s21::s21_controller::Down);
}

TEST(s21_ControllerTest, case7) {
  s21::s21_controller ctrl;
  bool hold = false;
  ctrl.direction = s21::s21_controller::Down;

  ctrl.userInput(s21::s21_controller::Right, &hold);

  EXPECT_EQ(ctrl.direction, s21::s21_controller::Right);
}

TEST(s21_ControllerTest, case8) {
  s21::s21_controller ctrl;
  bool hold = false;
  ctrl.direction = s21::s21_controller::Right;

  ctrl.userInput(s21::s21_controller::Up, &hold);

  EXPECT_EQ(ctrl.direction, s21::s21_controller::Up);
}

TEST(s21_ControllerTest, case9) {
  s21::s21_controller ctrl;
  bool hold = false;
  ctrl.direction = s21::s21_controller::Up;

  ctrl.userInput(s21::s21_controller::Left, &hold);

  EXPECT_EQ(ctrl.direction, s21::s21_controller::Left);
}

TEST(s21_ControllerTest, case10) {
  s21::s21_controller ctrl;
  bool hold = false;
  ctrl.direction = s21::s21_controller::Right;

  ctrl.userInput(s21::s21_controller::Right, &hold);

  EXPECT_TRUE(hold);
}

TEST(s21_ControllerTest, case11) {
  s21::s21_controller ctrl;
  bool hold = false;
  ctrl.direction = s21::s21_controller::Down;

  ctrl.userInput(s21::s21_controller::Down, &hold);

  EXPECT_TRUE(hold);
}

TEST(s21_ControllerTest, case12) {
  s21::s21_controller ctrl;
  bool hold = false;
  ctrl.direction = s21::s21_controller::Up;

  ctrl.userInput(s21::s21_controller::Up, &hold);

  EXPECT_TRUE(hold);
}

TEST(s21_ControllerTest, case13) {
  s21::s21_controller ctrl;
  bool hold = false;
  ctrl.direction = s21::s21_controller::Left;

  ctrl.userInput(s21::s21_controller::Left, &hold);

  EXPECT_TRUE(hold);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}