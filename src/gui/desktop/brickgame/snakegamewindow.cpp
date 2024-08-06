#include "snakegamewindow.h"
#include "ui_snakegamewindow.h"

namespace s21 {

SnakeGame::SnakeGame(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SnakeGame)
    , controller()
    , snakeModel(controller)
    , overlayLabel(new QLabel(this))
{
    ui->setupUi(this);
    timer = new QTimer(this);
    setFixedSize(700, 500);
    connect(ui->backButton, &QPushButton::clicked, this, &SnakeGame::on_backButton_clicked);
    connect(timer, &QTimer::timeout, this, &SnakeGame::updateView);
    overlayLabel->setTextFormat(Qt::PlainText);
    overlayLabel->setStyleSheet("color: white; background-color: rgba(0, 0, 0, 0); font-size: 24px;");
    overlayLabel->setGeometry(-47, 200, 400, 75);
    overlayLabel->setAlignment(Qt::AlignCenter);
    overlayLabel->raise();
    initGame();
}


SnakeGame::~SnakeGame() {
    delete ui;
}

void SnakeGame::on_backButton_clicked() {
    emit backButtonClicked();
}

void SnakeGame::paintEvent(QPaintEvent *) {
    QPainter painter(this);

    const auto& food = snakeModel.getFood();
    painter.setBrush(Qt::red);
    painter.setPen(Qt::red);
    painter.drawRect(food.x + 10, food.y + 90, 10, 10);

    painter.setBrush(Qt::NoBrush);
    painter.setPen(Qt::green);
    painter.drawRect(10, 90, 300, 300);

    painter.setBrush(Qt::green);
    const auto& snake = snakeModel.getSnake();
    for (const auto& segment : snake.body) {
        painter.drawRect(segment.first + 10, segment.second + 90, 10, 10);
    }

    const auto& gameInfo = snakeModel.getGameInfo();
    for (size_t y = 0; y < gameInfo.field.size(); ++y) {
        for (size_t x = 0; x < gameInfo.field[y].size(); ++x) {
            if (gameInfo.field[y][x] == 1) {
                painter.setBrush(Qt::green);
                painter.drawRect(x * 10 + 10, y * 10 + 90, 10, 10);
            }
        }
    }
}

void SnakeGame::keyPressEvent(QKeyEvent *event) {
    controller.keyPressEvent(event);
    if (!startGame || (controller.isKeyPressed(Right) ||
                       controller.isKeyPressed(Left) ||
                       controller.isKeyPressed(Up) ||
                       controller.isKeyPressed(Down))) {
        updateView();
    }
}

void SnakeGame::keyReleaseEvent(QKeyEvent *event) {
    controller.keyReleaseEvent(event);
}

void SnakeGame::updateView() {
    const auto& gameInfo = snakeModel.getGameInfo();
    handleInput();
    updateUI(gameInfo);
    if (startGame && !pauseGame && !gameInfo.gameOver && !win) {
        timer->start(gameInfo.speed);
        snakeModel.moveSnake();
    }
    update();
}

void SnakeGame::handleInput() {
    if (controller.isKeyPressed(Start) && !startGame) {
        hideMessage();
        startGame = true;
    } else if (controller.isKeyPressed(Pause) && startGame && !win && !snakeModel.getGameInfo().gameOver) {
        if (!pauseGame) {
            showMessage("Pause");
            timer->stop();
            pauseGame = true;
        } else {
            hideMessage();
            pauseGame = false;
        }
    } else if(snakeModel.getGameInfo().gameOver) {
        showMessage("Game Over\nPress s or space\nto start");
        if (controller.isKeyPressed(Start)) {
            gameTerminate();
        }
    } else if(snakeModel.getGameInfo().level == 10) {
        showMessage("You win\nPress s or space\nto start");
        win = true;
        if (controller.isKeyPressed(Start)) {
            gameTerminate();
        }
    }
}

void SnakeGame::updateUI(const GameInfo_t& gameInfo) {
    ui->highScoreDisplay->display(gameInfo.high_score);
    ui->scoreDisplay->display(gameInfo.score);
    ui->levelDisplay->display(gameInfo.level);
}

void SnakeGame::initGame() {
    snakeModel.initGame();
    showMessage("Start\nPress s or space\nto start");
    updateView();
}

void SnakeGame::gameTerminate() {
    startGame = false;
    win = false;
    pauseGame = false;
    initGame();
}

void SnakeGame::showMessage(const QString &message) {
    overlayLabel->setText(message);
    overlayLabel->show();
}

void SnakeGame::hideMessage() {
    overlayLabel->hide();
}

void SnakeController::userInput(UserAction_t action, bool hold) {
    if (hold) {
        keys[action] = true;
    } else {
        keys[action] = false;
    }
}

void SnakeController::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_S:
    case Qt::Key_Space:
        userInput(Start, true);
        break;
    case Qt::Key_P:
        userInput(Pause, true);
        break;
    case Qt::Key_Right:
        userInput(Right, true);
        break;
    case Qt::Key_Left:
        userInput(Left, true);
        break;
    case Qt::Key_Up:
        userInput(Up, true);
        break;
    case Qt::Key_Down:
        userInput(Down, true);
        break;
    default:
        break;
    }
}

