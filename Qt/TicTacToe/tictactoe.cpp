#include "tictactoe.h"
#include <QApplication>
#include <QGridLayout>
#include <QPushButton>
#include <QTimer>
#include <QLabel>

TicTacToe::TicTacToe(QWidget *parent)
    : QMainWindow(parent)
    , currentPlayer('X')
{

    setWindowTitle("Tic-Tac-Toe");
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QGridLayout *layout = new QGridLayout(centralWidget);

    messageLabel = new QLabel("Hey players! Good game.", this);//label widget, this-i vra display
    messageLabel->setFont(QFont("Arial", 16));
    layout->addWidget(messageLabel, 0, 0, 1, 3, Qt::AlignCenter);

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            buttons[i][j] = new QPushButton("", this);//empty string to each i j, new created qpushbutton is child of this
            buttons[i][j]->setFont(QFont("Arial", 40));
            layout->addWidget(buttons[i][j], i + 1, j);// i+1, q. vor 0-n label-i hamar a ogtagorcvum
            connect(buttons[i][j], SIGNAL(clicked()), this, SLOT(handleButtonClick()));
        }
    }

    currentPlayerLabel = new QLabel("Current Player: " + QString(currentPlayer), this);
    currentPlayerLabel->setFont(QFont("Arial", 14));
    layout->addWidget(currentPlayerLabel, 4, 0, 1, 3, Qt::AlignCenter);



    restartButton = new QPushButton("Restart", this);
    quitButton = new QPushButton("Quit", this);

    connect(restartButton, SIGNAL(clicked()), this, SLOT(resetGame()));
    connect(quitButton, SIGNAL(clicked()), qApp, SLOT(quit()));

    layout->addWidget(restartButton, 5, 0);
    layout->addWidget(quitButton, 5, 2);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(handleTimeout()));

    startTimer();
}

void TicTacToe::handleButtonClick()
{
    //which button is clicked
    QPushButton *button = qobject_cast<QPushButton *>(sender());//erb buttony push enq anum, signal->emit,
                                                                //u sender()-y return a anum pointer et buttonin.
    if (button) {
        if (button->text() == "") {
            button->setText(QString(currentPlayer));
            if (checkWinner()) {
                messageLabel->setText("<font color='green'>" + QString(currentPlayer) + " wins!</font>");
                timer->stop();
                for (int i = 0; i < 3; ++i) {
                    for (int j = 0; j < 3; ++j) {
                        buttons[i][j]->setEnabled(buttons[i][j]->text() != "");
                    }
                }
            } else if (checkDraw()) {
                messageLabel->setText("<font color='blue'>It's a draw!</font>");
                timer->stop();             
            } else {
                currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
                startTimer();
                currentPlayerLabel->setText("Current Player: " + QString(currentPlayer));
            }
        }
    }
}

void TicTacToe::handleTimeout()
{
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            buttons[i][j]->setEnabled(false);
        }
    }
    if (currentPlayer == 'O') {
        messageLabel->setText("<font color='red'>O loose the game, because time is out!</font>");
    } else {
        messageLabel->setText("<font color='red'>X loose the game, because time is out!</font>");
    }
    //resetGame();
}



void TicTacToe::startTimer()
{
    timer->start(15000); // 15 seconds

}

bool TicTacToe::checkWinner()
{
    //text->qstring, qpushbuttoni contentn a vercnum
    for (int i = 0; i < 3; ++i) {
        if (buttons[i][0]->text() != "" && buttons[i][0]->text() == buttons[i][1]->text() && buttons[i][1]->text() == buttons[i][2]->text()) {
            return true;
        }//rows
        if (buttons[0][i]->text() != "" && buttons[0][i]->text() == buttons[1][i]->text() && buttons[1][i]->text() == buttons[2][i]->text()) {
            return true;
        }//cols
    }
    if (buttons[0][0]->text() != "" && buttons[0][0]->text() == buttons[1][1]->text() && buttons[1][1]->text() == buttons[2][2]->text()) {
        return true;
    }//main diagonal
    if (buttons[0][2]->text() != "" && buttons[0][2]->text() == buttons[1][1]->text() && buttons[1][1]->text() == buttons[2][0]->text()) {
        return true;
    }//auxiliary diagonal
    return false;
}

bool TicTacToe::checkDraw()
{
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (buttons[i][j]->text() == "") {
                return false;
            }
        }
    }
    return true;
}

void TicTacToe::resetGame()
{
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            buttons[i][j]->setText("");
            buttons[i][j]->setEnabled(true);
        }
    }
    currentPlayer = 'X';
    startTimer();
    messageLabel->setText("Hey players! Good game.");
    currentPlayerLabel->setText("Current Player: " + QString(currentPlayer));

}
