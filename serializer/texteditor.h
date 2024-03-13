#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QMainWindow>
#include <QTextEdit>
#include <QFile>
#include <QTextStream>

class TextEditor : public QMainWindow
{
    Q_OBJECT

public:
    TextEditor(QWidget *parent = nullptr);
    ~TextEditor();

public slots:
    void open();
private slots:
    void save();
    void edit();

private:
    QTextEdit* area;
    QString fileName;
};

#endif // TEXTEDITOR_H
