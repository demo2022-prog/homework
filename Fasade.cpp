#include <iostream>

class Device {
public:
    std::string type;

    Device(const std::string &type) : type(type) {}

    virtual void On() {
        std::cout << type <<" is on" << std::endl;
    }

    virtual void Off() {
        std::cout << type <<" is off" << std::endl;
    }
};

class MediaPlayer : public Device{
private:
    std::string currentMovie;

public:
    MediaPlayer(const std::string &type) : Device(type) {}

    void play(std::string newMovie) {
        currentMovie = newMovie;
        std::cout << "Movie " << currentMovie << " started" << std::endl;
    }
};

class Amplifier : public Device {
    Device* streamingPLayer;
    int volume;

public:
    Amplifier(const std::string &type) : Device(type), volume(0) {}

    void setStreamingPlayer(Device* d) {
        streamingPLayer = d;
        std::cout << "Streaming player is " << d->type << std::endl;
    }

    void setSurroundSound() {
        std::cout << "Surround Sound Mode" << std::endl;
    }

    void setVolume(int v) {
        volume = v;
    }

};

class Projector : public Device {
private:
    Amplifier* _amplifier;
    Device* _input;

public:
    Projector(const std::string &type) : Device(type) {}

    void setInput(Device* d) {
        _input = d;
        std::cout << "Projector input is " << d->type << std::endl;
    }

    void wideScreenMode() {
        std::cout << "Wide Screen Mode" << std::endl;
    }
};

class Tuner {
private:
    Amplifier* _amplifier;

public:
    void on() {
        std::cout << "Tuner on" << std::endl;
    }

    void off() {
        std::cout << "Tuner off" << std::endl;
    }
};

class Popper : public Device {
public:
    Popper(const std::string &type) : Device(type) {}

    void pop() {
        std::cout << "Popcorn will be ready soon" << std::endl;
    }
};

class Lights: public Device {
private:
    int currentLight;

public:
    Lights(const std::string &type) : Device(type), currentLight(100) {}

    void dim(int light){
        currentLight = light;
    }
};

class Screen: public Device {
public:
    Screen(const std::string &type) : Device(type) {}

    void down(){
        std::cout << "Screen is down" << std::endl;
    }

    void up(){
        std::cout << "Screen is up" << std::endl;
    }
};

class Radio : public Device { // радио
public:
    Radio(const std::string &type) : Device(type) {}

    void  on() {
        std::cout << "Radio is on" << std::endl;
    }

    void off() {
        std::cout << "Radio is off" << std::endl;
    }
};

class Facade {
private:
    enum State {
        ON, OFF
    };
    int _state;
    MediaPlayer *mp;
    Popper *popper;
    Lights *light;
    Projector *projector;
    Screen *screen;
    Amplifier *amp;
    Radio *rad;

public:
    Facade() : _state(OFF) {
        mp = new MediaPlayer("media player");
        popper = new Popper("popper");
        light = new Lights("light");
        projector = new Projector("projector");
        screen = new Screen("screen");
        amp = new Amplifier("Amplifier");
        rad = new Radio("radio");
    }

    ~Facade() {
        delete mp;
        delete popper;
        delete light;
        delete projector;
        delete screen;
        delete amp;
        delete rad;
    }

    void on(int v, const std::string &type) {
        if (_state == ON) {
            std::cout << "HomeCinema is alredy ON" << std::endl;
            return;
        } else {
            popper->On(); // Включаем попкорн машину
            popper->pop(); // Готовим попкорн
            light->dim(0); // Глушим свет
            screen->down(); // Опускаем экран
            projector->On(); // Включаем проектор
            projector->setInput(mp); // Выбираем вход проектора
            projector->wideScreenMode(); // Широкоэкранный режим
            amp->On(); // Включаем усилитель
            amp->setStreamingPlayer(mp); // Выбираем куда отправлять звук
            amp->setSurroundSound(); // Режим объемного звука
            amp->setVolume(v); // Средняя громкость
            rad->on();   // Включаем радио
            mp->On(); // Включаем медиаплеер
            mp->play(type); // Наконец смотрим фильм
            _state = ON;
            std::cout << std::endl; // ополнительный отступ для читаемости
        }
    }

    void off() {
        if (_state == OFF) {
            std::cout << "HomeCinema is alredy OFF" << std::endl;
            return;
        } else {
            light->dim(100); // Зажигаем свет
            popper->Off(); // Выключаем попкорн
            screen->up(); // Поднимаем экран
            projector->Off(); // Выключаем проектор
            amp->Off(); // Выключаем усилитель
            mp->Off(); // Выключаем медиаплеер
            _state = OFF;
        }
    }
};

int main() {
Facade facade;
facade.on(5, "Lord of the Rings");
facade.off();

    return 0;
}