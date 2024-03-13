#ifndef PERSONINFO_H
#define PERSONINFO_H

#include <QString>
#include <QDate>

class PersonInfo
{
public:
    PersonInfo();
    PersonInfo(const QString &name, int age, const QDate &birthday);

    QString getName() const;
    int getAge() const;
    QDate getBirthday() const;

    void setName(const QString &name);
    void setAge(int age);
    void setBirthday(const QDate &birthday);

private:
    QString name;
    int age;
    QDate birthday;
};

#endif // PERSONINFO_H
