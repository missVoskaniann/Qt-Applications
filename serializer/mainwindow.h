#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QDateEdit>
#include <QIntValidator>
#include "texteditor.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void serialize();
    void deserialize();
    void openTextEditor();

private:
    QLineEdit *nameLineEdit;
    QLineEdit *ageLineEdit;
    QDateEdit *birthdayEdit;
    QPushButton *serializeButton;
    QPushButton *deserializeButton;
    QPushButton *openEditorButton;
    TextEditor *textEditor;
};

#endif // MAINWINDOW_H
