#ifndef LINKEDL_H
#define LINKEDL_H

#include <string>
#include <sstream>
using namespace std;

template <class T> class DList;

template <class T>
class DLink {
    private:
        DLink(T);
        DLink(T, DLink<T>*, DLink<T>*);
        DLink(const DLink<T>&);
        T value;
        DLink<T> *previous;
        DLink<T> *next;
        friend class DList<T>;
};

template <class T>
DLink<T>::DLink(T data) : value(data), previous(0), next(0) {};

template <class T>
DLink<T>::DLink(T data, DLink<T> *pdata, DLink<T> *ndata) : value(data), previous(pdata), next(ndata) {};

template <class T>
DLink<T>::DLink(const DLink<T> &nd) : value(nd.next), previous(nd.previous), next(nd.next) {};

template <class T>
class DList {
    public:
        DList();
        DList(const DList<T>&);
        void insertion(T data);
        int search(T data);
        void update(int index, T data);
        T removeFirst();
        T deleteAt(int index);
        string toStringForward() const;
        string toStringBackward() const;
    private:
        DLink<T> *head;
        DLink<T> *tail;
        int size;
};

template <class T>
DList<T>::DList() : head(0), tail(0), size(0) {};

template <class T>
string DList<T>::toStringBackward() const {
	stringstream aux;
	DLink<T> *p;

	p = head;
	aux << "[";
	while (p != 0) {
		aux << p->value;
		if (p->next != 0) {
			aux << ", ";
		}
		p = p->next;
	}
	aux << "]";
	return aux.str();
}

template <class T>
string DList<T>::toStringForward() const {
	stringstream aux;
	DLink<T> *p;

	p = tail;
	aux << "[";
	while (p != 0) {
		aux << p->value;
		if (p->previous != 0) {
			aux << ", ";
		}
		p = p->previous;
	}
	aux << "]";
	return aux.str();
}

template <class T>
void DList<T>::insertion(T data){
    DLink<T> *newData;
    newData = new DLink<T>(data);
    if(size == 0){
        head = newData;
        tail = newData;
    }
    else{
        newData -> next = head;
        head -> previous = newData;
        head = newData;
    }
    size ++;
}

template <class T>
int DList<T>::search(T data){
    int pos = 0;
    DLink<T> *nd;

    nd = tail;
    while(nd != 0){
        if(nd -> value == data){
            return pos;
        }
        nd = nd -> previous;
        pos ++;

    }
    return -1;
}

template <class T>
void DList<T>::update(int index, T data){
    int pos = 0;
    DLink<T> *nd;

    nd = tail;
    while(nd != 0){
        if(pos == index){
            nd -> value = data;
            break;
        }
        nd = nd -> previous;
        pos ++;
    }
}

template <class T>
T DList<T>::removeFirst(){
    T data;
    DLink<T> *nd;
    nd = tail;
    data = nd -> value;

    if(tail == head){
        head = 0;
        tail = 0;
    }
    else{
        tail = nd -> previous;
        nd -> previous -> next = 0;
    }
    delete nd;
    size --;
    return data;
}

template <class T>
T DList<T>::deleteAt(int index){
    int pos = 0;
    T data;
    DLink<T> *nd;

    if(index == 0){
        return removeFirst();
    }
    nd = tail;
    while(pos != index){
        nd = nd -> previous;
        pos ++;
    }
    data = nd -> value;
    nd -> next -> previous = nd -> previous;
    if(nd -> previous != 0){
        nd -> previous -> next = nd -> next;
    }
    size --;
    delete nd;
    return data;
}

#endif