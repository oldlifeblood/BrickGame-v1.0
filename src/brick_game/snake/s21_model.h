#ifndef S21_MODEL_H
#define S21_MODEL_H

/**
 * @file s21_model.h
 *
 * @brief Определение класса модели.
 */

#include <fstream>
#include <iostream>

#include "s21_controller.h"

#define WIDTH 10
#define HEIGHT 20

namespace s21 {
/**
 * @class s21_model
 * @brief Класс модели для управления игрой.
 */
class s21_model {
 public:
  /**
   * @brief Конструктор с указателем на контроллер.
   * @param ctrl Указатель на объект s21_controller.
   */
  s21_model(s21_controller *ctrl);
  ~s21_model();

  /**
   * @struct GameInfo_t
   * @brief Структура содержащая информацию об игре.
   */
  typedef struct {
    int **field;    /**< Поле игры */
    int **next;     /**< Следующий элемент */
    int score;      /**< Текущий счет */
    int high_score; /**< Рекордный счет */
    int level;      /**< Уровень игры */
    int speed;      /**< Скорость игры */
    int pause;      /**< Флаг паузы */
  } GameInfo_t;
  /**
   * @struct Snake
   * @brief Структура с состоянием змейки.
   */
  typedef struct {
    int **snake; /**< Координаты частей тела змейки */
    int xHead;   /**< Координата X головы змейки */
    int yHead;   /**< Координата Y головы змейки */
    int length;  /**< Длина змейки */
  } Snake;
  /**
   * @brief Инициализая игры.
   * @param game указатель на структуру GameInfo_t.
   * @param snake указатель на структуру Snake.
   */
  void initGame(GameInfo_t *game, Snake *snake);
  /**
   * @brief Перемещение змеи.
   * @param snake указатель на структуру Snake.
   */
  void moveSnake(Snake *snake);
  /**
   * @brief Метод для съедение фрукта.
   * @param game указатель на структуру GameInfo_t.
   * @param snake указатель на структуру Snake.
   */
  void eatFruit(GameInfo_t *game, Snake *snake);
  /**
   * @brief Запись рекорда.
   * @param snake указатель на структуру Snake.
   */
  int gameOverCheck(Snake *snake);
  /**
   * @brief Запись рекорда.
   * @param high_score переменная которая хранит лучший результат.
   */
  void writeHighScore(int high_score);
  /**
   * @brief Чтение рекорда.
   */
  int readHighScore();
  /**
   * @brief Метод создания нового фрукта.
   * @param game указатель на структуру GameInfo_t.
   * @param snake указатель на структуру Snake.
   */
  void newFruit(GameInfo_t *game, Snake *snake);
  /**
   * @brief Увеличение размера змеи.
   * @param snake указатель на структуру Snake.
   */
  void addBody(Snake *snake);
  /**
   * @brief Запись рекорда.
   * @param game указатель на структуру GameInfo_t.
   */
  void updateInfo(GameInfo_t *game);
  /**
   * @brief
   * @param snake указатель на структуру Snake.
   */
  bool isSnakeCell(Snake *snake, int x, int y);
  /**
   * @brief Победа игрока.
   * @param snake указатель на структуру Snake.
   */
  bool winGame(Snake snake);
  /**
   * @brief Освобождение памяти.
   * @param snake указатель на структуру Snake и указатель на структуру
   * GameInfo_t.
   */
  void free_memory(GameInfo_t *game, Snake *snake);

 private:
  s21_controller *control;
};
}  // namespace s21
#endif  // S21_MODEL_H
