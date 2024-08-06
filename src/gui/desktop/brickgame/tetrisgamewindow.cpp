#include "tetrisgamewindow.h"
#include "ui_tetrisgamewindow.h"
namespace s21 {

TetrisGame::TetrisGame(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TetrisGame)
    , startOverlayLabel(new QLabel(this))
    , pauseOverlayLabel(nullptr)
    , offsetX(10)
    , offsetY(10)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    setFixedSize(700, 500);
    connect(ui->backButton, &QPushButton::clicked, this, &TetrisGame::on_backButton_clicked);
    connect(timer, &QTimer::timeout, this, &TetrisGame::moveBlockDown);
    showMessageToStart();
    initGame(&gameInfo);
}

TetrisGame::~TetrisGame()
{
    delete ui;
    if (pauseOverlayLabel) {
        delete pauseOverlayLabel;
    }
    delete startOverlayLabel;

    for (int i = 0; i < QT_HEIGHT; ++i) {
        delete[] gameInfo.field[i];
    }
    delete[] gameInfo.field;

    for (int i = 0; i < QT_BLOCK_SIZE; ++i) {
        delete[] gameInfo.next[i];
    }
    delete[] gameInfo.next;
}

void TetrisGame::keyPressEvent(QKeyEvent *event)
{
    if (startOverlayLabel && (event->key() == Qt::Key_S || event->key() == Qt::Key_Space)) {
        userInput(Start, false);
    } else if (event->key() == Qt::Key_P && !startOverlayLabel) {
        userInput(Pause, false);
    } else if (event->key() == Qt::Key_Right && gameOn) {
        userInput(Right, false);
    } else if (event->key() == Qt::Key_Left && gameOn) {
        userInput(Left, false);
    } else if (event->key() == Qt::Key_Up && gameOn) {
        userInput(Up, false);
    } else if (event->key() == Qt::Key_Down && gameOn) {
        userInput(Down, false);
    }
}

void TetrisGame::userInput(UserAction_t action, bool hold)
{
    Q_UNUSED(hold);
    switch (action) {
    case Start:
        if (startOverlayLabel) {
            startOverlayLabel->hide();
            startOverlayLabel->deleteLater();
            startOverlayLabel = nullptr;
            startGame();
        }
        break;
    case Pause:
        if (!pauseOverlayLabel) {
            pauseOverlayLabel = new QLabel(this);
            pauseOverlayLabel->setTextFormat(Qt::PlainText);
            pauseOverlayLabel->setText("PAUSE");
            pauseOverlayLabel->setStyleSheet(
                "color: white; background-color: rgba(0, 0, 0, 0); font-size: 24px;");
            pauseOverlayLabel->setGeometry(140, 100, 100, 50);
            pauseOverlayLabel->raise();
            pauseOverlayLabel->show();
            pauseGame();
        } else {
            pauseOverlayLabel->hide();
            pauseOverlayLabel->deleteLater();
            pauseOverlayLabel = nullptr;
            resumeGame();
        }
        break;
    case Terminate:
        gameOver();
        break;
    case Left:
        moveBlockLeft();
        break;
    case Right:
        moveBlockRight();
        break;
    case Up:
        rotateBlock();
        break;
    case Down:
        moveBlockDown();
        break;
    case Action:
        rotateBlock();
        if (canMoveBlock(currentBlock, currentBlock.x, currentBlock.y))
            rotateBlock();
        break;
    default:
        break;
    }
}

void TetrisGame::drawNextBlock(QPainter &painter)
{
    double newSize = 0.9;
    double nextBlockX = 17;
    double nextBlockY = 0.5;
    for (int y = 0; y < BLOCK_SIZE; ++y) {
        for (int x = 0; x < BLOCK_SIZE; ++x) {
            if (nextBlock.block[y][x]) {
                painter.fillRect(QRect((nextBlockX + x * newSize) * QT_BLOCK_SIZE + offsetX,
                                       (nextBlockY + y * newSize) * QT_BLOCK_SIZE + offsetY,
                                       QT_BLOCK_SIZE * newSize,
                                       QT_BLOCK_SIZE * newSize),
                                 Qt::red);
            }
        }
    }
}

void TetrisGame::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    drawBoard(painter);
    if (gameOn) {
        drawCurrentBlock(painter);
        drawNextBlock(painter);
    }
}

