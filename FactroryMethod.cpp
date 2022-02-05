#include <iostream>
#include <vector>

class Pizza{
public:
    virtual void prepare() {
        bake();
        cut();
        box();
    }
    virtual void bake() {};
    virtual void cut() {};
    virtual void box() {};
};

class CheesePizza : public Pizza{
public:
    void bake() override {
        std::cout << "CheesePizza is baking." << std::endl;
    }
    void cut() override {
        std::cout << "CheesePizza is cuting." << std::endl;
    }
    void box() override {
        std::cout << "CheesePizza is boxing." << std::endl;
    }
};
class GreekPizza : public Pizza{
public:
    void bake() override {
        std::cout << "GreekPizza is baking." << std::endl;
    }
    void cut() override {
        std::cout << "GreekPizza is cuting." << std::endl;
    }
    void box() override {
        std::cout << "GreekPizza is boxing." << std::endl;
    }
};
class PepperoniPizza : public Pizza{
public:
    void bake() override {
        std::cout << "PepperoniPizza is baking." << std::endl;
    }
    void cut() override {
        std::cout << "PepperoniPizza is cuting." << std::endl;
    }
    void box() override {
        std::cout << "PepperoniPizza is boxing." << std::endl;
    }
};


class PizzaFactory { // базовая фабрика
public:
    virtual Pizza * createPizza() = 0;
    virtual ~PizzaFactory() {}
};

Pizza* orderPizza(PizzaFactory * pizzaFactory) {
    return pizzaFactory->createPizza();
}

class CheesePizzaFactory : public PizzaFactory {
public:
    Pizza* createPizza() override {
        return new CheesePizza();
    }
};

class GreekPizzaFactory : public PizzaFactory {
public:
    Pizza* createPizza() override {
        return new GreekPizza();
    }
};

class PepperoniPizzaFactory : public PizzaFactory {
public:
    Pizza* createPizza() override {
        return new PepperoniPizza();
    }
};


int main() {
    std::vector<Pizza*> orders;
    CheesePizzaFactory cp;
    GreekPizzaFactory gp;
    PepperoniPizzaFactory pp;

    orders.push_back(orderPizza(&gp));
    orders.push_back(orderPizza(&pp));
    orders.push_back(orderPizza(&cp));

    for(auto item : orders){
        item->prepare();
        std::cout << std::endl;
    }
}