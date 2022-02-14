//
// Created by dmitri on 14.02.2022.
//

#ifndef SINGLETON_PLAYER_H
#define SINGLETON_PLAYER_H

#include <iostream>
#include <vector>
#include <fstream>

template<class T>
class SmartPointer {
private:
    T* ptr;
public:
    SmartPointer(T* p = nullptr) : ptr(p) {}
    ~SmartPointer() { delete ptr; }
    T& operator*() { return *ptr; }
    T* operator->() { return ptr; }
    void operator=(T* p) {
        delete ptr;
        ptr = p;
    }
};

class Data {
public:
    Data(float h, int sp) : hp(h), speed(sp) {}
    float hp;
    int speed;
};

class Player {
private:
    float hp;
    int speed;
    std::string name;
    class Memento;
    SmartPointer<Memento> mem;

public:
    Player(float hp, int speed, const std::string &name);
    ~Player();
    void undo();
    void add();

    void changeSpeed(int change){
<<<<<<< HEAD
        add(); // сохраняем предыдущее состояние
=======
        add(); // сохраняем предидущее состояние
>>>>>>> 71cc22cf1651689295995595f2f568b80ce7e4e5
        speed += change;
    }

    void changeHp(float change){
<<<<<<< HEAD
        add(); // сохраняем предыдущее состояние
=======
        add(); // сохраняем предидущее состояние
>>>>>>> 71cc22cf1651689295995595f2f568b80ce7e4e5
        hp += change;
    }

    void print(){
        std::cout << "NAME: " << name << std::endl;
        std::cout << "HP = " << hp << "; SPEED = " << speed << std::endl;
    }

    float getHp() const {
        return hp;
    }

    int getSpeed() const {
        return speed;
    }

    const std::string &getName() const {
        return name;
    }
};

#endif //SINGLETON_PLAYER_H
