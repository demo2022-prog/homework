#include <iostream>
#include <vector>

class Events {
public:
    virtual void getEvent() = 0;
    virtual ~Events() {};
};

class Hotel: public Events {
public:
    void getEvent() {
        std::cout << "Booking Hotel" << std::endl;
    }
};

class Park: public Events {
    void getEvent() {
        std::cout << "Park visiting" << std::endl;
    }
};

class Food: public Events {
public:
    virtual void getEvent() = 0;
    virtual ~Food() {};
};

class Dinner: public Food {
public:
    Dinner(const std::string &type) : _type(type) {}
    void getEvent(){
        std::cout << "Food " << _type << std::endl;
    } ;
private:
    std::string _type;
};

class Lunch: public Food {
public:
    Lunch() : _type("lunch") {}
    void getEvent() {
        std::cout << "Food " << _type << std::endl;
    };

private:
    std::string _type;
};

class Breakfast: public Food {
public:
    Breakfast() : _type("breakfast") {}
    void getEvent() {
        std::cout << "Food " << _type << std::endl;
    };

private:
    std::string _type;
};

class Special: public Events {
public:
    virtual void getEvent() = 0;
    virtual ~Special() {};
};

class Skating:public Special {
public:
    Skating(const std::string &type) : _type("skating") {}
    void getEvent() {
        std::cout << _type << std::endl;
    };

private:
    std::string _type;
};

class Circus:public Special {
public:
    Circus(const std::string &type) : _type("circus") {}
    void getEvent() {
        std::cout << _type << std::endl;
    };

private:
    std::string _type;
};

class ScheduleDay { // расписание дня
private:
    std::vector<Events*> events;
public:
    void info(){
        for(auto item : events)
            item->getEvent();
    }
    ~ScheduleDay() {
        for(auto item : events)
            delete item;
    }
    void add(Events* ev) { events.push_back(ev); }
};

class BuilderDay { // конструктор дня
protected:
    ScheduleDay* _day;
public:

    virtual ~BuilderDay() {}
    virtual void addHotel() {}
    virtual void addPark() {}
    virtual void addBreakfast() {}
    virtual void addLunch() {}
    virtual void addDinner() {}
    virtual void addSkating() {}
    virtual void addCircus() {}
    virtual void createDay() {
        _day = new ScheduleDay;
    }
    virtual ScheduleDay* getDay() {
        return _day;
    }

};
class Director {
public:
    ScheduleDay* createDay(BuilderDay* bd) {
        bd->createDay();
        bd->addHotel();
        bd->addPark();
        bd->addBreakfast();
        bd->addLunch();
        bd->addDinner();
        bd->addSkating();
        bd->addCircus();
        return bd->getDay();
    }
};
class FirstDay : public BuilderDay{
public:
    virtual void addHotel() {
        _day->add(new Hotel);
    }
    virtual void addPark() {
        _day->add(new Park);
    }
    virtual void addDinner() {
        _day->add(new Dinner("dinner"));
    }
};
class SecondDay : public BuilderDay{
public:
    virtual void addBreakfast() {
        _day->add(new Breakfast);
    }
    virtual void addPark() {
        _day->add(new Park);
    }
    virtual void addDinner() {
        _day->add(new Dinner("dinner"));
    }

};
class ThirdDay : public BuilderDay{
public:
    virtual void addBreakfast() {
        _day->add(new Breakfast);
    }
    virtual void addSkating() {
        _day->add(new Skating("skating"));
    }
    virtual void addDinner() {
        _day->add(new Dinner("dinner"));
    }
    virtual void addCircus() {
        _day->add(new Circus("circus"));
    }
    virtual void addLunch() {
        _day->add(new Lunch);
    }

};

int main() {

    Director dir;
    FirstDay d1_builder;
    SecondDay d2_builder;
    ThirdDay d3_builder;

    ScheduleDay* d1 = dir.createDay(&d1_builder);
    ScheduleDay* d2 = dir.createDay(&d2_builder);
    ScheduleDay* d3 = dir.createDay(&d3_builder);

    std::cout << "#1: " << std::endl;
    d1->info();
    std::cout << std::endl;
    std::cout << "#2: " << std::endl;
    d2->info();
    std::cout << std::endl;
    std::cout << "#3: " << std::endl;
    d3->info();
    std::cout << std::endl;

    delete d1;
    delete d2;
    delete d3;
}