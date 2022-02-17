#include <iostream>

class CoffeeAutomat;

class State {
private:
    std::string info;

public:
    State(const std::string &info) : info(info) {}

    const std::string &getInfo() const {
        return info;
    }

    virtual void next(CoffeeAutomat*) = 0;
};

class NotCoin : public State {
public:
    NotCoin() : State("Not money") {}

    void next(CoffeeAutomat* am) override;
};

class WaitCoin : public State {
public:
    WaitCoin() : State("Insert money") {}

    void next(CoffeeAutomat* am) override;
};

class TakeCoffee : public State {
public:
    TakeCoffee() : State("Take a coffee") {}

    void next(CoffeeAutomat* am) override;
};

class ReadyCoffee : public State {
public:
    ReadyCoffee() : State("Coffee is ready"){}

    void next(CoffeeAutomat* am) override;
};

class OverCoffee : public State {
public:
    OverCoffee() : State("Coffee is over") {}

    void next(CoffeeAutomat*) override;
};

class PushPay : public State {
public:
    PushPay() : State("Push to pay") {}

    void next(CoffeeAutomat* am) override;
};

class CoffeeAutomat{
private:
    bool coin;
    int amount;
    State* state;

public:
    CoffeeAutomat(int amount) : state(nullptr), amount(amount), coin(false) {
        setState(new WaitCoin());
    }

    void setState(State*  st) {
        delete state;
        state = st;
        std::cout << state->getInfo() << std::endl;
    }

    ~CoffeeAutomat() {
        delete state;
    }

    void setCoin() {
        coin = true;
    }

    bool getCoin() {
        if(coin) {
            coin = false;
            return true;
        }
        return false;
    }

    bool getCoffee() {
        --amount;
        return amount >= 0;
    }

    void next() {
        state->next(this);
    }
};

void NotCoin::next(CoffeeAutomat* am) {
    am->setState(new WaitCoin());
}

void WaitCoin::next(CoffeeAutomat* am) {
    if(am->getCoin()) {
        am->setState(new PushPay());
    } else {
        am->setState(new NotCoin());
    }
}

void TakeCoffee::next(CoffeeAutomat* am) {
    am->setState(new WaitCoin());
}

void ReadyCoffee::next(CoffeeAutomat* am) {
    am->setState(new TakeCoffee());
}

void OverCoffee::next(CoffeeAutomat* am)  {
}

void PushPay::next(CoffeeAutomat* am) {
    if(am->getCoffee()) {
        am->setState(new ReadyCoffee());
    }
    else {
        am->setState(new OverCoffee());
    }
}

int main() {
    CoffeeAutomat am(2);        //состояние положить монету
        am.setCoin();            //положить монету в автомат
        am.next();                //состояние нажать заплатить
        am.next();                //состояние кофе готовый или кофе закончился
        am.next();                //состояние взять кофе или ничего если кофе закончился
        am.next();                //состояние положить монету или ничего если кофе закончился
        am.next();                //состояние нет монеты или ничего если кофе закончился
        am.next();                //состояние положить монету или ничего если кофе закончился

        return 0;
}
