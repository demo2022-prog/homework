#include <iostream>
#include <vector>

class Ingredient;
class MenuItem;

class Visitor {
public:
    virtual void visit(Ingredient*) = 0;
    virtual void visit(MenuItem*) = 0;
};

class Menu {
public:
    virtual void info(Visitor*) = 0;
};

class Ingredient : public Menu {
private:
    std::string name;
    int healthRating;
    float calories;
    float protein;
    float carbs;
    float fats;

public:
    Ingredient(const std::string &nm, const int hr, const float cal, const float prt, const float crb, const float ft) :
        name(nm), healthRating(hr), calories(cal), protein(prt), carbs(crb), fats(ft) {}

    const std::string &getName() const {
        return name;
    }

    const int getHealthRating() const {
        return healthRating;
    }

    const float getCalories() const {
        return calories;
    }

    const float getProtein() const {
        return protein;
    }

    const float getCarbs() const {
        return carbs;
    }

    const float getFats() const {
        return fats;
    }


    void info(Visitor* v) override { v->visit(this); }
};

class MenuItem : public Menu {
private:
    std::string name;
    std::string description;
    float price;
    std::vector<Ingredient*> ingredients;

public:
    MenuItem(const std::string &name, const std::string &description, float price) :
        name(name), description(description), price(price) {}
    const std::string &getName() const {
        return name;
    }
    const std::string &getDescription() const {
        return description;
    }
    float getPrice() const {
        return price;
    }

    void info(Visitor* v) override {
        v->visit(this);
    }
};

class Client : public Visitor{
    void visit(Ingredient* ing) override {
        std::cout 	<< "Name: " << ing->getName() << std::endl;
        std::cout << "HealthRating: " << ing->getHealthRating() << std::endl;
        std::cout << "Calories:" << ing->getCalories() << std::endl;
        std::cout << "Protein: " << ing->getProtein() << std::endl;
        std::cout << "Carbs: " << ing->getCarbs() << std::endl;
        std::cout << "Fats: " << ing->getFats() << std::endl;
    }

    void visit(MenuItem* mi) override {
        std::cout 	<< "Name: " << mi->getName() << std::endl;
        std::cout << "Description: " << mi->getDescription() << std::endl;
        std::cout << "Price:" << mi->getPrice() << std::endl;
    }
};



int main() {
    Client cl;
    std::vector<Menu *> vec;
    vec.push_back(new MenuItem("hodgepodge", "hotchpot", 5.25));
    vec.push_back(new Ingredient("smoked ribs", 70, 450.0, 7, 4, 12));
    vec.push_back(new Ingredient("olives", 10, 50.0, 5.4, 13.2, 1.2));

    for(Menu* m : vec) {
        m->info(&cl);
        std::cout << std::endl;
    }

    for(Menu* m : vec)
        delete m;
    return 0;
}
