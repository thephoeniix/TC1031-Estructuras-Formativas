#ifndef HEAP_H
#define HEAP_H

#include <string>
#include <sstream>
#include <iostream>
using namespace std;

template <class T>
class Heap {
    private:
        T *data;
        unsigned int cant;
        unsigned int parent(unsigned int pos) const;
        unsigned int left(unsigned int pos) const;
        unsigned int right(unsigned int pos) const;
        void heapify(unsigned int);
        void swap(unsigned int first, unsigned int next);

    public:
        unsigned int size1;
        Heap(unsigned int s);
        ~Heap();
        bool empty() const;
        void push(T val);
        void pop();
        int top();
        int size();
        string toString() const;
};

template <class T>
Heap<T>::Heap(unsigned int s) {
    size1 = s;
    data = new T[size1];
    cant = 0;
}

template <class T>
Heap<T>::~Heap() {
    delete [] data;
    data = 0;
    size1 = 0;
    cant = 0;
}

template <class T>
bool Heap<T>::empty() const {
    return(cant == 0);
}

template <class T>
unsigned int Heap<T>::parent(unsigned int pos) const {
    return (pos - 1) / 2;
}

template <class T>
unsigned int Heap<T>::left(unsigned int pos) const {
    return ((2 * pos) + 1);
}

template <class T>
unsigned int Heap<T>::right(unsigned int pos) const {
    return ((2 * pos) + 2);
}

template <class T>
void Heap<T>::swap(unsigned int first, unsigned int next) {
    T aux = data[first];
    data[first] = data[next];
    data[next] = aux;
}

template <class T>
void Heap<T>::heapify(unsigned int pos) {
    unsigned int l = left(pos);
    unsigned int r = right(pos);
    unsigned int min = pos;

    if(l <= cant && data[l] < data[min]) {
        min = l;
    }
    if (min != pos) {
        swap(pos, min);
        heapify(min);
    }
}

template <class T>
void Heap<T>::push(T val) {
    unsigned int pos;
    pos = cant;
    cant ++;
    while (pos > 0 && val < data[parent(pos)]) {
        data[pos] = data[parent(pos)];
        pos = parent(pos);
    }
    data[pos] = val;
}

template <class T>
void Heap<T>::pop() {
    T aux = data[0];
    data[0] = data[--cant];
    heapify(0);
}

template <class T>
int Heap<T>::top() {
    if (empty()) {
        return -1;
    }
    return data[0];
}

template <class T>
int Heap<T>::size() {
    return cant;
}

template <class T>
std::string Heap<T>::toString() const {
	std::stringstream aux;
	aux << "[";	for (unsigned int i = 0; i < cant; i++) {
		if (i != 0) {
			aux << " ";
		} aux << data[i];
	} aux << "]";
	return aux.str();
}

#endif
