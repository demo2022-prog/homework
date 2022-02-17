#include <iostream>

class Monster{
private:
    int hp;
    int atk;
    int def;
    int lvl = 1;
    std::string type;
public:
    Monster(int hp, int atk, int def, const std::string &type) : hp(hp), atk(atk), def(def), type(type) {}

    void changeHp(int change){
        hp += change;
    }

    void changeAtk(int change){
        atk += change;
    }

    void changeDef(int change){
        def += change;
    }

    void changelvl(int lvlup) {
        lvlup = lvlup - lvl;
        for(int i = 0; i < lvlup; ++i) {
            lvlUp();
        }
    }

    int getHp() const {
        return hp;
    }

    int getAtk() const {
        return atk;
    }

    int getDef() const {
        return def;
    }

    int getLvl() const {
        return lvl;
    }

    Monster* clone() const {
        return new Monster(this);
    }

    Monster(const Monster* mn) {
        hp = mn->hp;
        atk = mn->atk;
        def = mn->def;
        type = mn->type;
    }
    void lvlUp() {
        hp *= 1.2;
        atk *= 1.2;
        def *= 1.2;
        ++lvl;
    }
    void info() {
        std::cout << "Monster: " << type << " (atk: " << atk << ", def: " << def << ", hp: " << hp << ", lvl: " << lvl << ")" << std::endl;
    }
};

int main() {
    Monster* m1 = new Monster(100, 9, 7, "Dullahan");
    Monster* m2 = m1->clone();
    m2->lvlUp();

    m1->info();
    m2->info();
    std::cout << std::endl;

    m1->changelvl(35);
    m2->changelvl(51);

    m1->info();
    m2->info();

    delete m1;
    delete m2;

    return 0;
}