#include <iostream>
#include <vector>

class Observer;

class IHerald {
public:
    virtual void registration(Observer* obs) = 0;
    virtual void remove(Observer* obs) = 0;
    virtual void notify(int voicePower, std::string announcement) = 0;
    virtual void getAnswer() = 0;

};

class Announcement {
protected:
    std::string announcement;

public:
    Announcement() : announcement("") {}
};

class Citizen {
protected:
    std::string name;
    int hearingPower;

public:
    Citizen(std::string nm, int hp) : name(nm), hearingPower(hp) {}
};

class Observer : public Announcement, Citizen {
public:
    Observer(std::string nm, int ph) : Citizen(nm, ph), Announcement() {}

    void listen(int voicePower, std::string ann) {
        announcement = (voicePower <= hearingPower ? ann : "");
    }

    void getAnswer(){
        std::cout << name << ": I am " << (announcement == "" ? " " : "not ") << "hearing" << std::endl;
    }
};

class Doctor : public Observer {
public:
    Doctor(IHerald* h) : Observer("Doctor", 10){
        h->registration(this);
    }
};

class Blacksmith : public Observer {
public:
    Blacksmith(IHerald* h) : Observer("Blacksmith", 70){
        h->registration(this);
    }
};

class Child : public Observer {
public:
    Child(IHerald * h) : Observer("Child", 30){
        h->registration(this);
    }
};

class Herald : public IHerald {
private:
    std::vector<Observer*> observers;
public:
    void registration(Observer* obs) {
        observers.push_back(obs);
    }

    void remove(Observer* obs) {
        for(auto it = observers.begin(); it != observers.end(); ++it) // не очень красиво но работает
            if(*it == obs) observers.erase(it);
    }

    void notify(int voicePower, std::string announcement) override{
        for(auto obs : observers){
            obs->listen(voicePower, announcement);
        }
    }

    void getAnswer() override {
        for(auto obs : observers){
            obs->getAnswer();
        }
    }
};

int main() {
    Herald herald;
    Doctor dc(&herald);
    Blacksmith bl(&herald);
    Child ch(&herald);

    herald.notify(30, "execution");
    herald.getAnswer();
    std::cout << std::endl;
    herald.notify(100, "plague");
    herald.getAnswer();
    std::cout << std::endl;
    herald.notify(10, "the lord came again");
    herald.getAnswer();

    return 0;
}