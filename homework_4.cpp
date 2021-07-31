#include "ArrayInt.h"

// lesson 2
void comparsion (std::vector<int> Arr) {
    std::sort(Arr.begin(), Arr.end()); // сортируем для удобства
    int temp = 0;
    for (int i = 0; i < Arr.size(); i++) {
        temp = Arr[i];
       if (Arr[i - 1] == temp) {
           Arr.erase(Arr.begin() + i); // удаляем схожие элементы
       }
    }
    std::cout << Arr.size() << std::endl; // итоговая размерность и есть наше количество различных занчений
}

void prAr (std::vector<int> Arr) { // print vector
    for (int i = 0; i < Arr.size(); i++) {
    std::cout << Arr[i] << " ";
    }
    std::cout << std::endl;
}

// lesson 3

class Card {
private:
    bool m_IsFaceUp;
    enum m_Suit{diamonds, hearts, clubs, spades};
    enum m_Rank{two, tree, four, five, six, seven, eight, nine, ten, jack, queen, king, ace};
public:
    Card() {
        // не могу разобраться как вытягивать из enum рандомное значение, буду признателен если подскажете
    }
    bool flip() {
        if(m_IsFaceUp == 1) {
            m_IsFaceUp = 0;
            return  m_IsFaceUp;
        } else {
            m_IsFaceUp = 1;
            return m_IsFaceUp;
        }
    }
    int getValue() {
        return 0;
    }
};

class Hand {
private:
    std::vector<Card*> m_Cards;
public:
    void Add(Card* pCard){
        m_Cards.push_back(pCard);
    }
    void Clear() {
        m_Cards.clear();
    }
//    int getTotal () {
        // немного не понимаю как считать сумму карт
//        }
};

int main(int argc, char const *argv[]) {
// lesson 1
    ArrayInt arr{};
    arr.push_back(12);
    arr.push_back(2);
    arr.push_back(1);
    arr.push_back(14);
    arr.push_back(4);
    arr.printArrayInt();
    arr.pop_back(); // delete "4"
    arr.printArrayInt();
    arr.pop_front(); // delete "12"
    arr.printArrayInt();
    arr.erase();

// lesson 2

    std::vector<int> Array{2, 4, 2, 0, 5, 2};
    prAr(Array);
    comparsion(Array);

  return 0;
}
