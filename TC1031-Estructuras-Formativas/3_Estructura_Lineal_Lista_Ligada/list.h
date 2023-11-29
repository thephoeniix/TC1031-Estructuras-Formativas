#ifndef LIST_H_
#define LIST_H_


#include <list>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

template<class T> class List;
template<class T> class ListIterator;

template <class T>
class Link { // linked list 
private:
	Link(T);
	Link(T, Link<T>*);
	Link(const Link<T>&);

	T	    value; // object (value), type: template<class T> (create the next object) 
	Link<T> *next; // pointer to the next element

	friend class List<T>; // solo los amigos pueden acceder. 
	friend class ListIterator<T>; //aquí se validaria. 
};

template <class T>
Link<T>::Link(T val) : value(val), next(0) {}

template <class T>
Link<T>::Link(T val, Link* nxt) : value(val), next(nxt) {} 

template <class T>
Link<T>::Link(const Link<T> &source) : value(source.value), next(source.next) {} 

template <class T>	
class List{
    public:
        List();
        List(const List<T>&) ;
        ~List();
        
        string toString() const;
        bool empty() const;
        void clear();
        
        void insertion(T);
        int search(T);
        void update(int, T);
        T deleteAt(int);
       
        int  length() const;
        bool contains(T) const;
       
        T getLast() const;
        bool compare(const List<T>&) const;

    private:
        Link<T> *head;
        Link<T> *tail;
        int 	size;

        friend class ListIterator<T>;


};

template <class T>
List<T>::List() : head(0), size(0) {} //empty list (NO ELEMENTS IN THE LIST!!!!)
template <class T>
void List<T>::clear() {
	Link<T> *p, *q; //p recorre lista 
					//q elimina 

	p = head; //inicia en 0
	while (p != 0) {  
		q = p->next; //q es el siguiente de p  
		delete p; // se borra p 
		p = q; //p se vuelve otra vez head 
	}
	head = 0; //que no apunte a null para garantizar que ya no hay nada
	size = 0; //garantizas que el tamaño es null 
}

template <class T>
List<T>::~List() {
	clear(); // EL DESTRUCTOR, LIBERAR LA MEMORIA 
}


template <class T>
bool List<T>::empty() const {
	return (head == 0); // validate there are no elements
}

template <class T>
int List<T>::length() const {
	return size; // get length of the list
}

template <class T> // search if there is the "val" 
bool List<T>::contains(T val) const {
	Link<T> *p; // pointer to the head of the list

	p = head; //pointer starts with head
	while (p != 0) {  
		if (p->value == val) {
			return true; 
		}
		p = p->next;
	}
	return false; //
}

template <class T>
void List<T>::insertion(T value) {
   Link<T> *newLink = new Link<T>(value); 

        newLink->value = value;
        newLink->next = nullptr;

        if (head == nullptr) {
            head = newLink;
            tail = newLink;
        } else {
            tail->next = newLink;
            tail = newLink;
        }
}

template <class T>
int List<T>::search(T value){
    Link<T> *p;
    int pos = 0;

	p = head;
    while (p!=0){
        if (p->value == value){
            return pos;
        }
        p=p->next;
        pos++;
    }

    return -1;

}

template <class T>
void  List<T>::update(int index, T value){
    Link<T> *p;


    if (index < 0 || index >= size) {
        cout<<"Out of Bounds"<<endl;
        }
    
	p = head;
	int pos = 0;
	while (pos != index) {
		p = p->next;
		pos++;
	}
	p->value = value; 
    
}


template <class T>
string List<T>::toString() const {
	std::stringstream aux;
	Link<T> *p;

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
T List<T>::deleteAt(int index){
	Link<T> *p, *q;
    T value;
    int pos=0;

    if (index < 0 || index >= size) {
		cout<<"Out of Bounds"<<endl;
	}
    
    if (index == 0) {
        p = head;
        value = p->value;
        head = p->next; 
        delete p; 
    } else {
        p = head;
        pos = 0;
        while (pos != index) {
            q = p;
            p = p->next;
            pos++;
        }

        value = p->value;
        q->next = p->next;
        delete p;
	
    }

    size--;
    return value;

 }



#endif /* LIST_H_ */
