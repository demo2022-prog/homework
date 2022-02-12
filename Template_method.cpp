#include <iostream>
#include <vector>

class Data {
public:
    virtual void draw() = 0;
};

class Pixel : public Data {
private:
    int x;
    int y;
    std::string color;

public:
    Pixel(int x, int y, std::string color) : x(x), y(y), color(color) {}

    void draw() override {
        std::cout << "(" << x << ", " << y << ", " << color << ") ";
    }

};

class Figure : public Data {
private:
    int x;
    int y;
    std::string figure;

public:
    Figure(int x, int y, std::string figure) : x(x), y(y), figure(figure) {}

    void draw() override {
        std::cout << "(" << x << ", " << y << ", " << figure << ") ";
    }
};

class Image {
protected:
    std::vector<Data*> buffer;

public:
    void openFile(const std::string& filename) {
        std::cout << "Open file " << filename << std::endl;
    }

    virtual void readFile() = 0;

    void draw(){
        for (const auto it: buffer)
            it->draw();
        std::cout << std::endl;
    }

    void final() {
        std::cout << "Drawing image complete" << std::endl;
    }

    ~Image() {}
};

class BitmapImage : public Image {        // Растровое изображение
public:
    BitmapImage(const std::string &filename) {
        openFile(filename);
    }

    void readFile() override {
//Имитируем чтение
        buffer.push_back(new Pixel(1, 9, "red"));
        buffer.push_back(new Pixel(2, 4, "black"));
        buffer.push_back(new Pixel(0, 5, "yellow"));
    }
};

class VectorImage : public Image {        // Векторное изображение
public:
    VectorImage(const std::string &filename) {
        openFile(filename);
    }

    void readFile() override {
//Имитируем чтение
        buffer.push_back(new Figure(25, 5, "LINE"));
        buffer.push_back(new Pixel(42, 14, "RECTANGLE"));
    }

};

int main() {
    Image* img = new BitmapImage("Bitmap Image");
    img->readFile();
    img->draw();
    img->final();
    delete img;

    std::cout << std::endl;

    img = new VectorImage("Vector Image");
    img->readFile();
    img->draw();
    img->final();
    delete img;

}