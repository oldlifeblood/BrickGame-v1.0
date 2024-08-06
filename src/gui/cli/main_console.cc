#include "s21_view.h"

/**
 *
 * @file main_console.cc
 *
 * @brief main функция для запуска консольной версии игр.
 *
 */

int main() {
  s21::s21_View game;
  game.initScreen();
  int exit = 0;
  while (1) {
    game.preview();
    int k = 0;
    while (k != '1' && k != '2' && k != 'q') k = getch();
    if (k == '1')
      game.startTetrisGame();
    else if (k == '2')
      game.startSnakeGame();
    else if (k == 'q')
      game.closeScreen();
    nodelay(stdscr, true);
    int key;
    while ((key = getch()) != 'q') {
      game.handleInput(key);
      game.updateGame();
      if (game.checkGameOver()) break;
      if (game.getGameInfo()->pause)
        nodelay(stdscr, false);
      else
        nodelay(stdscr, true);
    }
  }
  return 0;
}
