#include <QApplication>
#include "tictactoe.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    TicTacToe game;
    game.show();

    return app.exec();
}