void SnakeController::keyReleaseEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_S:
    case Qt::Key_Space:
        userInput(Start, false);
        break;
    case Qt::Key_P:
        userInput(Pause, false);
        break;
    case Qt::Key_Right:
        userInput(Right, false);
        break;
    case Qt::Key_Left:
        userInput(Left, false);
        break;
    case Qt::Key_Up:
        userInput(Up, false);
        break;
    case Qt::Key_Down:
        userInput(Down, false);
        break;
    default:
        break;
    }
}

bool SnakeController::isKeyPressed(UserAction_t action) const {
    return keys[action];
}

SnakeModel::SnakeModel(SnakeController &controller) : controller(controller) {
}

void SnakeModel::initGame() {
    numRows = fieldHeight / 10;
    numCols = fieldWidth / 10;

    gameInfo.field.resize(numRows, std::vector<int>(numCols, 0));
    snake.xHead = 60;
    snake.yHead = 200;
    snake.length = 4;
    snake.direction = Right;

    snake.body.resize(snake.length, std::pair<int, int>(0, 0));
    for (int i = 0; i < snake.length; ++i) {
        snake.body[i].first = snake.xHead - i * 10;
        snake.body[i].second = snake.yHead;
    }
    placeFood();
    gameInfo.score = 0;
    gameInfo.high_score = readHighScore();
    gameInfo.level = 1;
    gameInfo.speed = 200;
    gameInfo.gameOver = false;
}

void SnakeModel::moveSnake() {
    if (controller.isKeyPressed(Right) && snake.direction != Left) {
        snake.direction = Right;
    } else if (controller.isKeyPressed(Left) && snake.direction != Right) {
        snake.direction = Left;
    } else if (controller.isKeyPressed(Up) && snake.direction != Down) {
        snake.direction = Up;
    } else if (controller.isKeyPressed(Down) && snake.direction != Up) {
        snake.direction = Down;
    }

    int newXHead = snake.xHead;
    int newYHead = snake.yHead;

    if (snake.direction == Right) {
        newXHead += 10;
    } else if (snake.direction == Left) {
        newXHead -= 10;
    } else if (snake.direction == Up) {
        newYHead -= 10;
    } else if (snake.direction == Down) {
        newYHead += 10;
    }

    if (newXHead < 0 || newXHead >= fieldWidth || newYHead < 0 || newYHead >= fieldHeight) {
        gameInfo.gameOver = true;
        return;
    }

    for (int i = 1; i < snake.length; ++i) {
        if (snake.body[i].first == newXHead && snake.body[i].second == newYHead) {
            gameInfo.gameOver = true;
            return;
        }
    }

    for (int i = snake.length - 1; i > 0; --i) {
        snake.body[i] = snake.body[i - 1];
    }

    snake.xHead = newXHead;
    snake.yHead = newYHead;
    snake.body[0].first = snake.xHead;
    snake.body[0].second = snake.yHead;
    checkEatFood();
}

int SnakeModel::returnLength() {
    return snake.length;
}

Snake& SnakeModel::getSnake() {
    return snake;
}

const GameInfo_t& SnakeModel::getGameInfo() const {
    return gameInfo;
}

const UserAction_t& SnakeModel::getUserAction() const {
    return userAction;
}

void SnakeModel::placeFood() {
    int margin = 10;
    int xMax = (fieldWidth - 2 * margin) / 10;
    int yMax = (fieldHeight - 2 * margin) / 10;

    bool foodOnSnake = true;

    while (foodOnSnake) {
        foodOnSnake = false;
        food.x = (rand() % xMax) * 10 + margin;
        food.y = (rand() % yMax) * 10 + margin;
        for (const auto& segment : snake.body) {
            if (segment.first == food.x && segment.second == food.y) {
                foodOnSnake = true;
                break;
            }
        }
    }
}

const Food& SnakeModel::getFood() const {
    return food;
}

void SnakeModel::checkEatFood() {
    if (snake.xHead == food.x && snake.yHead == food.y) {
        placeFood();
        snake.length++;
        snake.body.push_back(snake.body.back());
        gameInfo.score += 1;
    }
    if(gameInfo.high_score <= gameInfo.score) {
        gameInfo.high_score = gameInfo.score;
        writeHighScore(gameInfo.score);
    }
    levelUp();
}

void SnakeModel::levelUp() {
    int newLevel = gameInfo.score / 5 + 1;
    if (newLevel != gameInfo.level) {
        gameInfo.level = newLevel;
        gameInfo.speed -= 15;
    }
}

int SnakeModel::readHighScore() {
    int high_score = 0;
    FILE *file = fopen("high_score_snake.txt", "r");
    if (file != NULL) {
        if (fscanf(file, "%d", &high_score) == 1) {
            fclose(file);
            return high_score;
        }
        fclose(file);
    }
    return 0;
}

void SnakeModel::writeHighScore(int high_score) {
    FILE *file = fopen("high_score_snake.txt", "w");
    if (file != NULL) {
        fprintf(file, "%d", high_score);
        fclose(file);
    }
}

}
