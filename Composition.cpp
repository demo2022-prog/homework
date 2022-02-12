#include <iostream>
#include <vector>

class Dish {
public:
    virtual float getPrice() = 0;
    virtual std::string getName() = 0;
    virtual ~Dish(){};
};

class Pancake : public Dish {
private:
    std::string name;
    float price;

public:
    Pancake(const std::string &name, float price) : name(name), price(price) {}

    float getPrice() override {
        return price;
    }

    std::string getName() override{
        return name;
    }
};

class MorningPancake : public Pancake {
public:
    MorningPancake() : Pancake("Morning pancake", 240.0f) {}
};

class LunchPancake : public Pancake {
public:
    LunchPancake() : Pancake("Lunch pancake", 280.0f) {}
};

class MexicanPancake : public Pancake {
public:
    MexicanPancake() : Pancake("Mexican pancake", 270.0f) {}
};

class PotatoPancake : public Pancake {
public:
    PotatoPancake() : Pancake("Potato pancake", 210.0f) {}
};

class MushroomPancake : public Pancake {
public:
    MushroomPancake() : Pancake("Mushroom pancake", 220.0f) {}
};

class FalafelPancake : public Pancake {
public:
    FalafelPancake() : Pancake("Falafel pancake", 270.0f) {}
};

class ChocolatePancake : public Pancake {
public:
    ChocolatePancake() : Pancake("Chocolate pancake", 260.0f) {}
};

class BananaPancake : public Pancake {
public:
    BananaPancake() : Pancake("Banana pancake", 260.0f) {}
};

class JamPancake : public Pancake {
public:
    JamPancake() : Pancake("Jam pancake", 190.0f) {}
};

class Icecream : public Dish {
private:
    std::string name;
    float price;

public:
    Icecream(const std::string &name, float price) : name(name), price(price) {}

    float getPrice() override{
        return price;
    }

    std::string getName() override{
        return name;
    }
};

class BananaSplit : public Icecream {
public:
    BananaSplit() : Icecream("Banana Split", 260) {}
};

class BerryScream : public Icecream {
public:
    BerryScream() : Icecream("Berry ice cream", 260) {}
};

class HotBrauni : public Icecream {
public:
    HotBrauni() : Icecream("Hot Brauni", 310) {}
};

class TuttiFruity : public Icecream {
public:
    TuttiFruity() : Icecream("Tutti Fruity", 240) {}
};

class Vanilla : public Icecream {
public:
    Vanilla() : Icecream("Vanilla ice cream", 180) {}
};

class Pistachio : public Icecream {
public:
    Pistachio() : Icecream("Pistachio ice cream", 230) {}
};

class Beverage : public Dish {
private:
    std::string name;
    float price;

public:
    Beverage(const std::string &name, float price) : name(name), price(price) {}

    float getPrice() override {
        return price;
    }

    std::string getName() override {
        return name;
    }
};

class Pepsi : public Beverage {
public:
    Pepsi() : Beverage("Pistachio ice cream", 230) {}
};

class Coffee : public Beverage {
public:
    Coffee() : Beverage("Pistachio ice cream", 230) {}
};

class Tea : public Beverage {
public:
    Tea() : Beverage("Pistachio ice cream", 230) {}
};

class Composition : public Dish { // компоновщик
protected:
    std::vector<Dish*> menu;
    std::string name;
    float price;

public:
    Composition(std::string name) : name(name), price(0) {}

    float getPrice() override {
        return price;
    }

    std::string getName() override {
        return name;
    }

    void addDish(Dish* dish) { // функция добавления элемента
        menu.push_back(dish);
    }

    void totalPrice() { // функция подстчета цены
        for(auto it : menu) {
            price += it->getPrice();
        }
    }

    ~Composition() {
        for(auto it : menu)
            delete(it);
    }
};

class Breakfast : public Composition {
public:
    Breakfast() : Composition("Breakfast (set meal)") {
        addDish(new ChocolatePancake);
        addDish(new HotBrauni);
        addDish(new Coffee);
        totalPrice();
    }
};

class Lunch : public Composition {
public:
    Lunch() : Composition("Lunch (set meal)") {
        addDish(new TuttiFruity());
        addDish(new PotatoPancake());
        addDish(new Tea());
        totalPrice();
    }
};

class Dinner : public Composition {
public:
    Dinner() : Composition("Dinner (set meal)") {
        addDish(new FalafelPancake());
        addDish(new MexicanPancake());
        addDish(new Tea());
        totalPrice();
    }
};

int main() {
    Breakfast breakfast;
    std::cout << breakfast.getPrice() << std::endl;

    Lunch lunch;
    std::cout << lunch.getPrice() << std::endl;

    Dinner dinner;
    std::cout << dinner.getPrice() << std::endl;

        return 0;
    }