#include <iostream>
#include <vector>
#include <fstream>

class Data {
public:
    Data(float h, int sp) : hp(h), speed(sp) {}
    float hp;
    int speed;
};

class Memento {
private:
    std::string file_name;
    std::vector<Data*> data;

public:
    Memento(std::string name) : file_name(name + ".sav") {}

    ~Memento() {
        for(auto dt : data)
            delete dt;
    }

    void save() {
        std::ofstream out(file_name, std::ios::binary); // создаем файл сохранения
        if(out.is_open()) {
            int num = data.size();
            out.write(reinterpret_cast<char*>(&num), sizeof(num));
            for(auto dt : data)	{
                out.write(reinterpret_cast<char*>(&dt->hp), sizeof(dt->hp));
                out.write(reinterpret_cast<char*>(&dt->speed), sizeof(dt->speed));
            }
            out.close();
        } else {
            std::cerr << "Error" << std::endl;
        }
    }

    void load() {
        std::ifstream in(file_name, std::ios::binary); // загружаем сохранение
        if(in.is_open()) {
            int num;
            in.read(reinterpret_cast<char*>(&num), sizeof(num));
            for(int i=0; i< num; ++i) {
                float h;
                int sp;
                in.read(reinterpret_cast<char*>(&h), sizeof(h));
                in.read(reinterpret_cast<char*>(&sp), sizeof(sp));
                data.push_back(new Data(h, sp));
            }
            in.close();
        } else {
            std::cerr << "Error" << std::endl;
        }
    }

    void add(Data* dt) {
        data.push_back(dt);
    }

    Data* undo() {
        if(data.size() != 0) {
            Data * temp = data.back();
            data.pop_back();
            return temp;
        } else {
            return nullptr;
        }
    }
};

class Player{
private:
    float hp;
    int speed;
    std::string name;
    Memento* mem;

public:
    Player(float hp, int speed, const std::string &name) : hp(hp), speed(speed), name(name) {
        mem = new Memento(name);
        mem->load();
    }

    ~Player() {
        add();
        mem->save();
        delete mem;
    }

    void changeSpeed(int change){
        add(); // сохраняем предыдущее состояние
        speed += change;
    }

    void changeHp(float change){
        add(); // сохраняем предыдущее состояние
        hp += change;
    }

    void undo() { // загрузка из сохранения
        Data* dt = mem->undo();
        if(dt == nullptr) {
            std::cout << "no undo" << std::endl;
        } else {
            hp = dt->hp;
            speed = dt->speed;
            delete dt;
        }
        std::cout << "Download save" << std::endl;
    }

    void add() {
        mem->add(new Data(hp, speed));
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