void TetrisGame::drawBoard(QPainter &painter)
{
    for (int y = 0; y < QT_HEIGHT; ++y) {
        for (int x = 0; x < QT_WIDTH; ++x) {
            if (gameInfo.field[y][x]) {
                painter.fillRect(QRect(x * QT_BLOCK_SIZE + offsetX,
                                       y * QT_BLOCK_SIZE + offsetY,
                                       QT_BLOCK_SIZE,
                                       QT_BLOCK_SIZE),
                                 Qt::blue);
            } else {
                painter.drawRect(QRect(x * QT_BLOCK_SIZE + offsetX,
                                       y * QT_BLOCK_SIZE + offsetY,
                                       QT_BLOCK_SIZE,
                                       QT_BLOCK_SIZE));
            }
        }
    }
    QPen originalPen = painter.pen();
    QPen pen(Qt::green);
    pen.setWidth(1);
    painter.setPen(pen);
    painter.drawRect(10, 10, 331, 481);
    painter.setPen(originalPen);
}

void TetrisGame::drawCurrentBlock(QPainter &painter)
{
    for (int y = 0; y < BLOCK_SIZE; ++y) {
        for (int x = 0; x < BLOCK_SIZE; ++x) {
            if (currentBlock.block[y][x]) {
                painter.fillRect(QRect((currentBlock.x + x) * QT_BLOCK_SIZE + offsetX,
                                       (currentBlock.y + y) * QT_BLOCK_SIZE + offsetY,
                                       QT_BLOCK_SIZE,
                                       QT_BLOCK_SIZE),
                                 Qt::red);
            }
        }
    }
}

void TetrisGame::newBlock(Block *block)
{
    static const int blocks[7][4][2] = {{{0, 1}, {1, 1}, {2, 1}, {3, 1}},
                                        {{0, 1}, {1, 1}, {2, 1}, {2, 0}},
                                        {{0, 1}, {1, 1}, {2, 1}, {2, 2}},
                                        {{1, 1}, {1, 2}, {2, 1}, {2, 2}},
                                        {{0, 2}, {1, 2}, {1, 1}, {2, 1}},
                                        {{0, 1}, {1, 1}, {2, 1}, {1, 2}},
                                        {{0, 1}, {1, 1}, {1, 2}, {2, 2}}};

    int type = std::rand() % 7;
    for (int i = 0; i < BLOCK_SIZE; ++i) {
        for (int j = 0; j < BLOCK_SIZE; ++j) {
            block->block[i][j] = 0;
        }
    }
    for (int i = 0; i < 4; ++i) {
        int x = blocks[type][i][0];
        int y = blocks[type][i][1];
        block->block[x][y] = 1;
    }
    block->x = QT_WIDTH / 2 - BLOCK_SIZE / 2;
    block->y = 0;
    nextBlock = *block;

    repaint();
}

void TetrisGame::moveBlockDown()
{
    if(gameInfo.level >= 10) {
        gameOver();
    }
    if (canMoveBlock(currentBlock, 0, 1)) {
        currentBlock.y += 1;
    } else {
        placeBlock();
        currentBlock = nextBlock;
        newBlock(&nextBlock);
        checkGameOver();
    }
    repaint();
}

void TetrisGame::rotateBlock()
{
    Block tempBlock = currentBlock;
    for (int i = 0; i < BLOCK_SIZE; ++i) {
        for (int j = 0; j < BLOCK_SIZE; ++j) {
            tempBlock.block[i][j] = currentBlock.block[BLOCK_SIZE - j - 1][i];
        }
    }
    if (canMoveBlock(tempBlock, 0, 0)) {
        currentBlock = tempBlock;
        repaint();
    }
}

void TetrisGame::moveBlockLeft()
{
    if (canMoveBlock(currentBlock, -1, 0)) {
        currentBlock.x -= 1;
        repaint();
    }
}

void TetrisGame::moveBlockRight()
{
    if (canMoveBlock(currentBlock, 1, 0)) {
        currentBlock.x += 1;
        repaint();
    }
}

bool TetrisGame::canMoveBlock(const Block &block, int dx, int dy)
{
    for (int y = 0; y < BLOCK_SIZE; ++y) {
        for (int x = 0; x < BLOCK_SIZE; ++x) {
            if (block.block[y][x]) {
                int newX = block.x + x + dx;
                int newY = block.y + y + dy;
                if (newX < 0 || newX >= QT_WIDTH || newY < 0 || newY >= QT_HEIGHT) {
                    return false;
                }
                if (gameInfo.field[newY][newX]) {
                    return false;
                }
            }
        }
    }
    return true;
}

void TetrisGame::placeBlock()
{
    for (int y = 0; y < BLOCK_SIZE; ++y) {
        for (int x = 0; x < BLOCK_SIZE; ++x) {
            if (currentBlock.block[y][x]) {
                gameInfo.field[currentBlock.y + y][currentBlock.x + x] = 1;
            }
        }
    }
    checkFullLines();
}

