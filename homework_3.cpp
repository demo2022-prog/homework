#include <iostream>
#include <cmath>
#include <cstdio>
#define Pi 3.14 // Число Пи

// lesson 1

class Figure{
public:
    virtual void area() = 0 ;
};

class Parallelogram : Figure{
private:
    double base;
    double height;
    double sq;
public:
    Parallelogram (double m_base, double m_heihgt) {
        base = m_base;
        height = m_heihgt;
    }
    Parallelogram(){}

    virtual void area() {
        sq = base * height;
        std::cout << "Area Parallelogram = " << sq << '\n';
    }
};

class Circle : Figure{
private:
    double radius;
    double sq;
public:
    Circle (double m_radius) {
        radius = m_radius;
    }

    virtual void area() {
        sq = Pi * (pow (radius, 2));
        std::cout << "Area Circle = " << sq << '\n';
    }
};

class Rectangle : Parallelogram {
private:
    double length;
    double width;
    double sq;
public:
    Rectangle (double m_length, double m_width) : Parallelogram (m_length, m_width) {
        length = m_length;
        width = m_width;
    }
    virtual void area() {
        sq = length * width;
        std::cout << "Area Rectangle = " << sq << '\n';
    }
};

class Square : Parallelogram {
private:
    double side;
    double sq;
public:
    Square(double m_side) : Parallelogram () {
        side = m_side;
    }
    virtual void area() {
        sq = pow(side, 2);
        std::cout << "Area Square = " << sq << '\n';
    }
};

class Rhombus : Parallelogram {
private:
    double d1;
    double d2;
    double sq;
public:
    Rhombus(double m_d1, double m_d2) : Parallelogram () {
        d1 = m_d1;
        d2= m_d2;
    }
    virtual void area() {
        sq = (d1 * d2) / 2;
        std::cout << "Area Rhombus = " << sq << '\n';
    }
};

// lesson 2

class Car {
private:
    std::string model;
    std::string company;

public:
    Car() {}

    Car (std::string m_company, std::string m_model) {
        company = m_company;
        model = m_model;
    }

    virtual void getCar() {
        std::cout << company << " " << model  << std::endl;
    }
};

class PassengerCar : virtual public Car {
public:
    PassengerCar (std::string company, std::string model) : Car (company, model) {}
};

class Bus : virtual public Car {
public:
    Bus (std::string company, std::string model) : Car (company, model) {}
};

class Minivan : public PassengerCar,  public Bus {
public:
    Minivan (std::string company, std::string model) : Bus(company, model), PassengerCar(company, model), Car(company, model) {}
};

// lesson 3

class Fraction {
private:
    double numerator;
    double denominator;
public:
    Fraction() {
        numerator = 0;
        denominator = 0;
    }
    Fraction(double m_numerator, double m_denominator) {
        if (m_denominator != 0) { // для простоты рассматриваем только положительные дроби
        numerator = m_numerator;
        denominator = m_denominator;
        } else {
            std::cout << "Error" << std::endl;
        }
    }

