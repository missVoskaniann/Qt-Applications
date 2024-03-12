#include "texteditor.h"
#include <QAction>
#include <QString>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QApplication>
#include <QTextEdit>
#include <QMenu>
#include <QMenuBar>
TextEditor::TextEditor(QWidget *parent)
    : QMainWindow(parent)
{
    area = new QTextEdit(this);
    setCentralWidget(area);
    setWindowTitle("My text editor");

    openA = new QAction("&open", this);
    saveA = new QAction("&save", this);
    exitA = new QAction("&exit", this);

    openA->setShortcut(QKeySequence::Open);
    saveA->setShortcut(QKeySequence::Save);
    exitA->setShortcut(QKeySequence::Quit);
    connect(openA, &QAction::triggered, this, &TextEditor::open);
    connect(saveA, &QAction::triggered, this, &TextEditor::save);
    connect(exitA, &QAction::triggered, this, &TextEditor::exit);

    menu = menuBar()->addMenu("&File");
    menu->addAction(openA);
    menu->addAction(saveA);
    menu->addAction(exitA);


}

void TextEditor::open() {
    QString name = QFileDialog::getOpenFileName(this, "open", "(*.txt)");
    if (!name.isEmpty()) {
        QFile file(name);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            area->setPlainText(file.readAll());
            file.close();
        } else {
            QMessageBox::warning(this, "Error", "Can not open the file");
        }
    }
}

void TextEditor::save() {
    QString name = QFileDialog::getOpenFileName(this, "save", "(*.txt)");
    if (!name.isEmpty()) {
        QFile file(name);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << area->toPlainText();
            file.close();
        } else {
            QMessageBox::warning(this, "Error", "Can not save the file");
        }
    }
}

void TextEditor::exit()  {
    QApplication::quit();
}

TextEditor::~TextEditor()
{}

