#ifndef ARRAYINT_H
#define ARRAYINT_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>

class ArrayInt {
private:
    int m_length;
    int *m_data;

public:
    ArrayInt(): m_length(0), m_data(nullptr) {

    }

    ArrayInt(int length):
    m_length(length) {

        assert(length >= 0);

        if (length > 0) {
            m_data = new int[length];
        } else {
            m_data = nullptr;
        }
    }

    ~ArrayInt() {
        delete[] m_data;
    }

    void erase() {
            delete[] m_data;
            m_data = nullptr;
            m_length = 0;
        }

    int getLenght () const { // размер массива
        return m_length;
    }

    int& operator [](int index){
        assert(index >= 0 && index < m_length);
        return m_data[index];
    }

    void resize (int newLength) { // меняем размер массива
        if (m_length == newLength) {
            return;
        }

        if (newLength <= 0) {
            erase();
            return;
        }

        int *data = new int[newLength];

        if (m_length > 0) {
            int elementsToCopy = newLength > m_length ? m_length : newLength;
            for (int i = 0; i < elementsToCopy; i++) {
                data[i] = m_data[i];
            }
        }

        delete[] m_data;
        m_data = data;
        m_length = newLength;
    }

    void insertBefore(int value, int index){ // вставка элемента с определенным индексом
        assert(index >= 0 && index <= m_length);
        int *data = new int[m_length + 1];
        for(int i = 0; i < index; i++) {
            data[i] = m_data[i];
        }
        data[index] = value;

        for(int i = index; i < m_length; i++){
            data[i + 1] = m_data[i];
        }

        delete [] m_data;
        m_data = data;
        ++m_length;
    }

    void push_back(int value) { //вставка элемента в конец
        insertBefore(value, m_length);
    }

    // lesson 1
    void pop_back() { // delet last element
        int value = 0;
        int index = m_length;
        int *data = new int[m_length - 1];
        for(int i = 0; i < index; i++) {
            data[i] = m_data[i];
        }
        data[index] = value;

        for(int i = index; i < m_length; i++){
            data[i - 1] = m_data[i];
        }

        delete [] m_data;
        m_data = data;
        --m_length;
    }

    void pop_front () { // delete first element
        int value = 0;
        int index = m_length;
        int *data = new int[m_length - 1];
        for(int i = 0; i < index; i++) {
            data[i] = m_data[i + 1];
        }
        data[index] = value;

        for(int i = index; i < m_length; i++){
            data[i - 1] = m_data[i];
        }

        delete [] m_data;
        m_data = data;
        --m_length;
    }

    void printArrayInt () { // print array
        for (int i = 0; i < m_length; i ++) {
            std::cout << m_data[i] << " ";
        }
        std::cout << std::endl;
    }

    void maxSort () { //
    }

};

#endif // ARRAYINT_H
