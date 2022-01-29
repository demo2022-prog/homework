#include <iostream>
#include <vector>

class Pizza{
public:
    virtual void info() const = 0;
    virtual ~Pizza() {};
};

class CheesePizza : public Pizza{
public:
    void info() const {
        std::cout << "Cheese Pizza" << std::endl;
    }
};
class GreekPizza : public Pizza{
public:
    void info() const {
        std::cout << "Greek Pizza" << std::endl;
    }
};
class PepperoniPizza : public Pizza{
public:
    void info() const {
        std::cout << "Pepperoni Pizza" << std::endl;
    }
};

class PizzaFactory {
public:
    virtual Pizza* createPizza() = 0;
    virtual ~PizzaFactory() {};
};

class CheesePizzaFactory : public PizzaFactory{
public:
    Pizza* createPizza() {
        return new CheesePizza;
    }
};

class GreekPizzaFactory : public PizzaFactory{
public:
    Pizza* createPizza() {
        return new GreekPizza;
    }
};

class PepperoniPizzaFactory : public PizzaFactory{
public:
    Pizza* createPizza() {
        return new PepperoniPizza;
    }
};

struct Log {
    std::vector<Pizza*> piz;

    void info() {
        for (const auto &n: piz) {
            n->info();
        }
    }
    ~Log(){};
};

class orderPizza {
public:
    Log* createPizza(PizzaFactory& factory) {
        Log *a = new Log;
        a->piz.push_back(factory.createPizza());
        return a;
    }

};

int main() {
    orderPizza order;
    CheesePizzaFactory cpf;
    GreekPizzaFactory gpf;
    PepperoniPizzaFactory ppf;

    Log* pCheesePizza = order.createPizza(cpf);
    Log* pGreekPizza = order.createPizza(gpf);
    Log* pCPepperoniPizza = order.createPizza(ppf);

    pCheesePizza->info();
    pGreekPizza->info();
    pCPepperoniPizza->info();

    delete pCheesePizza;
    delete pGreekPizza;
    delete pCPepperoniPizza;
}
