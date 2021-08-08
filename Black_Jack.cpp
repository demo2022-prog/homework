#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include<algorithm>

class Card {
public:
    enum suit{diamonds, hearts, clubs, spades};
    enum rank{two, tree, four, five, six, seven, eight, nine, ten, jack = 10, queen = 10, king = 10, ace = 1};

    Card(rank r = ace, suit s = spades, bool ifu = true);

        void Flip() {
            m_isFaceUp = !m_isFaceUp;
        }

        int GetValue() const {
            int value = 0;
            if (m_isFaceUp) {
                value = m_Rank;
            }
                if (value > 10) {
                    value = 10;
                 }
             return value;
        }

friend std::ostream& operator<<(std::ostream& os, const Card& aCard);

private:
    bool m_isFaceUp;
    suit m_Suit;
    rank m_Rank;
};

Card::Card(rank r, suit s, bool ifu) : m_Rank(r), m_Suit(s), m_isFaceUp(ifu) {}

std::ostream& operator<<(std::ostream& os, const Card& aCard) {
    const std::string RANKS[] = { "0", "A", "2", "3", "4", "5", "6", "7", "8", "9","10", "J", "Q", "K" };
    const std::string SUITS[] = { "c", "d", "h", "s" };

    if (aCard.m_isFaceUp) {
        os << RANKS[aCard.m_Rank] << SUITS[aCard.m_Suit];
    }
    else {
        os << "XX";
    }
    return os;
}


class Hand {
protected:
    std::vector<Card*> m_Cards;
public:
    Hand() { m_Cards.reserve(7); }

    virtual ~Hand() {
        Clear();
    }

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

            int total = 0;
            std::vector<Card*>::const_iterator iter;
            for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter) {
                total += (*iter)->GetValue();
            }

            bool containsAce = false;
            for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter) {
                if ((*iter)->GetValue() == Card::ace) {
                    containsAce = true;
                }
            }

            if (containsAce && total <= 11) {
                total += 10;
            }

            return total;
    }

};

class GenericPlayer : public Hand {
protected:
    std::string m_Name;
public:
    GenericPlayer(const std::string& name = "");

    virtual ~GenericPlayer();

    virtual bool IsHitting() = 0;

    bool IsBusted() const;

    void Bust() const;

friend std::ostream& operator<<(std::ostream& os, const GenericPlayer& aGenericPlayer);

};

GenericPlayer::GenericPlayer(const std::string& name) : m_Name(name){}
GenericPlayer::~GenericPlayer() {}

bool GenericPlayer::IsBusted() const {
    return (GetTotal() > 21);
}

void GenericPlayer::Bust() const {
    std::cout << m_Name << " busts.\n";
}

std::ostream& operator<<(std::ostream& os, const GenericPlayer& aGenericPlayer) {
    os << aGenericPlayer.m_Name << ":\t";

    std::vector<Card*>::const_iterator pCard;
    if (!aGenericPlayer.m_Cards.empty()) {
        for (pCard = aGenericPlayer.m_Cards.begin(); pCard != aGenericPlayer.m_Cards.end(); ++pCard) {
            os << *(*pCard) << "\t";
        }


        if (aGenericPlayer.GetTotal() != 0) {
            std::cout << "(" << aGenericPlayer.GetTotal() << ")";
        }
    } else {
        os << "<empty>";
    }

    return os;
}



class Player : public GenericPlayer {
public:
    Player(const std::string& name = "");

    virtual ~Player();

    virtual bool IsHitting() const ;

    void Win() const {
        std::cout << "Player " << m_Name << " is Win!" << std::endl;
    }
    void Lose() const {
        std::cout << "Player " << m_Name << " is Lose!" <<std::endl;
    }
    void Push() const {
        std::cout << "Player " << m_Name << " played a draw!" << std::endl;
    }
};

bool Player::IsHitting() const {
    std::cout << m_Name << ", do you want a hit? (Y/N): ";
    char response;
    std::cin >> response;
    return (response == 'y' || response == 'Y');
}


class House : public GenericPlayer {
public:
    House(const std::string& name = "House");

    virtual ~House();

    virtual bool IsHitting() const {
        return (GetTotal() <= 16);
    }

    void FlipFirstCard() {
        if (!(m_Cards.empty())) {
            m_Cards[0]->Flip();
        } else {
            std::cout << "No card to flip!\n";
        }
    }
};

class Deck : public Hand {
public:
    Deck();

    virtual ~Deck();

    void Populate();

    void Shuffle() {
        std::random_shuffle(m_Cards.begin(), m_Cards.end());
    }

    void Deal(Hand& aHand) {
        if (!m_Cards.empty()) {
            aHand.Add(m_Cards.back());
            m_Cards.pop_back();
        }
        else {
            std::cout << "Out of cards. Unable to deal.";
        }
    }

    void AdditionalCards(GenericPlayer& aGenericPlayer) {
        std::cout << std::endl;
           while (!(aGenericPlayer.IsBusted()) && aGenericPlayer.IsHitting()) {
               Deal(aGenericPlayer);
               std::cout << aGenericPlayer << std::endl;

               if (aGenericPlayer.IsBusted()) {
                   aGenericPlayer.Bust();
               }
           }

    }
};

Deck::Deck() {
    m_Cards.reserve(52);
    Populate();
}

Deck::~Deck() {}

void Deck::Populate() {
    Clear();
    // создает стандартную колоду
    for (int s = Card::clubs; s <= Card::spades; ++s) {
        for (int r = Card::ace; r <= Card::king; ++r) {
            Add(new Card(static_cast<Card::rank>(r),
                         static_cast<Card::suit>(s)));
        }
    }
}


class Game {
public:
    Game(const std::vector<std::string>& names) {
           std::vector<std::string>::const_iterator pName;
           for (pName = names.begin(); pName != names.end(); ++pName) {
               m_Players.push_back(Player(*pName)); // сдесь ругается: /home/dmitri/Black_Jack/main.cpp:265: error: allocating an object of abstract class type 'Player'
           }

           srand(static_cast<unsigned int>(time(0)));
           m_Deck.Populate();
           m_Deck.Shuffle();

    }

    ~Game() {}

    void Play() {
        std::vector<Player>::iterator pPlayer;
        for (int i = 0; i < 2; ++i) {
            for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer) {
                m_Deck.Deal(*pPlayer);
            }
            m_Deck.Deal(m_House);
        }

        m_House.FlipFirstCard();

        for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer) {
            std::cout << *pPlayer << std::endl;
        }
        std::cout << m_House << std::endl;

        for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer) {
            m_Deck.AdditionalCards(*pPlayer);
        }

        m_House.FlipFirstCard();
        std::cout << std::endl << m_House;

        m_Deck.AdditionalCards(m_House);

        if (m_House.IsBusted()) {
            for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer) {
                if (!(pPlayer->IsBusted())) {
                    pPlayer->Win();
                }
            }
        }
        else {
            for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer) {
                if (!(pPlayer->IsBusted())) {
                    if (pPlayer->GetTotal() > m_House.GetTotal()) {
                        pPlayer->Win();
                    } else if (pPlayer->GetTotal() < m_House.GetTotal()) {
                        pPlayer->Lose();
                    } else {
                        pPlayer->Push();
                    }
                }
            }
        }

        for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer) {
            pPlayer->Clear();
        }
        m_House.Clear();

    }

private:
    Deck m_Deck;
    House m_House; // сдесь ругается: /home/dmitri/Black_Jack/main.cpp:331: error: field type 'House' is an abstract class
    std::vector<Player> m_Players;

};

int main() {
    return 0;
}
