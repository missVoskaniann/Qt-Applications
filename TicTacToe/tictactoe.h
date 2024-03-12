#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <QMainWindow>

class QPushButton;
class Timer;
class QLabel;

class TicTacToe : public QMainWindow {
    Q_OBJECT

public:
    TicTacToe(QWidget *parent = nullptr);

private slots:
    void handleButtonClick();
    void handleTimeout();
    void resetGame();

private:
    QPushButton *buttons[3][3];
    char currentPlayer;
    QTimer *timer;
    QLabel *messageLabel;
    QPushButton *restartButton;
    QPushButton *quitButton;
    QLabel *currentPlayerLabel;

    void startTimer();
    bool checkWinner();
    bool checkDraw();

};

#endif // TICTACTOE_H
