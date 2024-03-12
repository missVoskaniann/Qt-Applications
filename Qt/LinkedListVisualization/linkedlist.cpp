#include "linkedlist.h"

#include <QInputDialog>
#include <QColorDialog>
#include <QLabel>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QMessageBox>
#include <QPushButton>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QMainWindow>
#include <QDebug>

Node::Node(const QString& value, Node* nextNode)
    : data(value)
    , next(nextNode)
    , color(QColor("red")){}

LinkedListVisualizer::LinkedListVisualizer(QWidget* parent)
    : QGraphicsView(parent)
    , dataType(None)
    , scene(new QGraphicsScene(this))
    , head(nullptr)
    , nodeColor(QColor("red"))
    , pushBackColor(QColor("cyan"))
    , pushFrontColor(QColor("magenta"))
    , insertColor(QColor("lightGray"))
    , colorType()
    , pushFrontButton(new QPushButton("Push Front", this))
    , pushBackButton(new QPushButton("Push Back", this))
    , popFrontButton(new QPushButton("Pop Front", this))
    , popBackButton(new QPushButton("Pop Back", this))
    , resetButton(new QPushButton("Reset", this))
    , colorButton(new QPushButton("Select Color", this))
    , insertButton(new QPushButton("Insert", this))
    , deleteButton(new QPushButton("Delete", this))
    , searchButton(new QPushButton("Search", this))
    , swapButton(new QPushButton("Swap Nodes", this))
    , reverseButton(new QPushButton("Reverse List", this))
    , insertPositionInput(nullptr)
    , insertValueInput(nullptr)
    , deletePositionInput(nullptr)
    , titleLabel(new QLabel("Welcome to Singly Linked List", this))
    , menuBar(new QMenuBar(parent))
    , fileMenu(new QMenu(tr("File")))
    , aboutAction(new QAction(tr("About"), parent))
    , helpAction(new QAction(tr("Help"), parent))
{
    setScene(scene); //graphicSceane function
    setFixedSize(1200, 600);
    // Set up the menu bar
    menuBar->addMenu(fileMenu);
    fileMenu->addAction(aboutAction);
    fileMenu->addAction(helpAction);

    connect(aboutAction, &QAction::triggered, this, &LinkedListVisualizer::showAbout);
    connect(helpAction, &QAction::triggered, this, &LinkedListVisualizer::showHelp);

    QMainWindow* mainWindow = qobject_cast<QMainWindow*>(parent);
    if (mainWindow) {
        mainWindow->setMenuBar(menuBar);
        qDebug() << "Menu bar set successfully!";
    } else {
        qDebug() << "Parent is not a QMainWindow!";
    }


    pushFrontButton->setGeometry(220, 130, 100, 30);
    pushBackButton->setGeometry(840, 130, 100, 30);
    popFrontButton->setGeometry(220, 180, 100, 30);
    popBackButton->setGeometry(840, 180, 100, 30);
    resetButton->setGeometry(1070, 520, 100, 30);
    colorButton->setGeometry(940, 520, 120, 30);
    insertButton->setGeometry(550, 130, 100, 30);
    deleteButton->setGeometry(550, 180, 100, 30);
    searchButton->setGeometry(550, 400, 100, 30);
    swapButton->setGeometry(220, 400, 120, 30);
    reverseButton->setGeometry(840, 400, 120, 30);

    // Connect signals and slots
    connect(pushFrontButton, SIGNAL(clicked()), this, SLOT(pushFront()));
    connect(pushBackButton, SIGNAL(clicked()), this, SLOT(pushBack()));
    connect(popFrontButton, SIGNAL(clicked()), this, SLOT(popFront()));
    connect(popBackButton, SIGNAL(clicked()), this, SLOT(popBack()));
    connect(resetButton, SIGNAL(clicked()), this, SLOT(reset()));
    connect(colorButton, SIGNAL(clicked()), this, SLOT(changeNodeColor()));
    connect(insertButton, SIGNAL(clicked()), this, SLOT(insertNode()));
    connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteNode()));
    connect(searchButton, SIGNAL(clicked()), this, SLOT(search()));
    connect(swapButton, SIGNAL(clicked()), this, SLOT(swapNodes()));
    connect(reverseButton, SIGNAL(clicked()), this, SLOT(reverseList()));

    head = new Node{"Head", nullptr};
    visualizeLinkedList();

    titleLabel->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    titleLabel->setGeometry(0, 20, width(), 100);
    titleLabel->setFont(QFont("Arial", 35, QFont::Bold));

}


void LinkedListVisualizer::visualizeLinkedList() {
    scene->clear();

    const int nodeWidth = 80;
    const int nodeSpacing = 20;

    int x = (width() - nodeWidth) / 2;
    Node* current = head;

    if (head != nullptr && head->next != nullptr) {
        current = head->next;
    }

    while (current != nullptr) {
        QGraphicsRectItem* rectItem = scene -> addRect(x, 0, nodeWidth, 50);
        rectItem -> setBrush(current -> color);
        QGraphicsTextItem* textItem = scene -> addText(current -> data);
        textItem -> setPos(x + 10, 10);

        x += nodeWidth + nodeSpacing;

        if (current->next != nullptr) {
            QGraphicsTextItem* arrowItem = scene->addText("->");
            arrowItem -> setPos(x - 20, 10);
        }
        current = current -> next;
    }
}


