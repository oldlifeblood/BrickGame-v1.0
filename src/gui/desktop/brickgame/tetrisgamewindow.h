#ifndef TETRISGAMEWINDOW_H
#define TETRISGAMEWINDOW_H

#define QT_WIDTH 11
#define QT_HEIGHT 16
#define QT_BLOCK_SIZE 30

#include <QDialog>
#include <cstdlib>
#include <QKeyEvent>
#include <QLabel>
#include <QPainter>
#include <QTimer>
#include "../../../brick_game/tetris/s21_tetris.h"

/**
 * @file tetrisgamewindow.h
 *
 * @brief Определение игры tetris.
 */

namespace Ui {
class TetrisGame;
}

namespace s21 {

/**
 * @brief Класс TetrisGame представляет главное окно игры Тетрис.
 */
class TetrisGame : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Конструктор класса TetrisGame.
     * @param parent Родительский виджет, по умолчанию nullptr.
     */
    explicit TetrisGame(QWidget *parent = nullptr);

    /**
     * @brief Деструктор класса TetrisGame.
     */
    ~TetrisGame();

    /**
     * @brief Начинает игру Тетрис.
     */
    void startGame();

    /**
     * @brief Ставит игру Тетрис на паузу.
     */
    void pauseGame();

    /**
     * @brief Возобновляет игру Тетрис после паузы.
     */
    void resumeGame();

protected:
    /**
     * @brief Обрабатывает события нажатия клавиш.
     * @param event Событие клавиатуры.
     */
    void keyPressEvent(QKeyEvent *event) override;

    /**
     * @brief Обрабатывает события рисования.
     */
    void paintEvent(QPaintEvent *) override;

private slots:
    /**
     * @brief Слот для обработки нажатия кнопки "назад".
     */
    void on_backButton_clicked();

signals:
    /**
     * @brief Сигнал, испускаемый при необходимости показать первое окно.
     */
    void firstWindow();

    /**
     * @brief Сигнал, испускаемый при нажатии кнопки "назад".
     */
    void backButtonClicked();

private:
    Ui::TetrisGame *ui; /**< Указатель на UI компоненты. */
    QLabel *startOverlayLabel; /**< Метка для стартового наложения. */
    QLabel *pauseOverlayLabel; /**< Метка для наложения паузы. */
    QTimer *timer; /**< Таймер для игровых событий. */
    GameInfo_t gameInfo; /**< Структура, содержащая информацию об игре. */
    Block currentBlock; /**< Текущий падающий блок. */
    Block nextBlock; /**< Следующий блок, который появится. */
    int offsetX; /**< Смещение по X для рисования игрового поля. */
    int offsetY; /**< Смещение по Y для рисования игрового поля. */
    int linesCleared = 0; /**< Количество убранных линий в игре. */
    bool gameOn = false; /**< Флаг, указывающий, идет ли игра. */

    /**
     * @brief Инициализирует игру.
     * @param game Указатель на структуру GameInfo_t.
     */
    void initGame(GameInfo_t *game);

    /**
     * @brief Обрабатывает ввод пользователя.
     * @param action Действие пользователя.
     * @param hold Флаг, указывающий, удерживается ли действие.
     */
    void userInput(UserAction_t action, bool hold);

    /**
     * @brief Рисует текущий блок.
     * @param painter Ссылка на объект QPainter.
     */
    void drawCurrentBlock(QPainter &painter);

    /**
     * @brief Рисует следующий блок.
     * @param painter Ссылка на объект QPainter.
     */
    void drawNextBlock(QPainter &painter);

    /**
     * @brief Генерирует новый блок.
     * @param block Указатель на блок, который нужно сгенерировать.
     */
    void newBlock(Block *block);

    /**
     * @brief Рисует игровое поле.
     * @param painter Ссылка на объект QPainter.
     */
    void drawBoard(QPainter &painter);

    /**
     * @brief Перемещает текущий блок вниз на одну единицу.
     */
    void moveBlockDown();

    /**
     * @brief Проверяет, может ли блок переместиться на новую позицию.
     * @param block Блок для проверки.
     * @param dx Изменение позиции по X.
     * @param dy Изменение позиции по Y.
     * @return True, если блок может переместиться, иначе false.
     */
    bool canMoveBlock(const Block &block, int dx, int dy);

    /**
     * @brief Устанавливает текущий блок на игровое поле.
     */
    void placeBlock();

    /**
     * @brief Поворачивает текущий блок.
     */
    void rotateBlock();

    /**
     * @brief Перемещает текущий блок влево.
     */
    void moveBlockLeft();

    /**
     * @brief Перемещает текущий блок вправо.
     */
    void moveBlockRight();

    /**
     * @brief Проверяет и очищает полные линии на игровом поле.
     */
    void checkFullLines();

    /**
     * @brief Очищает конкретную линию на игровом поле.
     * @param lineIndex Индекс линии для очистки.
     */
    void clearLine(int lineIndex);

    /**
     * @brief Перемещает линии вниз, начиная с конкретной линии.
     * @param startY Начальный индекс линии.
     */
    void moveLinesDown(int startY);

    /**
     * @brief Проверяет, закончилась ли игра.
     */
    void checkGameOver();

    /**
     * @brief Обрабатывает логику окончания игры.
     */
    void gameOver();

    /**
     * @brief Очищает игровое поле.
     */
    void clearGameField();

    /**
     * @brief Показывает сообщение о начале игры.
     */
    void showMessageToStart();

    /**
     * @brief Записывает рекордный счет в файл.
     * @param high_score Рекордный счет для записи.
     */
    void writeHighScore(int high_score);

    /**
     * @brief Считывает рекордный счет из файла.
     */
    void readHighScore();

    /**
     * @brief Проверяет, является ли текущий счет новым рекордом.
     */
    void checkHighScore();

    /**
     * @brief Обновляет счет в зависимости от количества убранных линий.
     * @param linesCleared Количество убранных линий.
     */
    void scoringPoints(int linesCleared);

    /**
     * @brief Повышает уровень игры в зависимости от текущего счета.
     */
    void levelUp();
};

} // namespace s21

#endif // TETRISGAMEWINDOW_H