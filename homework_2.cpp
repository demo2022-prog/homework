#include <iostream>
#include <cstdio>

// Lesson 1
class Person { // Родительский класс
public:
  std::string name;
  int age;
  int mass;

  Person(std::string m_name, int m_age, int m_mass) { // Базовый конструктор
    name = m_name;
    age = m_age;
    mass = m_mass;
  }

  void reName(std::string m_name) { // Переназначение
    name = m_name;
  }
  void reAge(int m_age) { // Переназначение
    age = m_age;
  }
  void reMass(int m_mass) { // Переназначение
    mass = m_mass;
  }

  void printPerson() { // Вывод объекта
    std::cout << name << " " << age << " " << mass << std::endl;
  }
};

class Stydent : public Person {
private:
  int year;

public:
  Stydent(std::string m_name, int m_age, int m_mass, int m_year) : Person(m_name, m_age, m_mass) { // Конструктор дочернего класса на основе Базового конструктора
    year = m_year;
  }

  void reYear(int i_year) { // Переназначение
    year = i_year;
  }

  void printStydent() { // Вывод объекта
    std::cout << name << " " << age << " " << mass << " " << year << std::endl;
  }
};

// Lesson 2
class Fruit { // Родительский класс
public:
  std::string name;
  std::string color;

  Fruit(std::string m_color, std::string m_name) { // Базовый конструктор
    name = m_name;
    color = m_color;
  }

   std::string getName() {
    return name;
  }
   std::string getColor() {
    return color;
  }
};

class Apple : public Fruit {
public:

Apple(std::string m_color = "Green", std::string m_name = "Apple") : Fruit(m_color, m_name) {}
};

class Banana : public Fruit {
public:
  Banana(std::string m_color = "Yellow", std::string m_name = "Banana") : Fruit(m_color, m_name) {}
};

class GrannySmith : public Apple {
public:
  GrannySmith(std::string m_color = "Green", std::string m_name = "Granny Smith") : Apple(m_color, m_name) {}
};

int main(int argc, char const *argv[]) {
  // Lesson 1
 Person anton("Anton", 20, 65);
  anton.printPerson();

  Stydent ivan("Ivan", 21, 70, 2012);
  Stydent semen("Semin", 24, 68, 2015);
  semen.printStydent();

  semen.reYear(2014);
  semen.reName("Semen");
  semen.printStydent();

  // Lesson 2
  Apple a("red");
      Banana b;
      GrannySmith c;

      std::cout << "My " << a.getName() << " is " << a.getColor() << ".\n";
      std::cout << "My " << b.getName() << " is " << b.getColor() << ".\n";
      std::cout << "My " << c.getName() << " is " << c.getColor() << ".\n";
  return 0;
}
