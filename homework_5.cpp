#include <iostream>
#include <vector>

// lesson 1
template<typename  Type>

class Pair1 {
private:
    Type fValue;
    Type sValue;
public:
    Pair1 (Type m_fValue, Type m_sValue) {
        fValue = m_fValue;
        sValue = m_sValue;
    }

    Type first () const {
        return fValue;
    }

    Type second () const {
        return sValue;
    }
};

// lesson 2

template<typename T1, typename T2>

class Pair {
private:
    T1 fValue;
    T2 sValue;
public:
    Pair (T1 m_fValue, T2 m_sValue) {
        fValue = m_fValue;
        sValue = m_sValue;
    }

     T1 first () const  {
        return fValue;
    }

    T2 second () const {
        return sValue;
    }
};

// lesson 3

template<typename  T>

class StringValuePair: public Pair<std::string, T> {
public:
    StringValuePair (std::string fv, T sv) : Pair<std::string, T> (fv, sv) {
    }
};

// lesson 4

class Card {
private:
    bool m_IsFaceUp;
    enum m_Suit{diamonds, hearts, clubs, spades};
    enum m_Rank{two, tree, four, five, six, seven, eight, nine, ten, jack, queen, king, ace};
public:
    Card() {

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
    int getTotal () {
        return 0;
        }
};

class GenericPlayer : public Hand {
private:
    std::string m_Name;
public:
    virtual bool IsHitting() const {
        return 0;
    }
    bool IsBoosted() const {
        return 0;
    }
    void Bust() const {
        std::cout << m_Name << " more 21" << std::endl;
    }
};

int main(int argc, char *argv[]) {
// lesson 1
    Pair1<int> p1(6, 9);
        std::cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';

    const Pair1<double> p2(3.4, 7.8);
        std::cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';

// lesson 2
    Pair<int, double> p3(6, 7.8);
        std::cout << "Pair: " << p3.first() << ' ' << p3.second() << '\n';

    const Pair<double, int> p4(3.4, 5);
        std::cout << "Pair: " << p4.first() << ' ' << p4.second() << '\n';

// lesson 3
        StringValuePair<int> svp("Amazing", 7);
            std::cout << "Pair: " << svp.first() << ' ' << svp.second() << '\n';
    return 0;
}

