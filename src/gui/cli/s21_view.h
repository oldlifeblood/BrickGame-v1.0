#ifndef S21_VIEW_H
#define S21_VIEW_H

/**
 * @file s21_view.h для консольной версии
 *
 * @brief Определение класса для вывода.
 */

#include <locale.h>
#include <ncurses.h>
#include <sys/ioctl.h>
#include <time.h>
#include <unistd.h>

#include <cstdlib>
#include <cstring>

#include "../../brick_game/snake/s21_controller.h"
#include "../../brick_game/snake/s21_model.h"
#include "../../brick_game/tetris/s21_tetris.h"

/**
 *
 * @brief Определение класса для пространства s21.
 */
namespace s21 {
class s21_View {
  /**
   *
   * @brief enum структура для определения какая игра запущена.
   */
  enum GameType { SnakeGame, TetrisGame, None };
  UserAction_t action = Start;

 public:
  s21_View();
  ~s21_View();
  /**
   * @brief Инициализация для запуска игры через lncurses.
   */
  void initScreen();
  /**
   * @brief Закрытие игры через lncurses.
   */
  void closeScreen();
  /**
   * @brief Запуск начальной заставки игр.
   */
  void preview();
  /**
   * @brief Запуск игры змейка.
   */
  void startSnakeGame();
  /**
   * @brief Запуск игры тетрис.
   */
  void startTetrisGame();
  /**
   * @brief Обновление кадров игры.
   */
  void updateGame();
  /**
   * @brief Обработка нажатых кнопок на клавиатуре.
   */
  void handleInput(int key);
  /**
   * @brief Отрисовка игры.
   */
  void drawGame();
  /**
   * @brief Отрисовка фреймов.
   */
  void drawFrame();
  /**
   * @brief Конец игры.
   */
  void gameOver();
  /**
   * @brief Выход из игры.
   */
  void terminate();
  /**
   * @brief Отрисовка игры.
   */
  void setTerminalSize(int rows, int cols);
  /**
   * @brief Отрисовка дизайнерской надписи snake.
   */
  void decor_s();
  /**
   * @brief Отрисовка дизайнерской надписи tetris.
   */
  void decor_t();
  /**
   * @brief Получение информации об игре(какой счет, какой уровень итд).
   */
  GameInfo_t *getGameInfo() const;
  /**
   * @brief Проверка на то что не закончилась ли игра.
   */
  bool checkGameOver();

 private:
  GameType gameType;
  GameInfo_t *gameInfo;
  GameInfo_t TetrisGameInfo;
  s21_model::GameInfo_t SnakeGameInfo;
  s21_model::Snake snake;
  Block currentBlock, nextBlock;
  bool holdKey;
  s21_controller *control;
  s21_model *snakeModel;
};

}  // namespace s21

#endif  // VIEW_H
