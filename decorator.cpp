#include <iostream>

class Beverage {            // Абстрактный класс
public:
    virtual double getDescription() const = 0;
    virtual double cost() const = 0;
};

class HouseBlend: public Beverage{   // Молотый
public:
    double cost() const override {
        return 5.5;
    }
    double getDescription() const override {
        return cost();
    }
};

class DarkRoast: public Beverage{  // Темной обжарки
    double cost() const override {
        return 6.0;
    }
    double getDescription() const override {
        return cost();
    }
};

class Decaf: public Beverage{    // Без кофеина
    double cost() const override {
        return 7.3;
    }
    double getDescription() const override {
        return cost();
    }
};

class Espresso: public Beverage{  // Эспрессо
    double cost() const override {
        return 3.5;
    }
    double getDescription() const override {
        return cost();
    }
};

class IComponent : public Beverage { // где-то здесь ошибка
public:
    virtual double getDescription() const override {
        return 0;
    }
    virtual double cost() const override {
        return 0;
    }
};

class Decorator : public IComponent {
public:
    Decorator(IComponent* component) : _component(component) {}
    virtual double cost();
    virtual double getDescription();

private:
    IComponent* _component;

};

double  Decorator::cost() {
    return _component->cost();
}

double Decorator::getDescription() {
    return _component->getDescription();
}

class ChocolateDecorator : public Decorator { // где-то здесь проблема. не могу создать декоратор
public:
    ChocolateDecorator(IComponent*);
    virtual double cost();
    virtual double getDescription();

};

double ChocolateDecorator::cost() {
    return Decorator::cost() + 1.5;
}

double ChocolateDecorator::getDescription() {
    return Decorator::getDescription();
}

class SugarDecorator : public Decorator {
public:
    SugarDecorator(IComponent*);
    virtual double cost();
    virtual double getDescription();

};

double SugarDecorator::cost() {
    return Decorator::cost() + 0.5;
}
double SugarDecorator::getDescription() {
    return Decorator::getDescription();
}

class CinnamonDecorator : public Decorator {
public:
    CinnamonDecorator(IComponent*);
    virtual double cost();
    virtual double getDescription();

};

double CinnamonDecorator::cost() {
    return Decorator::cost() + 1.5;
}
double CinnamonDecorator::getDescription() {
    return Decorator::getDescription();
}


int main() {
    HouseBlend* houseBlend = new HouseBlend;
    std::cout << houseBlend->cost() <<std::endl;
}