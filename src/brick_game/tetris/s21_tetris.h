#ifndef TETRIS_H
#define TETRIS_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 10 ///< Ширина игрового поля
#define HEIGHT 20 ///< Высота игрового поля
#define BLOCK_SIZE 4 ///< Размер блока

/**
 * @brief Структура для хранения информации об игре.
 */
typedef struct {
    int **field; ///< Игровое поле
    int **next; ///< Следующий блок
    int score; ///< Текущий счет
    int high_score; ///< Рекордный счет
    int level; ///< Уровень игры
    int speed; ///< Скорость игры
    int pause; ///< Флаг паузы игры
} GameInfo_t;

/**
 * @brief Перечисление возможных действий пользователя.
 */
typedef enum {
    Start, ///< Начало игры
    Pause, ///< Пауза
    Terminate, ///< Завершение игры
    Left, ///< Движение влево
    Right, ///< Движение вправо
    Up, ///< Поворот блока
    Down, ///< Движение вниз
    Action ///< Действие (например, сброс блока)
} UserAction_t;

/**
 * @brief Структура для представления блока.
 */
typedef struct {
    int x, y; ///< Координаты блока
    int block[BLOCK_SIZE][BLOCK_SIZE]; ///< Матрица блока
} Block;

/**
 * @brief Освобождает память, выделенную для игрового поля.
 * 
 * @param game Указатель на структуру GameInfo_t.
 */
void free_memory(GameInfo_t *game);

/**
 * @brief Инициализирует новую игру.
 * 
 * @param game Указатель на структуру GameInfo_t.
 */
void initGame(GameInfo_t *game);

/**
 * @brief Обновляет текущее состояние игры, включая счет и уровень.
 * 
 * @param game Указатель на структуру GameInfo_t.
 * @param score Количество очков для добавления к текущему счету.
 * @return Обновленная структура GameInfo_t.
 */
GameInfo_t updateCurrentState(GameInfo_t *game, int score);

/**
 * @brief Генерирует новый блок.
 * 
 * @param block Указатель на структуру Block.
 */
void newBlock(Block *block);

/**
 * @brief Проверяет столкновение блока с границами игрового поля или другими блоками.
 * 
 * @param game Указатель на структуру GameInfo_t.
 * @param block Указатель на структуру Block.
 * @param y Координата y для проверки.
 * @param x Координата x для проверки.
 * @return 1 если есть столкновение, иначе 0.
 */
int checkCollision(GameInfo_t *game, Block *block, int y, int x);

/**
 * @brief Объединяет текущий блок с игровым полем.
 * 
 * @param game Указатель на структуру GameInfo_t.
 * @param block Указатель на структуру Block.
 */
void mergeBlock(GameInfo_t *game, Block *block);

/**
 * @brief Поворачивает блок.
 * 
 * @param block Указатель на структуру Block.
 * @param game Указатель на структуру GameInfo_t.
 * @param y Координата y для проверки.
 * @param x Координата x для проверки.
 */
void rotateBlock(Block *block, GameInfo_t *game, int y, int x);

/**
 * @brief Очищает заполненные линии на игровом поле.
 * 
 * @param game Указатель на структуру GameInfo_t.
 */
void clearLines(GameInfo_t *game);

/**
 * @brief Проверяет, окончена ли игра.
 * 
 * @param game Указатель на структуру GameInfo_t.
 * @return 1 если игра окончена, иначе 0.
 */
int gameOverCheck(GameInfo_t *game);

/**
 * @brief Обрабатывает ввод пользователя.
 * 
 * @param action Действие пользователя.
 * @param game Указатель на структуру GameInfo_t.
 * @param figure Указатель на текущий блок.
 * @param hold Флаг удержания кнопки.
 */
void userInput(UserAction_t action, GameInfo_t *game, Block *figure, bool hold);

/**
 * @brief Записывает рекордный счет в файл.
 * 
 * @param high_score Рекордный счет.
 */
void writeHighScore(int high_score);

/**
 * @brief Читает рекордный счет из файла.
 * 
 * @return Рекордный счет.
 */
int readHighScore();

#endif // TETRIS_H
