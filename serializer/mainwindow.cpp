#include "mainwindow.h"
#include "personinfo.h"
#include <QGridLayout>
#include <QLabel>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QInputDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    nameLineEdit = new QLineEdit;
    QRegularExpressionValidator *nameValidator = new QRegularExpressionValidator(QRegularExpression("[a-zA-Z]*"), this);
    nameLineEdit->setValidator(nameValidator);

    ageLineEdit = new QLineEdit;
    ageLineEdit->setValidator(new QIntValidator(1, 150, this));
    birthdayEdit = new QDateEdit;

    serializeButton = new QPushButton("Serialize");
    deserializeButton = new QPushButton("Deserialize");
    openEditorButton = new QPushButton("Open Editor");

    connect(serializeButton, &QPushButton::clicked, this, &MainWindow::serialize);
    connect(deserializeButton, &QPushButton::clicked, this, &MainWindow::deserialize);
    connect(openEditorButton, &QPushButton::clicked, this, &MainWindow::openTextEditor);

    textEditor = new TextEditor;

    QGridLayout *mainLayout = new QGridLayout(centralWidget);

    mainLayout->addWidget(new QLabel("Name:"), 0, 0);
    mainLayout->addWidget(nameLineEdit, 1, 0);

    mainLayout->addWidget(new QLabel("Age:"), 2, 0);
    mainLayout->addWidget(ageLineEdit, 3, 0);

    mainLayout->addWidget(new QLabel("Birthday:"), 4, 0);
    mainLayout->addWidget(birthdayEdit, 5, 0);

    QFrame *separator = new QFrame;
    separator->setFrameShape(QFrame::VLine);
    separator->setFrameShadow(QFrame::Sunken);
    mainLayout->addWidget(separator, 0, 2, 6, 1);

    mainLayout->addWidget(serializeButton, 1, 3);
    mainLayout->addWidget(deserializeButton, 3, 3);
    mainLayout->addWidget(openEditorButton, 5, 3);
}

MainWindow::~MainWindow()
{
    delete nameLineEdit;
    delete ageLineEdit;
    delete birthdayEdit;
    delete serializeButton;
    delete deserializeButton;
    delete textEditor;
}

void MainWindow::serialize()
{
    QString filename = "/home/voskanian/Desktop/Qt/serializer/person_info.txt";
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        PersonInfo person(nameLineEdit->text(), ageLineEdit->text().toInt(), birthdayEdit->date());
        out << person.getName() << "\n";
        out << person.getAge() << "\n";
        out << person.getBirthday().toString(Qt::ISODate);
        file.close();
        qDebug() << "Serialized!";
    }
    else
    {
        qDebug() << "Failed to open file for writing.";
    }
}

void MainWindow::deserialize()
{
    QString filename = "/home/voskanian/Desktop/Qt/serializer/person_info.txt";
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        QString name = in.readLine();
        QString ageStr = in.readLine();
        QString birthdayStr = in.readLine();

        bool ageOk;
        ageStr.toInt(&ageOk);
        if (!ageOk)
        {
            QMessageBox::critical(this, "Error", "Invalid age in file.");
            return;
        }

        QDate birthday = QDate::fromString(birthdayStr, Qt::ISODate);
        if (!birthday.isValid())
        {
            QMessageBox::critical(this, "Error", "Invalid birthday in file.");
            return;
        }

        static QRegularExpression digitRegex("\\d");
        if (name.contains(digitRegex))
        {
            QMessageBox::critical(this, "Error", "Name cannot contain digits.");
            return;
        }

        nameLineEdit->setText(name);
        ageLineEdit->setText(ageStr);
        birthdayEdit->setDate(birthday);

        file.close();
        qDebug() << "Deserialized!";
    }
    else
    {
        qDebug() << "Failed to open file for reading.";
    }
}

void MainWindow::openTextEditor()
{
    textEditor->open();
    textEditor->show();
}