    Fraction operator +(const Fraction & other) {
      Fraction temp;
      if(this->denominator != other.denominator) {
        temp.numerator = (this->numerator * other.denominator) + (other.numerator * this->denominator);
        temp.denominator = this->denominator * other.denominator;
      } else {
          temp.numerator = this->numerator + other.numerator;
          temp.denominator = this->denominator;
      }
      return temp;
   }
    Fraction operator -(const Fraction & other) {
      Fraction temp;
      if(this->denominator != other.denominator) {
         temp.numerator = (this->numerator * other.denominator) - (other.numerator * this->denominator);
        temp.denominator = this->denominator * other.denominator;
      } else {
          temp.numerator = this->numerator - other.numerator;
          temp.denominator = this->denominator;
      }
      return temp;
   }
    Fraction operator *(const Fraction & other) {
      Fraction temp;
      if(this->denominator != other.denominator) {
         temp.numerator = (this->numerator * other.denominator) * (other.numerator * this->denominator);
        temp.denominator = this->denominator * other.denominator;
      } else {
          temp.numerator = this->numerator * other.numerator;
          temp.denominator = this->denominator;
      }
      return temp;
   }
    Fraction operator /(const Fraction & other) {
      Fraction temp;
      if(this->denominator != other.denominator) {
        temp.numerator = (this->numerator * other.denominator) / (other.numerator * this->denominator);
        temp.denominator = this->denominator * other.denominator;
      } else {
          temp.numerator = this->numerator / other.numerator;
          temp.denominator = this->denominator;
      }
      return temp;
   }
    bool operator ==(const Fraction & other) {
        if(this->denominator == other.denominator) {
            return this->numerator == other.numerator;
        } else {
            return (this->numerator * other.denominator) == (other.numerator * this->denominator);
        }
    }
    bool operator !=(const Fraction & other) {
        if(this->denominator == other.denominator) {
            return this->numerator != other.numerator;
        } else {
            return (this->numerator * other.denominator) != (other.numerator * this->denominator);
        }
    }
    bool operator <(const Fraction & other) {
        if(this->denominator == other.denominator) {
            return this->numerator < other.numerator;
        } else {
            return (this->numerator * other.denominator) < (other.numerator * this->denominator);
        }
    }
    bool operator >(const Fraction & other) {
        if(this->denominator == other.denominator) {
            return this->numerator > other.numerator;
        } else {
            return (this->numerator * other.denominator) > (other.numerator * this->denominator);
        }
    }
    bool operator <=(const Fraction & other) {
        if(this->denominator == other.denominator) {
            return this->numerator <= other.numerator;
        } else {
            return (this->numerator * other.denominator) <= (other.numerator * this->denominator);
        }
    }
    bool operator >=(const Fraction & other) {
        if(this->denominator == other.denominator) {
            return this->numerator >= other.numerator;
        } else {
            return (this->numerator * other.denominator) >= (other.numerator * this->denominator);
        }
    }

    double  getNumeratot () {
          return numerator;
        }
    double  getDenominator () {
          return denominator;
        }
};

// lesson 4

class Card {
private:
    bool position;
    enum color{};
    enum value{};
public:
    Card() {

    }
    bool flip() {
        if(position == 1) {
            position = 0;
            return  position;
        } else {
            position = 1;
            return position;
        }
    }
    //int getValue() {
      //  return value;
    //}
};

int main(int argc, char const *argv[]) {
// lesson 1
   Circle a(5);
   a.area();
   Parallelogram b(4, 3.2);
   b.area();
   Rectangle c(4, 3);
   c.area();
   Square d(4);
   d.area();
   Rhombus e(2.4, 4.4);
   e.area();

 // lesson 2
    Car car1("Toyota", "Corolla");
    car1.getCar();
    PassengerCar car2("BMW", "5-series");
    car2.getCar();
    Bus car3("Man", "TGS");
    car3.getCar();
    Minivan car4("MB", "V-class"); // если я правильно понял здесь у нас "алмаз смерти"
    car4.getCar();

// lesson 3
    Fraction f1(3, 4);
    std::cout << f1.getNumeratot() << " / " << f1.getDenominator() << std::endl;
    Fraction f2(2, 5);
    std::cout << f2.getNumeratot() << " / " << f2.getDenominator() << std::endl;
    Fraction fsum = f1 + f2;
    std::cout << fsum.getNumeratot()<< " / " << fsum.getDenominator() << std::endl;
    Fraction fdiff = f1 - f2;
    std::cout << fdiff.getNumeratot()<< " / " << fdiff.getDenominator() << std::endl;
    Fraction fmult = f1 * f2;
    std::cout << fmult.getNumeratot()<< " / " << fmult.getDenominator() << std::endl;
    Fraction fdiv = f1 / f2;
    std::cout << fdiv.getNumeratot()<< " / " << fdiv.getDenominator() << std::endl;
    bool result1 = f1 == f2;
    std::cout << result1 << std::endl;
    bool result2 = f1 != f2;
    std::cout << result2 << std::endl;
    bool result3 = f1 < f2;
    std::cout << result3 << std::endl;
    bool result4 = f1 > f2;
    std::cout << result4 << std::endl;
    bool result5 = f1 <= f2;
    std::cout << result5 << std::endl;
    bool result6 = f1 >= f2;
    std::cout << result6 << std::endl;
  return 0;
}
