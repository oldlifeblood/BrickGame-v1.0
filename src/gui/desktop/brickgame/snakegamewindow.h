#ifndef SNAKEGAMEWINDOW_H
#define SNAKEGAMEWINDOW_H

#include <QDialog>
#include <QTimer>
#include <cstdlib>
#include <QPainter>
#include <QKeyEvent>
#include <utility>
#include <QLabel>

/**
 * @file snakegamewindow.h
 *
 * @brief Определение игры Snake.
 */

namespace Ui {
class SnakeGame;
}

namespace s21 {

/**
 * @brief Перечисление для пользовательских действий в игре.
 */
typedef enum {
    Start, /**< Начать игру. */
    Pause, /**< Поставить игру на паузу. */
    Terminate, /**< Завершить игру. */
    Left, /**< Переместить змейку влево. */
    Right, /**< Переместить змейку вправо. */
    Up, /**< Переместить змейку вверх. */
    Down, /**< Переместить змейку вниз. */
    Action /**< Действие (для обобщенных действий). */
} UserAction_t;

/**
 * @brief Структура, хранящая информацию об игре Змейка.
 */
typedef struct GameInfo_t{
    std::vector<std::vector<int>> field; /**< Игровое поле. */
    int score; /**< Текущий счет. */
    int high_score; /**< Рекордный счет. */
    int level; /**< Текущий уровень игры. */
    int speed; /**< Скорость игры. */
    bool gameOver = false; /**< Флаг окончания игры. */
} GameInfo_t;

/**
 * @brief Структура, представляющая змейку.
 */
struct Snake {
    std::vector<std::pair<int, int>> body; /**< Тело змейки в виде вектора пар (x, y). */
    int xHead; /**< Координата X головы змейки. */
    int yHead; /**< Координата Y головы змейки. */
    int length; /**< Длина змейки. */
    UserAction_t direction; /**< Направление движения змейки. */
};

/**
 * @brief Структура, представляющая еду для змейки.
 */
struct Food
{
    int x; /**< Координата X еды. */
    int y; /**< Координата Y еды. */
};

/**
 * @brief Класс контроллера для управления змейкой.
 */
class SnakeController {
public:
    /**
     * @brief Обрабатывает пользовательский ввод.
     * @param action Действие пользователя.
     * @param hold Флаг, указывающий, удерживается ли действие.
     */
    void userInput(UserAction_t action, bool hold);

    /**
     * @brief Обрабатывает событие нажатия клавиши.
     * @param event Событие клавиатуры.
     */
    void keyPressEvent(QKeyEvent *event);

    /**
     * @brief Обрабатывает событие отпускания клавиши.
     * @param event Событие клавиатуры.
     */
    void keyReleaseEvent(QKeyEvent *event);

    /**
     * @brief Проверяет, нажата ли определенная клавиша.
     * @param action Действие, соответствующее клавише.
     * @return True, если клавиша нажата, иначе false.
     */
    bool isKeyPressed(UserAction_t action) const;

private:
    bool keys[8] = {false}; /**< Массив состояний клавиш. */
};
/**
 * @brief Класс модели для игры Змейка.
 */
class SnakeModel {
public:
    /**
     * @brief Конструктор класса SnakeModel.
     * @param controller Ссылка на контроллер змейки.
     */
    SnakeModel(SnakeController &controller);

    /**
     * @brief Инициализирует игру Змейка.
     */
    void initGame();

    /**
     * @brief Обрабатывает движение змейки по игровому полю.
     */
    void moveSnake();

    /**
     * @brief Возвращает длину змейки.
     * @return Длина змейки.
     */
    int returnLength();

    /**
     * @brief Возвращает ссылку на объект змейки.
     * @return Ссылка на объект змейки.
     */
    Snake& getSnake();

    /**
     * @brief Возвращает информацию об игре.
     * @return Константная ссылка на структуру GameInfo_t.
     */
    const GameInfo_t& getGameInfo() const;

