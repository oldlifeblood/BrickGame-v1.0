#ifndef S21_CONTROLLER_H
#define S21_CONTROLLER_H

/**
 * @file s21_controller.h
 *
 * @brief Определение класса контроллера.
 */

namespace s21 {
/**
 * @class s21_controller
 * @brief Класс контроллера для обработки пользовательских действий в программе.
 */
class s21_controller {
 public:
  /**
   * @brief Конструктор по умолчанию.
   */
  s21_controller(){};

  /**
   * @brief Деструктор по умолчанию.
   */
  ~s21_controller() {}
  /**
   * @enum UserAction_t
   * @brief Перечисление возможных действий пользователя.
   */
  typedef enum {
    Start,     /**< Начало действия */
    Pause,     /**< Пауза */
    Terminate, /**< Завершение действия */
    Left,      /**< Действие влево */
    Right,     /**< Действие вправо */
    Up,        /**< Действие вверх */
    Down,      /**< Действие вниз */
    Action,    /**< Другое действие */
    None       /**< Без действия */
  } UserAction_t;

  UserAction_t direction;
  int pause = 0;
  /**
   * @brief Обрабатывает ввод пользователя.
   *
   * @param action Действие пользователя.
   * @param hold Указатель на флаг удержания действия.
   */
  void userInput(UserAction_t action, bool *hold);
};
}  // namespace s21

#endif  // S21_CONTROLLER_H
