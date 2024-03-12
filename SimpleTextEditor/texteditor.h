#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QMainWindow>
class QTextEdit;
class QMenu;
class QAction;

class TextEditor : public QMainWindow
{
    Q_OBJECT

public:
    TextEditor(QWidget *parent = nullptr);
    ~TextEditor();

private slots:
    void save();
    void open();
    void exit();

private:
    QTextEdit* area;
    QMenu *menu;
    QAction *openA;
    QAction *saveA;
    QAction *exitA;
};
#endif // TEXTEDITOR_H
