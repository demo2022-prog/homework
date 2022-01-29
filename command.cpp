#include <iostream>
#include <vector>


enum class Colors {
    RED,
    ORANGE,
    YELLOW,
    GREEN,
    CYAN,
    BLUE,
    VIOLET,
    WHITE
};

class Light{
public:
    Light():state(false), color(Colors::WHITE){};
    void On(){
        if(!state){
            state = true;
        }
    };

    void Off(){
        if(state){
            state = false;
        }
    };

    void changeColor(Colors newColor){
        color = newColor;
    }

    bool getState() const {
        return state;
    }

private:
    bool state;
    Colors color;
};


class Command {
public:
    virtual ~Command() {};
    virtual void Execute() = 0;

    void setLight (Light* _light) {
        light = _light;
    }


protected:
    Light* light;
};

class ColorCommand : public Command {
    Colors color;

public:
    ColorCommand(Colors newColor) {
        color = newColor;
    }

    void Execute() {
        light->changeColor(color);
    }
};

class Invoker {
    std::vector<Command*> DoneCommands;
    Light light;
    Command* pCommand;

public:
    Invoker() : pCommand(nullptr) {}

    ~Invoker() {
        for (Command* ptr : DoneCommands) {
            delete ptr;
        }
    }

    void NewColor(Colors newColor) {
        pCommand = new ColorCommand(newColor);
        pCommand->setLight(&light);
        pCommand->Execute();
        DoneCommands.push_back(pCommand);
    }

    void Undo(Colors newColor) {
        if(DoneCommands.size() != 0) {
            pCommand = DoneCommands.back();
            DoneCommands.pop_back();
            delete pCommand;
        } else {
            std::cerr << "No any commands" << std::endl;
        }
    }

    void Print()  { // мерцание
        for (int i = 0; i < DoneCommands.size(); i++) {
            std::cout << DoneCommands[i] << " ";
        }
        std::cout << std::endl;
    }
    void  unPrint()  { // мерцание в обратном порядке
        for (int i = (DoneCommands.size() - 1); i >= 0; i--) {
            std::cout << DoneCommands[i] << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    Light light;
    light.On();

    Invoker inv;
    inv.NewColor(Colors::RED);
    inv.NewColor(Colors::YELLOW);
    inv.NewColor(Colors::GREEN);
    inv.NewColor(Colors::WHITE);

    inv.Print();
    inv.unPrint();
    return 0;
}
