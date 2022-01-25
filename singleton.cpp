#include <iostream>
#include <string>

class ChocolateBoiler{
private:
    bool _empty;
    bool _boiled;
    static ChocolateBoiler* _uniqueInstance;
    std::string _value; // для визуализации работы
    ChocolateBoiler(const std::string& name): _value(name){
        _empty = true;
        _boiled = false;
//        _value = name;
    }

public:
    virtual ~ChocolateBoiler();
    ChocolateBoiler(ChocolateBoiler& other) = delete;
    void operator=(ChocolateBoiler&) = delete;
    static ChocolateBoiler* GetInstance(const std::string& name);

    std::string value() const {
        return _value;
    }

    bool isEmpty() const{
        return _empty;
    }

    bool isBoiled() const{
        return _boiled;
    }

    void fill(){
        if (isEmpty()){
            _empty = false;
            _boiled = false;
        }
    }

    void drain(){
        if (!isEmpty() && isBoiled()){
            _empty = true;
        }
    }

    void boil(){
        if (!isEmpty() && !isBoiled()){
            _boiled = true;
        }
    }
};

ChocolateBoiler* ChocolateBoiler::_uniqueInstance = nullptr;

ChocolateBoiler* ChocolateBoiler::GetInstance(const std::string &name) {
    if (_uniqueInstance == nullptr) {
        _uniqueInstance = new ChocolateBoiler(name);
    }
    return _uniqueInstance;
}

ChocolateBoiler::~ChocolateBoiler() {
    delete _uniqueInstance;
}

int main() {
    ChocolateBoiler* boiler = ChocolateBoiler::GetInstance("First");
    std::cout << boiler->value() << std::endl; //проверка

    ChocolateBoiler* boiler2 = ChocolateBoiler::GetInstance("Second");
    std::cout << boiler2->value() << std::endl; //проверка
    return 0;
}
