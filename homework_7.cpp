#include <iostream>
#include<memory>

// lesson 1
class Date {
private:
   int day;
   int month;
   int year;
public:
   Date () {}
   Date(int m_day, int m_month, int m_year) {
       day = m_day;
       month = m_month;
       year = m_year;
   }

   ~Date () {}

   void rDay(int m_day) {day = m_day;}
   void rMonth(int m_month) {month = m_month;}
   void rYear(int m_year) {year = m_year;}

   int getDay () {return day;}
   int getMonth() {return month;}
   int getYear () {return year;}

   friend std::ostream& operator<< (std::ostream &out, const Date &date);
};

// первые указатели для практики сделал кастомными
template<class T>
class today {
   T* m_ptr;
public:
   today(T* ptr=nullptr)
      :m_ptr(ptr)
{}

   ~today() {
      delete m_ptr;
   }

   today(today& a)
       {
           m_ptr = a.m_ptr;
           a.m_ptr = nullptr;
       }

       today& operator=(today& a)
       {
           if (&a == this){
               return *this;
           }

           delete m_ptr;
           m_ptr = a.m_ptr;
           a.m_ptr = nullptr;
           return *this;
       }

   T& operator*() const { return *m_ptr; }
   T* operator->() const { return m_ptr; }
   bool isNull() const { return m_ptr == nullptr;  }
};

template<class T>
class date {
   T* m_ptr;
public:
   date(T* ptr=nullptr)
       :m_ptr(ptr)
 {}

   ~date() {
      delete m_ptr;
   }

   date(date& a)
       {
           m_ptr = a.m_ptr;
           a.m_ptr = nullptr;
       }

       date& operator=(date& a) {
           if (&a == this) {
               return *this;
           }

           delete m_ptr;
           m_ptr = a.m_ptr;
           a.m_ptr = nullptr;
           return *this;
       }

   T& operator*() const { return *m_ptr; }
   T* operator->() const { return m_ptr; }
   bool isNull() const { return m_ptr == nullptr;  }
};


std::ostream& operator<< (std::ostream &out, const Date &date) {
       out << "Date: " << date.day << ". " << date.month << ". " << date.year << "\n";
       return out;
   }

// lesson 2
// в этом задании использую шаблонные указатели

void dateComp (Date *ptr1, Date *ptr2) { // сравнение решил сделать в лоб
    if (ptr1->getYear() > ptr2->getYear()) {
        std::cout << *ptr1 << std::endl;
    } else  if (ptr1->getYear() < ptr2->getYear()){
        std::cout << *ptr2 << std::endl;
    } else  if (ptr1->getYear() == ptr2->getYear()){
        if (ptr1->getMonth() > ptr2->getMonth()) {
            std::cout << *ptr1 << std::endl;
        } else if (ptr1->getMonth() < ptr2->getMonth()) {
            std::cout << *ptr2 << std::endl;
        } else if (ptr1->getMonth() == ptr2->getMonth()) {
                if (ptr1->getDay() > ptr2->getDay()) {
                    std::cout << *ptr1 << std::endl;
                } else {
                    std::cout << *ptr2;
                }
        }
    }
}

void swapPtr (Date *ptr1, Date *ptr2) {
    Date newptr{};
    newptr = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = newptr;
}

int main(int argc, char const *argv[]) {
// lesson 1
    today<Date> ptr(new Date(4, 7, 2020));
    date<Date> newptr(new Date);
    std::cout << *ptr;
    ptr->rDay(5);
    ptr->rMonth(8);
    ptr->rYear(2021);
    std::cout << *ptr;
    *newptr = *ptr;
    std::cout << *ptr;
    std::cout << *newptr;

// lesson 2
    std::unique_ptr<Date> date1(new Date);
    date1->rDay(7);
    date1->rMonth(8);
    date1->rYear(2021);
    std::unique_ptr<Date> date2(new Date);
    date2->rDay(7);
    date2->rMonth(8);
    date2->rYear(2020);
    std::cout << *date1;
    std::cout << *date2 << std::endl;
    dateComp(date1.get(), date2.get());
    swapPtr(date1.get(), date2.get());
    std::cout << *date1;
    std::cout << *date2;
   return 0;
}

