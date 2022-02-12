#include <iostream>
#include <map>

class Device {
private:
    std::string name;

public:
    Device(std::string nm) : name(nm) {}

    std::string getName() {
        return name;
    }
    virtual void onDo() = 0;
};

class Calendar : public Device{
public:
    Calendar() : Device("calender") {}

    bool WorkDay(std::string day){
        return false;
    }

    bool Removal(std::string day)  {
        return false;
    }

    void onDo() override {}
};

class Coffee : public Device {
public:
    Coffee() : Device("coffee") {}

    void onDo(){
        std::cout << "Starting coffee" << std::endl;
    }
};

class TeaPot : public Device{
public:
    TeaPot() : Device("tea") {}

    void onDo(){
        std::cout << "Starting tea" << std::endl;
    }
};

class Alarm :  public Device {
public:
    Alarm() : Device("alarm") {}
    void onDo(){
        std::cout << "Rise and shine, Mr. Freeman" << std::endl;
    }
    bool isOn() {
        onDo();
        return true;
    }
};

class Mediator {
private:
    std::map<std::string, Device *> _devices;
    void setNewAlarm() {
        if(getCalender()->WorkDay("tomorrow")){
            if(getCalender()->Removal("tomorrow")) {
                std::cout << "Set next alarm working day and waste removal" << std::endl;
            } else {
                std::cout << "Set next alarm working day" << std::endl;
            }
        } else {
            if(getCalender()->Removal("tomorrow"))
                std::cout << "Set next alarm weekend and waste removal" << std::endl;
            else
                std::cout << "Set next alarm weekend" << std::endl;
        }
    }
    Calendar* getCalender() {
        return (Calendar *)_devices["calender"];
    }
    Alarm* getAlarm() {
        return (Alarm *)_devices["alarm"];
    }

public:
    void add(Device* dv) {
        _devices[dv->getName()] = dv;
    }
    void getUp() {
        if(getAlarm()->isOn()) {
            if(getCalender()->WorkDay("tomorrow")) {
                _devices["coffee"]->onDo();
            } else {
                _devices["tea"]->onDo();
            }
                setNewAlarm();
        }
    }
};

int main() {
    Coffee cf;
    TeaPot tp;
    Alarm al;
    Calendar cl;

    Mediator md;
    md.add(&cf);
    md.add(&tp);
    md.add(&al);
    md.add(&cl);

    md.getUp();
    return 0;
}
