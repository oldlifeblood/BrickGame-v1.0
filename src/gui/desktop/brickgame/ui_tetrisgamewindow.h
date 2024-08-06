/********************************************************************************
** Form generated from reading UI file 'tetrisgamewindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TETRISGAMEWINDOW_H
#define UI_TETRISGAMEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_TetrisGame
{
public:
    QHBoxLayout *horizontalLayout;
    QFrame *gameArea;
    QVBoxLayout *verticalLayout_gameArea;
    QVBoxLayout *verticalLayout_infoPanel;
    QLabel *nextPieceLabel;
    QHBoxLayout *horizontalLayout_3;
    QFrame *nextPieceDisplay;
    QVBoxLayout *verticalLayout_nextPieceDisplay;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label;
    QLCDNumber *levelDisplay;
    QLabel *scoreLabel;
    QHBoxLayout *horizontalLayout_score;
    QLCDNumber *scoreDisplay;
    QLabel *highScoreLabel;
    QHBoxLayout *horizontalLayout_highScore;
    QLCDNumber *highScoreDisplay;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *backButton;

    void setupUi(QDialog *TetrisGame)
    {
        if (TetrisGame->objectName().isEmpty())
            TetrisGame->setObjectName("TetrisGame");
        TetrisGame->resize(600, 425);
        TetrisGame->setStyleSheet(QString::fromUtf8("\n"
"    QDialog {\n"
"        background-color: #282828;\n"
"    }\n"
"   "));
        horizontalLayout = new QHBoxLayout(TetrisGame);
        horizontalLayout->setSpacing(10);
        horizontalLayout->setContentsMargins(10, 10, 10, 10);
        horizontalLayout->setObjectName("horizontalLayout");
        gameArea = new QFrame(TetrisGame);
        gameArea->setObjectName("gameArea");
        gameArea->setStyleSheet(QString::fromUtf8(""));
        gameArea->setFrameShape(QFrame::NoFrame);
        gameArea->setFrameShadow(QFrame::Plain);
        verticalLayout_gameArea = new QVBoxLayout(gameArea);
        verticalLayout_gameArea->setSpacing(10);
        verticalLayout_gameArea->setContentsMargins(10, 10, 10, 10);
        verticalLayout_gameArea->setObjectName("verticalLayout_gameArea");

        horizontalLayout->addWidget(gameArea);

        verticalLayout_infoPanel = new QVBoxLayout();
        verticalLayout_infoPanel->setSpacing(10);
        verticalLayout_infoPanel->setContentsMargins(10, 10, 10, 10);
        verticalLayout_infoPanel->setObjectName("verticalLayout_infoPanel");
        nextPieceLabel = new QLabel(TetrisGame);
        nextPieceLabel->setObjectName("nextPieceLabel");
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        nextPieceLabel->setFont(font);
        nextPieceLabel->setStyleSheet(QString::fromUtf8("\n"
"         QLabel {\n"
"             color: #ffffff;\n"
"         }\n"
"        "));

        verticalLayout_infoPanel->addWidget(nextPieceLabel);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        nextPieceDisplay = new QFrame(TetrisGame);
        nextPieceDisplay->setObjectName("nextPieceDisplay");
        nextPieceDisplay->setMinimumSize(QSize(80, 80));
        nextPieceDisplay->setStyleSheet(QString::fromUtf8("border:none;"));
        nextPieceDisplay->setFrameShape(QFrame::StyledPanel);
        nextPieceDisplay->setFrameShadow(QFrame::Sunken);
        verticalLayout_nextPieceDisplay = new QVBoxLayout(nextPieceDisplay);
        verticalLayout_nextPieceDisplay->setSpacing(10);
        verticalLayout_nextPieceDisplay->setContentsMargins(10, 10, 10, 10);
        verticalLayout_nextPieceDisplay->setObjectName("verticalLayout_nextPieceDisplay");

        horizontalLayout_3->addWidget(nextPieceDisplay);


        verticalLayout_infoPanel->addLayout(horizontalLayout_3);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        label = new QLabel(TetrisGame);
        label->setObjectName("label");
        QFont font1;
        font1.setBold(true);
        label->setFont(font1);
        label->setStyleSheet(QString::fromUtf8("\n"
"         QLabel {\n"
"             color: #ffffff;\n"
"         }\n"
"        "));

        horizontalLayout_5->addWidget(label);

        levelDisplay = new QLCDNumber(TetrisGame);
        levelDisplay->setObjectName("levelDisplay");
        levelDisplay->setStyleSheet(QString::fromUtf8("\n"
"QLCDNumber {\n"
"background-color: #000000;\n"
"color: #00ff00;\n"
"border: 2px solid #00ff00;\n"
"}\n"
""));

        horizontalLayout_5->addWidget(levelDisplay);


        verticalLayout_infoPanel->addLayout(horizontalLayout_5);

        scoreLabel = new QLabel(TetrisGame);
        scoreLabel->setObjectName("scoreLabel");
        scoreLabel->setFont(font);
        scoreLabel->setStyleSheet(QString::fromUtf8("\n"
"         QLabel {\n"
"             color: #ffffff;\n"
"         }\n"
"        "));

        verticalLayout_infoPanel->addWidget(scoreLabel);

        horizontalLayout_score = new QHBoxLayout();
        horizontalLayout_score->setSpacing(10);
        horizontalLayout_score->setContentsMargins(10, 10, 10, 10);
        horizontalLayout_score->setObjectName("horizontalLayout_score");
        scoreDisplay = new QLCDNumber(TetrisGame);
        scoreDisplay->setObjectName("scoreDisplay");
        scoreDisplay->setStyleSheet(QString::fromUtf8("\n"
"           QLCDNumber {\n"
"               background-color: #000000;\n"
"               color: #00ff00;\n"
"               border: 2px solid #00ff00;\n"
"           }\n"
"          "));

        horizontalLayout_score->addWidget(scoreDisplay);


        verticalLayout_infoPanel->addLayout(horizontalLayout_score);

        highScoreLabel = new QLabel(TetrisGame);
        highScoreLabel->setObjectName("highScoreLabel");
        highScoreLabel->setFont(font);
        highScoreLabel->setStyleSheet(QString::fromUtf8("\n"
"         QLabel {\n"
"             color: #ffffff;\n"
"         }\n"
"        "));

        verticalLayout_infoPanel->addWidget(highScoreLabel);

        horizontalLayout_highScore = new QHBoxLayout();
        horizontalLayout_highScore->setSpacing(10);
        horizontalLayout_highScore->setContentsMargins(10, 10, 10, 10);
        horizontalLayout_highScore->setObjectName("horizontalLayout_highScore");
        highScoreDisplay = new QLCDNumber(TetrisGame);
        highScoreDisplay->setObjectName("highScoreDisplay");
        highScoreDisplay->setStyleSheet(QString::fromUtf8("\n"
"           QLCDNumber {\n"
"               background-color: #000000;\n"
"           background-color: #000000;\n"
"               color: #00ff00;\n"
"               border: 2px solid #00ff00;\n"
"           }\n"
"          "));

        horizontalLayout_highScore->addWidget(highScoreDisplay);


        verticalLayout_infoPanel->addLayout(horizontalLayout_highScore);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(10);
        horizontalLayout_2->setContentsMargins(10, 10, 10, 10);
        horizontalLayout_2->setObjectName("horizontalLayout_2");

        verticalLayout_infoPanel->addLayout(horizontalLayout_2);

        backButton = new QPushButton(TetrisGame);
        backButton->setObjectName("backButton");
        backButton->setMinimumSize(QSize(150, 50));
        backButton->setFont(font);
        backButton->setStyleSheet(QString::fromUtf8("\n"
"QPushButton {\n"
"background-color: #4CAF50;\n"
"color: white;\n"
"border: none;\n"
"border-radius: 10px;\n"
"padding: 10px;\n"
"}\n"
"QPushButton\n"
"{\n"
"background-color: #45a049;\n"
"}\n"
"QPushButton\n"
"{\n"
"background-color: #388e3c;\n"
"}\n"
""));

        verticalLayout_infoPanel->addWidget(backButton);


        horizontalLayout->addLayout(verticalLayout_infoPanel);


        retranslateUi(TetrisGame);

        QMetaObject::connectSlotsByName(TetrisGame);
    } // setupUi

    void retranslateUi(QDialog *TetrisGame)
    {
        TetrisGame->setWindowTitle(QCoreApplication::translate("TetrisGame", "Tetris Game", nullptr));
        nextPieceLabel->setText(QCoreApplication::translate("TetrisGame", "Next Piece:", nullptr));
        label->setText(QCoreApplication::translate("TetrisGame", "LEVEL", nullptr));
        scoreLabel->setText(QCoreApplication::translate("TetrisGame", "Score:", nullptr));
        highScoreLabel->setText(QCoreApplication::translate("TetrisGame", "High Score:", nullptr));
        backButton->setText(QCoreApplication::translate("TetrisGame", "Back to Menu", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TetrisGame: public Ui_TetrisGame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TETRISGAMEWINDOW_H
