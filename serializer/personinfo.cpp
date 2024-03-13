#include "personinfo.h"

PersonInfo::PersonInfo() {}

PersonInfo::PersonInfo(const QString &name, int age, const QDate &birthday)
    : name(name), age(age), birthday(birthday) {}

QString PersonInfo::getName() const
{
    return name;
}

int PersonInfo::getAge() const
{
    return age;
}

QDate PersonInfo::getBirthday() const
{
    return birthday;
}

void PersonInfo::setName(const QString &name)
{
    this->name = name;
}

void PersonInfo::setAge(int age)
{
    this->age = age;
}

void PersonInfo::setBirthday(const QDate &birthday)
{
    this->birthday = birthday;
}
