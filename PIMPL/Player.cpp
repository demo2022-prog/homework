//
// Created by dmitri on 14.02.2022.
//

#include "Player.h"

class Player :: Memento {
private:
    std::string file_name;
    std::vector<Data*> data;

public:
    Memento(std::string nm) : file_name(nm + ".sav") {}

    ~Memento(){
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
        std::ifstream in(file_name, std::ios::binary);
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

Player::Player(float hp, int speed, const std::string &name) : hp(hp), speed(speed), name(name) {
    mem = new Memento(name);
    mem->load();
}

Player::~Player() {
    add();
    mem->save();
}

void Player::undo() { // загрузка из сохранения
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

void Player::add() {
    mem->add(new Data(hp, speed));
}
