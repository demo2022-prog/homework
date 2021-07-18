#include <iostream>
#include <cstdint>

#define SIZE 10
// lesson 1
class Power {
private:
  double base; // Основание
  double extend; // Степень
  double result; // Результат
public:

  Power () { // Инициализируем значение по умолчанию
    base = 1;
    extend = 1;
    result = 0;
  }

  void set (double i_base, double i_extend) { // Присваиваем пользовательские значения
    base = i_base;
    extend = i_extend;
  }
  void calculate () { // Возводим в степень
    result = extend;
    for (size_t i = 2; i < extend; i++) {
      result = result * base;
    }
  }
  void printResult() { // Выводи результат
    std::cout << base << " ^ " << extend << " = " << result << std::endl;
  }
};

// lesson 2
class RGB {
private:
  uint8_t m_red;
  uint8_t m_green;
  uint8_t m_blue;
  uint8_t m_alpha;

public:

  RGB() { // Инициализируем значение по умолчанию
    m_red = 0;
    m_green = 0;
    m_blue = 0;
    m_alpha = 255;
  }

  RGB(uint8_t i_red, uint8_t i_green, uint8_t i_blue, uint8_t i_aplha) { // Присваиваем пользовательские значения
// Проверки решил опустить, т.к. компилятор не даст задать что то отличное от 0...255
    m_red = i_red;
    m_green = i_green;
    m_blue = i_blue;
    m_alpha = i_aplha;
  }

  void printColor() { // Выводи результат
    int a = m_red, b = m_green, c = m_blue, d = m_alpha; // Преобразуем типы для более понятного отображения (лично у меня с отображением char проблемы)
    std::cout << "red = " << a << " green = " << b << " blue = " << c << " alpha = " << d << std::endl;
    //std::cout << "red = " << m_red << " green = " << m_green << " blue = " << m_blue << " alpha = " << m_alpha << std::endl;
  }
};

// lesson 3
class Stack {
private:
  int arr[SIZE]; // Массив значений
  int cursor; // Указатель на текущий элемент

public:
  void reset () { // Обнуляем массив и ставим указатель на 0
    for (size_t i = 0; i < SIZE; i++) {
      arr[i] = 0;
    }
    cursor = 0;
  }

  void push(int val) {
    if (cursor > (SIZE - 1)) {
      std::cout << "Stack is empty" << std::endl;
    } else {
      arr[cursor] = val;
      cursor++;
      //print(); // Для проверки работоспособности
    }
  }

void pop() { // Вытягиваем текущее значение
  if (cursor == 0) {
    std::cout << "Stack is null" << std::endl; // Пусть по условию по другому, но так привычнее
  } else {
    cursor--; // Сдвигаем курсор на -1
    }
  }

  void print() {
    if (cursor == 0) {
      std::cout << "Stack is null" << std::endl; // Пусть по условию по другому, но так привычнее
    } else {
      std::cout << "( ";
      for (size_t i = 0; i < cursor; i++) {
        std::cout << arr[i] << " ";
      }
      std::cout << " )" << std::endl;
    }
  }
};

int main(int argc, char const *argv[]) {
// lesson 1
  Power test {};
  test.set(2, 4);
  test.calculate();
  test.printResult();

// lesson 2
  //RGB color {};
  RGB color (125, 65, 255, 10);
  color.printColor();

// lesson 3
  Stack stack;
  stack.reset();
  stack.print();

  stack.push(3);
  stack.push(7);
  stack.push(5);
  stack.print();

  stack.pop();
  stack.print();

  stack.pop();
  stack.pop();
  stack.print();



  return 0;
}
