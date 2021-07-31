#include <iostream>
#include <string>
#include<iomanip>
#include<cstdio>

// lesson 1
template<class T>
T input_user(const char* promt) {
    T a;
    std::cout << promt;
    std::cin >> a;

    while (std::cin.fail() || std::cin.get() != '\n') {
        std::cin.clear();
        std::cin.ignore(9999, '\n');
        std::cin.sync();
        std::cout << "Error!\n" << promt; std::cin >> a;
    }
    return a;
};

// lesson 2
std::ostream& endll(std::ostream& stream) {
   stream << '\n' << '\n';
   return stream;
}

// lesson 3 and lesson 4 вынесены в отдельный файл для игры Black Jack Black_Jack.cpp


int main() {
// lesson 1
   std::cout << input_user<int>("Enter the number: ") << /*lesson 2*/ endll;

   return 0;
}
