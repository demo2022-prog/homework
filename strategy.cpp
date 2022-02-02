#include <iostream>
#include <fstream>

class DivideStrategy {
public:
    virtual void Divide(std::string);
};

class TextWork {
protected:
    DivideStrategy* divideStrategy;

public:
    virtual void useStrategy() = 0;
    virtual void setStrategy(DivideStrategy*) = 0;
    virtual ~TextWork();
};

class TextEditor: TextWork {
private:
    size_t EditorWidth;
    std::string all_text;
    DivideStrategy *divideStrategy1;
public:
    TextEditor() {};

    TextEditor(const std::string &text) : all_text(text) {};

    TextEditor(std::ifstream &file) {
        std::string line;
        if (file.is_open()) {
            while (getline(file, line)) {
                all_text += line;
            }
        }
    }

    void PrintText() const {
        std::cout << all_text << std::endl;
    }

    void useStrategy() override {
        divideStrategy->Divide(all_text);
    }

    void setStrategy(DivideStrategy *strategy) override {
        divideStrategy = strategy;
    }
};

class DivideByScreenWidth : public DivideStrategy {
private:
    size_t _EditorWidth;
public:
    DivideByScreenWidth() {
    std::cout << "DivideByScreenWidth by screen width = " << _EditorWidth << std::endl;
}
};

class DivideBySentence : public DivideStrategy {
public:
    DivideBySentence() {
        std::cout << "Divided by Sentences" << std::endl;
    }
};

class DivideByUserWidth : public DivideStrategy {
public:
    DivideByUserWidth(int userWidth) {
        std::cout << "Divided by Sentences" << std::endl;
    }
};

int main() {

}