    /**
     * @brief Возвращает текущее действие пользователя.
     * @return Константная ссылка на перечисление UserAction_t.
     */
    const UserAction_t& getUserAction() const;

    /**
     * @brief Возвращает координаты еды на игровом поле.
     * @return Константная ссылка на структуру Food.
     */
    const Food& getFood() const;

    /**
     * @brief Проверяет, съела ли змейка еду.
     */
    void checkEatFood();

    /**
     * @brief Повышает уровень игры в зависимости от текущего счета.
     */
    void levelUp();

    /**
     * @brief Считывает рекордный счет из файла.
     * @return Рекордный счет.
     */
    int readHighScore();

    /**
     * @brief Записывает рекордный счет в файл.
     * @param high_score Рекордный счет для записи.
     */
    void writeHighScore(int high_score);

private:
    SnakeController &controller; /**< Ссылка на контроллер змейки. */
    Snake snake; /**< Объект змейки. */
    GameInfo_t gameInfo; /**< Информация об игре. */
    UserAction_t userAction; /**< Действие пользователя. */
    Food food; /**< Еда на игровом поле. */
    int numRows; /**< Количество строк на игровом поле. */
    int numCols; /**< Количество столбцов на игровом поле. */
    int fieldWidth = 300; /**< Ширина игрового поля. */
    int fieldHeight = 300; /**< Высота игрового поля. */

    /**
     * @brief Размещает еду на игровом поле.
     */
    void placeFood();
};
/**
 * @brief Класс, представляющий окно игры Змейка.
 */
class SnakeGame: public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Конструктор класса SnakeGame.
     * @param parent Родительский виджет, по умолчанию nullptr.
     */
    explicit SnakeGame(QWidget *parent = nullptr);

    /**
     * @brief Деструктор класса SnakeGame.
     */
    ~SnakeGame();

protected:
    /**
     * @brief Обрабатывает событие рисования на виджете.
     * @param event Событие рисования.
     */
    void paintEvent(QPaintEvent *);

    /**
     * @brief Обрабатывает событие нажатия клавиши.
     * @param event Событие клавиатуры.
     */
    void keyPressEvent(QKeyEvent *event);

    /**
     * @brief Обрабатывает событие отпускания клавиши.
     * @param event Событие клавиатуры.
     */
    void keyReleaseEvent(QKeyEvent *event);

signals:
    /**
     * @brief Сигнал, испускаемый при необходимости показать второе окно.
     */
    void secondWindow();

    /**
     * @brief Сигнал, испускаемый при нажатии кнопки "назад".
     */
    void backButtonClicked();

private slots:
    /**
     * @brief Слот для обработки нажатия кнопки "назад".
     */
    void on_backButton_clicked();

private:
    Ui::SnakeGame *ui; /**< Указатель на компоненты пользовательского интерфейса. */
    SnakeController controller; /**< Контроллер змейки. */
    SnakeModel snakeModel; /**< Модель змейки. */
    QTimer *timer; /**< Таймер для обновления игрового экрана. */
    QLabel *overlayLabel; /**< Окно сообщения. */
    bool startGame = false; /**< Флаг начала игры. */
    bool win = false; /**< Флаг победы игрока. */
    bool pauseGame = false; /**< Флаг паузы игры. */

    /**
     * @brief Обновляет вид игры.
     */
    void updateView();

    /**
     * @brief Обрабатывает пользовательский ввод.
     */
    void handleInput();

    /**
     * @brief Обновляет пользовательский интерфейс на основе информации об игре.
     * @param gameInfo Информация об игре.
     */
    void updateUI(const GameInfo_t& gameInfo);

    /**
     * @brief Инициализирует игру.
     */
    void initGame();

    /**
     * @brief Завершает текущую игру.
     */
    void gameTerminate();

    /**
     * @brief Отображает сообщение на экране.
     * @param message Сообщение для отображения.
     */
    void showMessage(const QString &message);

    /**
     * @brief Скрывает отображенное сообщение.
     */
    void hideMessage();
};
}
#endif