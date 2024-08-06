#include "s21_view.h"

namespace s21 {
s21_View::s21_View()
    : gameType(GameType::None),
      holdKey(true),
      control(nullptr),
      snakeModel(nullptr),
      gameInfo(nullptr) {}

s21_View::~s21_View() {
  delete control;
  delete snakeModel;
  delete gameInfo;
  snakeModel->free_memory(
      reinterpret_cast<s21_model::GameInfo_t *>(&SnakeGameInfo), &snake);
  free_memory(&TetrisGameInfo);
}

void s21_View::setTerminalSize(int rows, int cols) {
  std::string command = "printf '\\e[8;" + std::to_string(rows) + ";" +
                        std::to_string(cols) + "t'";
  system(command.c_str());
}

void s21_View::initScreen() {
  setlocale(LC_ALL, "");
  initscr();
  setTerminalSize(42, 39);
  cbreak();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);
}

void s21_View::closeScreen() {
  clear();
  drawFrame();
  mvprintw(2, WIDTH * 2 + 2, "SCORE: 0");
  mvprintw(4, WIDTH * 2 + 2, "HIGH: 0");
  mvprintw(6, WIDTH * 2 + 2, "LEVEL: 0");
  mvprintw(8, WIDTH * 2 + 2, "SPEED: 0");
  mvprintw(29, 3, "┏━━┓┏━━━┳━━┳━━━┳┓┏━┓");
  mvprintw(30, 3, "┃┏┓┃┃┏━┓┣┫┣┫┏━┓┃┃┃┏┛");
  mvprintw(31, 3, "┃┗┛┗┫┗━┛┃┃┃┃┃╋┗┫┗┛┛");
  mvprintw(32, 3, "┃┏━┓┃┏┓┏┛┃┃┃┃╋┏┫┏┓┃");
  mvprintw(33, 3, "┃┗━┛┃┃┃┗┳┫┣┫┗━┛┃┃┃┗┓");
  mvprintw(34, 3, "┗━━━┻┛┗━┻━━┻━━━┻┛┗━┛");
  mvprintw(35, 15, "┏━━━┳━━━┳━┓┏━┳━━━┓");
  mvprintw(36, 15, "┃┏━┓┃┏━┓┃┃┗┛┃┃┏━━┛");
  mvprintw(37, 15, "┃┃╋┗┫┃╋┃┃┏┓┏┓┃┗━━┓");
  mvprintw(38, 15, "┃┃┏━┫┗━┛┃┃┃┃┃┃┏━━┛");
  mvprintw(39, 15, "┃┗┻━┃┏━┓┃┃┃┃┃┃┗━━┓");
  mvprintw(40, 15, "┗━━━┻┛╋┗┻┛┗┛┗┻━━━┛");
  mvprintw(5, 5, "┏━━┓");
  mvprintw(6, 5, "┃┏┓┃");
  mvprintw(7, 5, "┃┗┛┗┳┓╋┏┳━━┓");
  mvprintw(8, 5, "┃┏━┓┃┃╋┃┃┃━┫");
  mvprintw(9, 5, "┃┗━┛┃┗━┛┃┃━┫");
  mvprintw(10, 5, "┗━━━┻━┓┏┻━━┛");
  mvprintw(11, 5, "╋╋╋╋┏━┛┃");
  mvprintw(12, 5, "╋╋╋╋┗━━┛");
  refresh();
  napms(2000);
  endwin();
  exit(0);
}

void s21_View::startSnakeGame() {
  gameType = SnakeGame;
  control = new s21_controller();
  snakeModel = new s21_model(control);
  snakeModel->initGame(&SnakeGameInfo, &snake);
  gameInfo = reinterpret_cast<GameInfo_t *>(&SnakeGameInfo);
  holdKey = true;
}

void s21_View::startTetrisGame() {
  gameType = TetrisGame;
  initGame(&TetrisGameInfo);
  newBlock(&currentBlock);
  newBlock(&nextBlock);
  gameInfo = &TetrisGameInfo;
  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
      gameInfo->next[i][j] = nextBlock.block[i][j];
    }
  }
  holdKey = true;
}

void s21_View::drawFrame() {
  mvprintw(0, 0, "┏");
  for (int i = 0; i < WIDTH * 2; i++) printw("━");
  printw("┓");
  for (int i = WIDTH; i < WIDTH * 2 + 4; i++) printw("━");
  printw("┓");

  mvprintw(HEIGHT + 1, 0, "┗");
  for (int i = 0; i < WIDTH * 2; i++) printw("━");
  printw("┛");
  for (int i = WIDTH; i < WIDTH * 2 + 4; i++) printw("━");
  printw("┛");

  for (int y = 1; y <= HEIGHT * 2; y++) {
    mvprintw(y, 0, "┃");
    mvprintw(y, WIDTH * 3 + 6, "┃");
  }
  mvprintw(HEIGHT * 2 + 1, 0, "┗");
  for (int i = 0; i < WIDTH * 3 + 5; i++) printw("━");
  printw("┛");

  for (int y = 1; y <= HEIGHT; y++) mvprintw(y, WIDTH * 2 + 1, "┃");

  mvprintw(25, 30, "▲");
  mvprintw(27, 27, "◄     ►");
  mvprintw(29, 30, "▼");
  mvprintw(25, 5, "🅟     🅜     🅢");
  mvprintw(26, 3, "𝙋𝙖𝙪𝙨𝙚  𝙈𝙚𝙣𝙪  𝙎𝙩𝙖𝙧𝙩");
}

