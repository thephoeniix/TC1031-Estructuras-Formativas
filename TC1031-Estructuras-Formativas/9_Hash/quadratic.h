#ifndef HASH_H
#define HASH_H

#include <string>
#include <sstream>

using namespace std;

template <class Key, class Value>
class Quadratic {
    private:
		unsigned int (*func) (const Key);
		unsigned int size;
		unsigned int count;
		Key *keys;
		Key initialValue;
		Value *values;
		long indexOf(const Key) const;

    public: 
        Quadratic(unsigned int, Key, unsigned int (*f) (const Key));
		~Quadratic();
		string toString() const; 
        bool put(Key, Value);
		Value get(const Key);
};

template <class Key, class Value>
Quadratic<Key, Value>::Quadratic(unsigned int s, Key init, unsigned int (*f) (const Key)) {
	size = s;
	keys = new Key[size];
	initialValue = init;
	for (unsigned int i = 0; i < size; i++) {
		keys[i] = init;
	}
	values = new Value[size];
	for (int i = 0; i < s; i++) {
		values[i] = 0;
	}
	func = f;
	count = 0;
}

template <class Key, class Value>
Quadratic<Key, Value>::~Quadratic() {
	delete [] keys;
	keys = 0;
	delete [] values;
	values = 0;
	size = 0;
	func = 0;
	count = 0;
}

template <class Key, class Value>
long Quadratic<Key, Value>::indexOf(const Key k) const {
	unsigned int i, start;
	start = i = func(k) % size;
	do {
		if (keys[i] == k) {
			return i;
		}
		i = (i + 1) % size;
	}
	while (start != i);
	return -1;
}

template <class Key, class Value>
bool Quadratic<Key, Value>::put(Key k, Value v) {
	unsigned int i, start;
	long pos;

	pos = indexOf(k);
	if (pos != -1) {
		values[pos] = v;
		return true;
	}
	start = i = func(k) % size;
	do {
		if (keys[i] == initialValue) {
			keys[i] = k;
			values[i] = v;
			return true;
		}
		count++;
		i = (i + (count*count)) % size;
	}
	while (start != i);
	return false;
}

template <class Key, class Value>
Value Quadratic<Key, Value>::get(const Key k) {
	unsigned int i, start;
	long pos;
	pos = indexOf(k);
	if (pos != -1) {
		return values[pos];
	}
	return -1;
}

template <class Key, class Value>
string Quadratic<Key, Value>::toString() const {
	stringstream aux;
	for (int i = 0; i < size; i++){
			if (keys[i] != initialValue){
				aux << "(" << i << " ";
			  aux << keys[i] << " : " << values[i] << ") ";
			}
	}
	return aux.str();
}

#endif