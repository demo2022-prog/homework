#include <clocale>
#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cstdint>
#include <cassert>
#include <algorithm>
#include <set>
#include <iomanip>	
#include <sstream>

class Card {
public:
    enum Suit{diamonds, hearts, clubs, spades};
    enum Rank{two, tree, four, five, six, seven, eight, nine, ten, jack = 10, queen = 10, king = 10, ace = 1};

    Card(Rank rank, Suit suit, bool ifu) : m_Rank(rank), m_Suit(suit), m_isFaceUp(ifu) {}

        void Flip() {
            m_isFaceUp = !m_isFaceUp;
        }

        int GetValue() {

            int value = 0;
            if (m_isFaceUp) {
                value = m_Rank;
            }
            return value;
        }

private:
    bool m_isFaceUp;
    Suit m_Suit;
    Rank m_Rank;
};

class Hand {
protected:
    std::vector<Card*> m_Cards;
public:
    Hand() { m_Cards.reserve(7); }

    virtual ~Hand();


    void Add(Card* pCard) {
        m_Cards.push_back(pCard);
    }

    void Clear() {
        std::vector<Card*>::iterator iter = m_Cards.begin();
        for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter) {
            delete* iter;
            *iter = 0;
        }
        m_Cards.clear();

    }

    int GetTotal() const {
        if (m_Cards.empty()) {
            return 0;
        }
        if (m_Cards[0]->GetValue() == 0) {
            return 0;
        }
        int sum{ 0 };

        for (auto card : m_Cards) {
            sum += card->GetValue();
        }
        bool containsAce = false;

    for (auto card : m_Cards) {
        if (card->GetValue() == Card::ace) {
            containsAce = true;
        }
        if (containsAce && sum <= 11) {
            sum += 10;
        }
    }
        return sum;
    }
};

class Deck : public Hand {

};

class GenericPlayer : protected Hand {
protected:
    std::string m_name;
public:
    GenericPlayer(std::string name) : m_name(name) {}

    virtual bool IsHitting() = 0;

    bool IsBoosted() {
        if (GetTotal() > 21) {
            return true;
        } else {
            return false;
            }
    }

    void Bust() {
        std::cout << m_name << " has too many points!" << std::endl;
    }

    friend std::ostream& operator<< (std::ostream& print, GenericPlayer& gp) {
        print << "Player: " << gp.m_name << "\n" << "Cards:\n";
        for (auto c : gp.m_Cards) {
                print << c << "\n";
        }
            print << "Total: " << gp.GetTotal();
            return print;
        }
};

class Player : public GenericPlayer {
public:
    Player(std::string name) :GenericPlayer(name){}
    virtual bool IsHitting() const {
        if (GetTotal() < 21) {
            char answer;
            std::cout << "Do you need another card ?  Y/N :  ";
            std::cin >> answer;
            if (answer == 'y' || 'Y') {
                return 1;
            } else {
                return 0;
            }
        }
        else
            return false;
    }
    void Win() const {
        std::cout << "Player " << m_name << " is Win!" << std::endl;
    }
    void Lose() const {
        std::cout << "Player " << m_name << " is Lose!" <<std::endl;
    }
    void Push() const {
        std::cout << "Player " << m_name << " played a draw!" << std::endl;
    }
};

class House : GenericPlayer {
public:
    virtual bool IsHitting() const {
        if (GetTotal() <= 16) {
            return 1;
        } else {
            return 0;
        }
    }

    void FlipFirstCard() {
        if(m_Cards[0]->GetValue() == 0) {
            m_Cards[0]->Flip();
        }
    }
};

class Game {

};

int main() {
    return 0;
}