void LinkedListVisualizer::pushFront() {
    QString valueStr = QInputDialog::getText(this, "Push Front", "Enter value");
    if (!valueStr.isEmpty()) {
        if (dataType == None) {
            if (valueStr.toInt()) {
                dataType = Int;
            } else if (valueStr.toDouble()) {
                dataType = Double;
            } else {
                dataType = String;
            }
        } else {
            if ((dataType == Int && !valueStr.toInt()) ||
                (dataType == Double && !valueStr.toDouble())) {
                QMessageBox::warning(this, "Invalid Input", "Data type mismatch.");
                return;
            }
        }
        Node* newNode = new Node{valueStr, head->next};
        head -> next = newNode;
        newNode -> color = pushFrontColor;
        visualizeLinkedList();
    }
}

void LinkedListVisualizer::pushBack() {
    QString valueStr = QInputDialog::getText(this, "Push Back", "Enter value");
    if (!valueStr.isEmpty()) {
        if (dataType == None) {
            if (valueStr.toInt()) {
                dataType = Int;
            } else if (valueStr.toDouble()) {
                dataType = Double;
            } else {
                dataType = String;
            }
        } else {
            if ((dataType == Int && !valueStr.toInt()) ||
                (dataType == Double && !valueStr.toDouble())) {
                QMessageBox::warning(this, "Invalid Input", "Data type mismatch.");
                return;
            }
        }

        Node* newNode = new Node{valueStr, nullptr};
        if (head == nullptr) {
            head = newNode;
        } else {
            Node* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
        newNode -> color = pushBackColor;
        visualizeLinkedList();
    }
}

void LinkedListVisualizer::insertNode() {
    bool ok;//check whether user has entered valid integer, max - 100
    int position = QInputDialog::getInt(this, "Insert Node", "Enter position", 0, 1, 100, 1, &ok);

    if (ok) {
        QString valueStr = QInputDialog::getText(this, "Insert Node", "Enter value");
        if (!valueStr.isEmpty()) {
            if (dataType == None) {
                if (valueStr.toInt()) {
                    dataType = Int;
                } else if (valueStr.toDouble()) {
                    dataType = Double;
                } else {
                    dataType = String;
                }
            } else {
                if ((dataType == Int && !valueStr.toInt()) ||
                    (dataType == Double && !valueStr.toDouble())) {
                    QMessageBox::warning(this, "Invalid Input", "Data type mismatch.");
                    return;
                }
            }
            Node* newNode = new Node{valueStr, nullptr};
            if (position == 0) {
                newNode->next = head;
                head = newNode;
            } else {
                Node* current = head;
                for (int i = 0; i < position - 1 && current != nullptr; ++i) {
                    current = current->next;
                }

                if (current != nullptr) {
                    newNode->next = current->next;
                    current->next = newNode;
                }
            }

            if (position >= getNodeCount()) {
                QMessageBox::warning(this, "Invalid Input", "Please enter a valid position.");
                dataType = None;
                delete newNode;
                return;
            }
            newNode->color = insertColor;
        }
    }
}

void LinkedListVisualizer::popFront() {
    if (head != nullptr && head -> next != nullptr) {
        Node* temp = head -> next;
        head -> next = head -> next -> next;
        delete temp;
        visualizeLinkedList();
    }
}

void LinkedListVisualizer::popBack() {
    if (head != nullptr && head->next != nullptr) {
        if (head -> next -> next == nullptr) {
            delete head -> next;
            head -> next = nullptr;
        } else {
            Node* current = head;
            while (current -> next -> next != nullptr) {
                current = current -> next;
            }
            delete current -> next;
            current -> next = nullptr;
        }

        visualizeLinkedList();
    }
}


void LinkedListVisualizer::deleteNode() {
    bool ok;
    int position = QInputDialog::getInt(this, "Delete Node", "Enter position", 0, 1, 100, 1, &ok);

    if (ok) {
        if (position == 0 && head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        } else {
            Node* current = head;
            for (int i = 0; i < position - 1 && current != nullptr; ++i) {
                current = current->next;
            }

            if (current != nullptr && current -> next != nullptr) {
                Node* temp = current -> next;
                current -> next = current -> next -> next;
                delete temp;
            }
            visualizeLinkedList();
        }
    }
}


int LinkedListVisualizer::getNodeCount() const {
    int count = 0;
    Node* current = head;
    while (current != nullptr) {
        ++count;
        current = current->next;
    }
    return count;
}

void LinkedListVisualizer::search() {
    QString valueToSearch = QInputDialog::getText(this, "Search Node", "Enter value to search");
    if (!valueToSearch.isEmpty()) {
        int index = searchValue(valueToSearch);
        if (index != -1) {
            QMessageBox::information(this, "Search Result", "Value found at index " + QString::number(index));
        } else {
            QMessageBox::information(this, "Search Result", "Value not found in the list");
        }
    }
}

int LinkedListVisualizer::searchValue(const QString& value) const {
    int index = 0;
    Node* current = head;
    while (current != nullptr) {
        if (current->data == value) {
            return index;
        }
        current = current->next;
        ++index;
    }
    return -1;
}

void LinkedListVisualizer::swapNodes() {
    int position1 = QInputDialog::getInt(this, "Swap Nodes", "Enter position of the first node", 0, 1, getNodeCount() - 1, 1);
    int position2 = QInputDialog::getInt(this, "Swap Nodes", "Enter position of the second node", 0, 1, getNodeCount() - 1, 1);

    if (position1 == position2) {
        QMessageBox::warning(this, "Invalid Input", "Please enter different positions.");
        return;
    }
    Node* prev1 = nullptr;
    Node* node1 = head;
    for (int i = 0; i < position1 && node1 != nullptr; ++i) {
        prev1 = node1;
        node1 = node1 -> next;
    }

    Node* prev2 = nullptr;
    Node* node2 = head;
    for (int i = 0; i < position2 && node2 != nullptr; ++i) {
        prev2 = node2;
        node2 = node2 -> next;
    }

    if (node1 != nullptr && node2 != nullptr) {
        if (prev1 != nullptr) {
            prev1 -> next = node2;
        } else {
            head = node2;
        }

        if (prev2 != nullptr) {
            prev2 -> next = node1;
        } else {
            head = node1;
        }

        Node* temp = node1 -> next;
        node1 -> next = node2 -> next;
        node2 -> next = temp;

        visualizeLinkedList();
    } else {
        QMessageBox::warning(this, "Invalid Input", "Please enter valid positions.");
    }
}

void LinkedListVisualizer::reverseList() {
    Node* prev = nullptr;
    Node* current = head -> next;
    Node* next = nullptr;

    while (current != nullptr) {
        next = current -> next;
        current -> next = prev;
        prev = current;
        current = next;
    }
    head -> next = prev;

    visualizeLinkedList();
}
//recursive verison
/*
void LinkedListVisualizer::reverseListRecursive(Node* prev, Node* current) {
    if (current == nullptr) {
        // Base case: reached the end of the list
        head->next = prev;
        visualizeLinkedList();
        return;
    }

    Node* next = current->next;
    current->next = prev;

    // Recursive call with updated parameters
    reverseListRecursive(current, next);
}

void LinkedListVisualizer::reverseList() {
    // Call the recursive function with initial parameters
    reverseListRecursive(nullptr, head->next);
}

*/

void LinkedListVisualizer::reset() {
    while (head != nullptr && head -> next != nullptr) {
        Node* temp = head -> next;
        head->next = head -> next -> next;
        delete temp;
    }
    delete head;
    head = new Node{"Head", nullptr};
    nodeColor = QColor("red");
    dataType = None;
    visualizeLinkedList();
}

void LinkedListVisualizer::changeNodeColor() {
    QStringList colorTypes;
    colorTypes << "Push Back" << "Push Front" << "Insert";
    bool ok;//push ok anf then change color
    colorType = QInputDialog::getItem(this, "Select Color", "Choose color for:", colorTypes, 0, false, &ok);

    if (ok) {
        QColor newColor = QColorDialog::getColor(nodeColor, this, "Choose Node Color");
        if (newColor.isValid()) {
            if (colorType == "Push Back") {
                pushBackColor = newColor;
            } else if (colorType == "Push Front") {
                pushFrontColor = newColor;
            } else if (colorType == "Insert") {
                insertColor = newColor;
            }
            visualizeLinkedList();
        }
    }
}

void LinkedListVisualizer::showAbout() {
    QMessageBox::about(this, "About", "Singly Linked List Visualizer\n\n"
                                      "This program allows you to visualize operations on a singly linked list.\n\n"
                                      "Developed by MAK production.\n\n"
                                      "Based on MAK 1.2.4 (64 bit)\n"
                                      "Built on Dec 7 2023 13:23:09");
}

void LinkedListVisualizer::showHelp() {
    QString helpText = "Singly Linked List Visualizer Help\n\n"
                       "1. Push Front: Adds a node to the front of the list.\n"
                       "2. Push Back: Adds a node to the end of the list.\n"
                       "3. Pop Front: Removes the node from the front of the list.\n"
                       "4. Pop Back: Removes the node from the end of the list.\n"
                       "5. Reset: Clears the entire linked list.\n"
                       "6. Select Color: Changes the color of nodes based on the operation (Push Back, Push Front, Insert).\n"
                       "7. Insert: Inserts a node at the specified position.\n"
                       "8. Delete: Deletes a node at the specified position.\n"
                       "9. Search: Searches for a value in the list and displays its index.\n"
                       "10. Swap Nodes: Swaps nodes at two specified positions.\n"
                       "11. Reverse List: Reverses the order of nodes in the list.\n\n"
                       "Note: The 'Head' node is not counted in positions. \n"
                       "Note is always points to the first element in list. ";

    QMessageBox::information(this, "Help", helpText);//information is ststic member
}


