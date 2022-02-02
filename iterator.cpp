#include <iostream>
#include <vector>
#include <list>
#include <deque>

class Employer {
private:
    int number;
public:
    Employer() {}
    Employer(int number) : number(number) {}

    int getNumber() const {
        return number;
    }

    ~Employer() {}
}; // за основу взял упрощенный класс из занятия

bool operator<(Employer& lhs, Employer& rhs) {
    return lhs < rhs;
}
bool operator<(const Employer& lhs, const Employer& rhs) {
    return lhs < rhs;
}

class IIterator {
public:
    virtual bool hasNext() const = 0;
    virtual Employer getNext() = 0;
    virtual Employer getLast() = 0;
};

template<template<typename> class Cont> // для использования с разными контейнерами
class Iterator : public IIterator {
private:
   Cont<Employer> employers;
    int position = 0;

public:
    Iterator(const Cont<Employer> &employers) : employers(employers) {}

    virtual Employer getNext() override { // итерируем от начала
        Employer employer;
        if(hasNext()) {
            employer = *(std::next(employers.begin, position));
            ++position;
        }
        return employer;
    }

    virtual Employer getLast() override { // итерируем от конца
        Employer employer;
        position = employers.size();
        if(position >= 0) {
            employer = *(std::next(employers.begin, position));
            --position;
        }
        return employer;
    }

    virtual bool hasNext() const override{
        return position < employers.size();
    }
};

template<template<typename> class Cont>
class Company {
private:
    Cont<Employer> employers;
    int last_number = 0;

public:
    Company() {}

    void addEmployer(int number) {
        employers.insert(Employer(number));
        ++last_number;
    }

    Cont<Employer> getEmployers() const {
        return employers;
    }

    IIterator* createIterator(){
        return new Iterator<Cont>;
    }
};

int main() {
    Company<std::vector<Employer>> company; // на этом этапе ошибка. не смог решить

}