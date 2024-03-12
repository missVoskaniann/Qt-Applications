#ifndef LINKEDLIST_H
#define LINKEDLIST_H

//all necessary headers
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QColor>
#include <QPushButton>
#include <QLabel>
#include <QInputDialog>


class QLineEdit;
class QPushButton;
class QLabel;
class QMenuBar;

struct Node {
    QString data;
    Node* next;
    QColor color;
    Node(const QString&, Node* nextNode = nullptr);
};

class LinkedListVisualizer : public QGraphicsView {
    Q_OBJECT

public:
    LinkedListVisualizer(QWidget* parent = nullptr);

private slots:
    void pushFront();
    void pushBack();
    void popFront();
    void popBack();
    void reset();
    void changeNodeColor();
    void insertNode();
    void deleteNode();
    void search();
    void swapNodes();
    void reverseList();
    void showAbout();
    void showHelp();

private:
    void visualizeLinkedList();
    int getNodeCount() const;
    int searchValue(const QString& value) const;
    void updateNodeColors(Node* startNode);

private://d_ms
    enum DataType {
        None,
        Int,
        String,
        Double
    } dataType;

    QGraphicsScene* scene;
    Node* head;
    QColor nodeColor;
    QColor pushBackColor;
    QColor pushFrontColor;
    QColor insertColor;
    QString colorType;

    //buttons
    QPushButton* pushFrontButton;
    QPushButton* pushBackButton;
    QPushButton* popFrontButton;
    QPushButton* popBackButton;
    QPushButton* resetButton;
    QPushButton* colorButton;
    QPushButton* insertButton;
    QPushButton* deleteButton;
    QPushButton* searchButton;
    QPushButton* swapButton;
    QPushButton* reverseButton;
    //linEdits
    QLineEdit* insertPositionInput;
    QLineEdit* insertValueInput;
    QLineEdit* deletePositionInput;
    //title
    QLabel* titleLabel;
    //menuba
    QMenuBar* menuBar;
    QMenu* fileMenu; // Declare a menu for "File"
    QAction* aboutAction; // Declare an action for "About"
    QAction* helpAction;
};

#endif // LINKEDLIST_H
