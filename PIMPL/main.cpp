#include "Player.h"

int main() {
    Player pl(100.0, 60, "player_1"); // создаем игрока
    pl.print();
    pl.changeHp(-9.0); // проверяем функцию
    pl.changeSpeed(10); // проверяем функцию
    pl.print();
    std::cout << std::endl;

    pl.undo(); // загружаем сохранение
    pl.print();
    std::cout << std::endl;

    pl.changeHp(-20.0); // проверяем функцию
    pl.changeSpeed(-10); // проверяем функцию
    pl.print();
    std::cout << std::endl;

    pl.undo(); // загружаем сохранение
    pl.print();
}