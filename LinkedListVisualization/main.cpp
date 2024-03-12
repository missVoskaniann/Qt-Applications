#include "linkedlist.h"
#include <QApplication>
#include <QMainWindow>


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QMainWindow mainWindow;
    mainWindow.setFixedSize(1200, 600);
    mainWindow.setWindowTitle("Singly Linked List");

    LinkedListVisualizer linkedListVisualizer(&mainWindow);
    mainWindow.setCentralWidget(&linkedListVisualizer);

    mainWindow.show();

    return a.exec();
}