void s21_View::decor_t() {
  mvprintw(2, WIDTH * 2 + 2, "SCORE: %d", gameInfo->score);
  mvprintw(4, WIDTH * 2 + 2, "HIGH: %d", gameInfo->high_score);
  mvprintw(7, WIDTH * 2 + 2, "NEXT: ");
  mvprintw(10, WIDTH * 2 + 2, "LEVEL: %d", gameInfo->level);
  mvprintw(12, WIDTH * 2 + 2, "SPEED: %d", gameInfo->level);
  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
      if (gameInfo->next[i][j] == 1)
        mvprintw(i + 6, j * 2 + WIDTH * 2 + 8, "▣ ");
    }
  }
  mvprintw(35, 2, "▀▀█▀▀ ░█▀▀▀ ▀▀█▀▀ ░█▀▀█ ▀█▀ ░█▀▀█");
  mvprintw(36, 2, "─░█── ░█▀▀▀ ─░█── ░█▄▄▀ ░█─ ─▀▀▄▄");
  mvprintw(37, 2, "─░█── ░█▄▄▄ ─░█── ░█─░█ ▄█▄ ░█▄▄█");
}

void s21_View::decor_s() {
  mvprintw(2, WIDTH * 2 + 2, "SCORE: %d", gameInfo->score);
  mvprintw(4, WIDTH * 2 + 2, "HIGH: %d", gameInfo->high_score);
  mvprintw(6, WIDTH * 2 + 2, "LEVEL: %d", gameInfo->level);
  mvprintw(8, WIDTH * 2 + 2, "SPEED: %d", gameInfo->level);
  mvprintw(35, 3, "░█▀▀▀█ ░█▄─░█ ─█▀▀█ ░█─▄▀ ░█▀▀▀");
  mvprintw(36, 3, "─▀▀▀▄▄ ░█░█░█ ░█▄▄█ ░█▀▄─ ░█▀▀▀");
  mvprintw(37, 3, "░█▄▄▄█ ░█──▀█ ░█─░█ ░█─░█ ░█▄▄▄");
}

void s21_View::drawGame() {
  clear();
  drawFrame();
  if (gameType == TetrisGame)
    decor_t();
  else
    decor_s();
  if (gameType == SnakeGame) {
    if (snakeModel->gameOverCheck(&snake) || snakeModel->winGame(snake)) {
      gameOver();
      return;
    }
    for (int i = 0; i < HEIGHT; ++i) {
      for (int j = 0; j < WIDTH; ++j) {
        if (gameInfo->field[i][j] == 1) {
          mvprintw(i + 1, j * 2 + 1, " ▣");
        } else if (gameInfo->field[i][j] == 2) {
          mvprintw(i + 1, j * 2 + 1, " ◉");
        }
      }
    }
    mvprintw(snake.yHead + 1, snake.xHead * 2 + 1, " ▣");
    for (int i = 1; i < snake.length; ++i) {
      mvprintw(snake.snake[i][1] + 1, snake.snake[i][0] * 2 + 1, " ▣");
    }
  } else if (gameType == TetrisGame) {
    if (gameOverCheck(gameInfo)) {
      gameOver();
      return;
    }
    for (int i = 0; i < HEIGHT; ++i) {
      for (int j = 0; j < WIDTH; ++j) {
        if (gameInfo->field[i][j] == 1) {
          mvprintw(i + 1, j * 2 + 1, " ▣");
        }
      }
    }
    for (int i = 0; i < BLOCK_SIZE; ++i) {
      for (int j = 0; j < BLOCK_SIZE; ++j) {
        if (currentBlock.block[i][j] == 1) {
          mvprintw(currentBlock.y + i + 1, (currentBlock.x + j) * 2 + 1, " ▣");
        }
      }
    }
  }
  if (gameInfo->pause) {
    mvprintw(18, WIDTH * 2 + 6, "PAUSE");
  }

  refresh();
}

void s21_View::handleInput(int key) {
  s21_controller::UserAction_t s_action;
  switch (key) {
    case KEY_LEFT:
      action = Left;
      s_action = s21_controller::Left;
      break;
    case KEY_RIGHT:
      action = Right;
      s_action = s21_controller::Right;
      break;
    case KEY_UP:
      action = Up;
      s_action = s21_controller::Up;
      break;
    case KEY_DOWN:
      action = Down;
      s_action = s21_controller::Down;
      break;
    case 'm':
      action = Terminate;
      s_action = s21_controller::Terminate;
      break;
    case 'p':
      action = Pause;
      s_action = s21_controller::Pause;
      break;
    default:
      return;
      break;
  }

  if (gameType == SnakeGame) {
    control->userInput(s_action, &holdKey);
  } else if (gameType == TetrisGame) {
    userInput(action, gameInfo, &currentBlock, holdKey);
  }
}

