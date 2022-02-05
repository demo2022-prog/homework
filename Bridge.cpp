#include <iostream>

class DrawingImplementor {
public:
    virtual void drawRectangle(double) = 0;
    virtual ~DrawingImplementor() {}
};

class PaintBrush : public DrawingImplementor {
public:
    void drawRectangle(double w) {
        std::cout << "Brush width " << w << std::endl;
    }
};

class PaintPen : public DrawingImplementor {
public:
    void drawRectangle(double w) {
        std::cout << "Pen width " << w << std::endl;
    }
};

class Shape {
protected:
    DrawingImplementor* imp;

public:
    virtual void draw() = 0; // low-level
    virtual void resize(double) {}; // high-level
    virtual ~Shape() {}
};

class Rectangle: public Shape {
protected:
    DrawingImplementor* imp;

public:
    Rectangle(DrawingImplementor* i) : imp(i) {};
    void draw() override {
        imp->drawRectangle(1);
    }
};

class RectangleWidth : public Rectangle {
private:
    double width;

public:
    RectangleWidth(DrawingImplementor* i):Rectangle(i) {}
    void resize(double p) {
        width = p;
    }
    void draw() override {
        imp->drawRectangle(width);
    }
};

int main() {
    PaintPen pp;
    PaintBrush pb;

    Rectangle rg(&pp);
    rg.draw();
    RectangleWidth rgW(&pb);
    rgW.resize(7);
    rgW.draw();

    return 0;
}