void TetrisGame::checkFullLines()
{
    int linesCleared = 0;
    for (int y = QT_HEIGHT - 1; y >= 0; --y) {
        bool fullLine = true;
        for (int x = 0; x < QT_WIDTH; ++x) {
            if (!gameInfo.field[y][x]) {
                fullLine = false;
                break;
            }
        }
        if (fullLine) {
            clearLine(y);
            moveLinesDown(y);
            linesCleared++;
            y++;
        }
    }
    scoringPoints(linesCleared);
}

void TetrisGame::scoringPoints(int linesCleared)
{
    switch (linesCleared) {
    case 1:
        gameInfo.score += 100;
        break;
    case 2:
        gameInfo.score += 300;
        break;
    case 3:
        gameInfo.score += 700;
        break;
    case 4:
        gameInfo.score += 1500;
        break;
    default:
        break;
    }
    ui->scoreDisplay->display(gameInfo.score);
    checkHighScore();
    levelUp();
}

void TetrisGame::checkHighScore()
{
    if (gameInfo.score > gameInfo.high_score) {
        writeHighScore(gameInfo.score);
    }
}

void TetrisGame::clearLine(int lineIndex)
{
    for (int x = 0; x < QT_WIDTH; ++x) {
        gameInfo.field[lineIndex][x] = 0;
    }
}

void TetrisGame::moveLinesDown(int startY)
{
    for (int y = startY; y > 0; --y) {
        for (int x = 0; x < QT_WIDTH; ++x) {
            gameInfo.field[y][x] = gameInfo.field[y - 1][x];
        }
    }
    for (int x = 0; x < QT_WIDTH; ++x) {
        gameInfo.field[0][x] = 0;
    }
    clearLine(0);
}

void TetrisGame::checkGameOver()
{
    for (int x = 0; x < QT_WIDTH; ++x) {
        if (gameInfo.field[0][x] == 1) {
            userInput(Terminate, false);
        }
    }
}

void TetrisGame::gameOver()
{
    gameOn = false;
    ui->scoreDisplay->display(0);
    timer->stop();
    clearGameField();
    initGame(&gameInfo);
    showMessageToStart();
}

void TetrisGame::clearGameField()
{
    for (int y = 0; y < QT_HEIGHT; ++y) {
        for (int x = 0; x < QT_WIDTH; ++x) {
            gameInfo.field[y][x] = 0;
        }
    }
}

void TetrisGame::showMessageToStart()
{
    startOverlayLabel = new QLabel(this);
    startOverlayLabel->setTextFormat(Qt::PlainText);
    startOverlayLabel->setText("Press 'S' or 'Space'\nto start");
    startOverlayLabel->setStyleSheet(
        "color: white; background-color: rgba(0, 0, 0, 0); font-size: 24px;");
    startOverlayLabel->setGeometry(65, 100, 400, 50);
    startOverlayLabel->raise();
    startOverlayLabel->show();
}

void TetrisGame::startGame()
{
    gameOn = true;
    timer->start(gameInfo.speed);
    repaint();
}

void TetrisGame::pauseGame()
{
    timer->stop();
    gameOn = false;
}

void TetrisGame::resumeGame()
{
    timer->start(gameInfo.speed);
    gameOn = true;
}

void TetrisGame::initGame(GameInfo_t *game)
{
    game->field = new int *[QT_HEIGHT];
    for (int i = 0; i < QT_HEIGHT; ++i) {
        game->field[i] = new int[QT_WIDTH]();
    }
    game->next = new int *[QT_BLOCK_SIZE];
    for (int i = 0; i < QT_BLOCK_SIZE; ++i) {
        game->next[i] = new int[QT_BLOCK_SIZE]();
    }
    game->score = 0;
    game->pause = 0;
    game->high_score = 0;
    levelUp();
    readHighScore();
    newBlock(&currentBlock);
    newBlock(&nextBlock);
}

void TetrisGame::writeHighScore(int high_score) {
    FILE *file = fopen("high_score_tetris.txt", "w");
    if (file != NULL) {
        fprintf(file, "%d", high_score);
        fclose(file);
    }
    readHighScore();
}

void TetrisGame::readHighScore() {
    int high_score = 0;
    FILE *file = fopen("high_score_tetris.txt", "r");
    if (file != NULL) {
        if (fscanf(file, "%d", &high_score) == 1) {
            fclose(file);
        }
        fclose(file);
    }
    gameInfo.high_score = high_score;
    ui->highScoreDisplay->display(high_score);
}

void TetrisGame::levelUp() {
    int newLevel = gameInfo.score / 600 + 1;
    if (newLevel != gameInfo.level) {
        gameInfo.level = newLevel;
        ui->levelDisplay->display(gameInfo.level);
        gameInfo.speed = std::max(1000 - (gameInfo.level - 1) * 100, 200);
        timer->setInterval(gameInfo.speed);
    }
}


void TetrisGame::on_backButton_clicked()
{
    emit backButtonClicked();
}
}