void s21_View::updateGame() {
  int interval = getGameInfo()->speed;
  struct timespec sp_start, sp_end, ts1, ts2 = {0, 0};
  if (gameType == SnakeGame) {
    if (!gameInfo->pause && !snakeModel->gameOverCheck(&snake)) {
      snakeModel->moveSnake(&snake);
      snakeModel->eatFruit(reinterpret_cast<s21_model::GameInfo_t *>(gameInfo),
                           &snake);
      if (holdKey) {
        interval /= 2;
        holdKey = false;
      }
    }
    gameInfo->pause = control->pause;
  } else if (gameType == TetrisGame) {
    if (!gameInfo->pause && !gameOverCheck(gameInfo)) {
      clock_gettime(CLOCK_MONOTONIC, &sp_start);
      if (checkCollision(gameInfo, &currentBlock, currentBlock.y + 1,
                         currentBlock.x)) {
        mergeBlock(gameInfo, &currentBlock);
        clearLines(gameInfo);
        currentBlock = nextBlock;
        newBlock(&nextBlock);
        for (int i = 0; i < BLOCK_SIZE; i++) {
          for (int j = 0; j < BLOCK_SIZE; j++) {
            gameInfo->next[i][j] = nextBlock.block[i][j];
          }
        }
      } else {
        currentBlock.y++;
      }
    }
    clock_gettime(CLOCK_MONOTONIC, &sp_end);
  }
  drawGame();
  if (gameType == SnakeGame)
    usleep(interval);
  else {
    if (sp_end.tv_sec - sp_start.tv_sec <= 0 &&
        (ts2.tv_nsec = gameInfo->speed - (sp_end.tv_nsec - sp_start.tv_nsec)) >
            0) {
      nanosleep(&ts2, &ts1);
    }
  }
}

void s21_View::gameOver() {
  clear();
  drawFrame();
  if (gameType == SnakeGame)
    decor_s();
  else
    decor_t();
  if (snakeModel->winGame(snake))
    mvprintw(9, 6, "𝗬𝗢𝗨 𝗪𝗜𝗡");
  else
    mvprintw(9, 6, "𝗚𝗮𝗺𝗲 𝗢𝘃𝗲𝗿");
  refresh();
  napms(2000);
  preview();
}

void s21_View::terminate() {
  closeScreen();
  exit(0);
}

GameInfo_t *s21_View::getGameInfo() const { return gameInfo; }

bool s21_View::checkGameOver() {
  if (gameType == TetrisGame) {
    return gameOverCheck(gameInfo);
  } else if (gameType == SnakeGame) {
    return snakeModel->gameOverCheck(&snake);
  }
  return false;
}

void s21_View::preview() {
  clear();
  drawFrame();
  mvprintw(2, WIDTH * 2 + 2, "SCORE: 0");
  mvprintw(4, WIDTH * 2 + 2, "HIGH: 0");
  mvprintw(6, WIDTH * 2 + 2, "LEVEL: 0");
  mvprintw(8, WIDTH * 2 + 2, "SPEED: 0");
  mvprintw(29, 3, "┏━━┓┏━━━┳━━┳━━━┳┓┏━┓");
  mvprintw(30, 3, "┃┏┓┃┃┏━┓┣┫┣┫┏━┓┃┃┃┏┛");
  mvprintw(31, 3, "┃┗┛┗┫┗━┛┃┃┃┃┃╋┗┫┗┛┛");
  mvprintw(32, 3, "┃┏━┓┃┏┓┏┛┃┃┃┃╋┏┫┏┓┃");
  mvprintw(33, 3, "┃┗━┛┃┃┃┗┳┫┣┫┗━┛┃┃┃┗┓");
  mvprintw(34, 3, "┗━━━┻┛┗━┻━━┻━━━┻┛┗━┛");
  mvprintw(35, 15, "┏━━━┳━━━┳━┓┏━┳━━━┓");
  mvprintw(36, 15, "┃┏━┓┃┏━┓┃┃┗┛┃┃┏━━┛");
  mvprintw(37, 15, "┃┃╋┗┫┃╋┃┃┏┓┏┓┃┗━━┓");
  mvprintw(38, 15, "┃┃┏━┫┗━┛┃┃┃┃┃┃┏━━┛");
  mvprintw(39, 15, "┃┗┻━┃┏━┓┃┃┃┃┃┃┗━━┓");
  mvprintw(40, 15, "┗━━━┻┛╋┗┻┛┗┛┗┻━━━┛");
  mvprintw(7, 5, "𝐒𝐞𝐥𝐞𝐜𝐭 𝐠𝐚𝐦𝐞:");
  mvprintw(9, 5, "1. 𝚃𝙴𝚃𝚁𝙸𝚂");
  mvprintw(10, 5, "2. 𝑺𝑵𝑨𝑲𝑬");
  mvprintw(13, 4, "'q' - EXIT");

  refresh();
}

}  // namespace s21
