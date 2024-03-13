#include "texteditor.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>

TextEditor::TextEditor(QWidget *parent)
    : QMainWindow(parent)
{
    area = new QTextEdit(this);
    setCentralWidget(area);
    setWindowTitle("Text Editor");

    fileName = "/home/voskanian/Desktop/Qt/serializer/person_info.txt";
    open();

    QPushButton *saveButton = new QPushButton("Save", this);
    connect(saveButton, &QPushButton::clicked, this, &TextEditor::save);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(area);
    layout->addWidget(saveButton);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);
    setCentralWidget(widget);
}

TextEditor::~TextEditor()
{}

void TextEditor::open() {
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        area->setPlainText(file.readAll());
        file.close();
    } else {
        QMessageBox::warning(this, "Error", "Can not open the file");
    }
}


void TextEditor::save() {
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << area->toPlainText();
        file.close();
        close();
    } else {
        QMessageBox::warning(this, "Error", "Can not save the file");
    }
}


void TextEditor::edit() {
    open();
}
