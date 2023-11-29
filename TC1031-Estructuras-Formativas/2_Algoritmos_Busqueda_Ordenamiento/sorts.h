#ifndef SORTS_H
#define SORTS_H

#include <iostream>
#include <vector>
#include <list>
using namespace std;

template <class T>
class Sorts {
    private:
        void swap(vector<T> &v, int i, int ref);
        void copyArray(vector<T>&, vector<T>&, int, int);
        void mergeArray(vector<T>&v, vector<T>&B, int low, int mid, int high);
        void mergeSplit(vector<T>&v, vector<T>&B, int low, int high);
    public:
        void ordenaSeleccion(vector<T>&v);
        void ordenaBurbuja(vector<T>&v);
        void ordenaMerge(vector<T>&v);
       int busqSecuencial(const vector<T>&vec, int d);
        T busqBinaria(vector<T>&v, int value);
};

template <class T>
void Sorts<T>::swap(vector<T> &v, int i, int j){
    T aux = v[i];
    v[i] = v[j];
    v[j] = aux;
}

template <class T>
void Sorts<T>::ordenaSeleccion(vector<T> &v){
    int pos;
    for (int i = v.size() - 1; i > 0; i --){
        pos = 0;
        for (int j = 1; j <= i; j ++){
            if (v[j] > v[pos]){
                pos = j;
            }
        }
        if (pos != i){
            swap(v, i, pos);
        }
    }
}

template <class T>
void Sorts<T>::ordenaBurbuja(vector<T>&v){
    for (int i = v.size() - 1; i > 0; i --){
        for (int j = 0; j < i; j ++){
            if (v[j] > v[j + 1]){
                swap(v, j, j + 1);
            }
        }
    }
}

template <class T>
void Sorts<T>::copyArray(vector<T>&v, vector<T>&tmp, int low, int high){
    for (int i = low; i <= high; i++){
        v[i] = tmp[i];
    }
}

template <class T>
void Sorts<T>::mergeArray(vector<T>&v, vector<T>&B, int low, int mid, int high){
    int i, j, k;
    i = low;
    j = mid + 1;
    k = low;

    while(i <= mid && j <= high){
        if (v[i] < v[j]){
            B[k] = v[i];
            i ++;
        }
        else{
            B[k] = v[j];
            j ++;
        }
        k ++;
    }
    if (i > mid){
        for (; j <= high; j++){
            B[k++] = v[j];
        }
    }
    else{
        for (; i <= mid; i++){
            B[k++] = v[i];
        }
    }
}

template <class T>
void Sorts<T>::mergeSplit(vector<T>&A, vector<T>&B, int low, int high){
    int mid;

    if ((high - low) < 1){
        return;
    }
    mid = (high + low) / 2;
    mergeSplit(A, B, low, mid);
    mergeSplit(A, B, mid + 1, high);
    mergeArray(A, B, low, mid, high);
    copyArray(A, B, low, high);
}

template <class T>
void Sorts<T>::ordenaMerge(vector<T>&vec){
    vector<T> tmp(vec.size());
    mergeSplit(vec, tmp, 0, vec.size() - 1);
}

template <class T>
int Sorts<T>::busqSecuencial(const vector<T>&vec, int d){
    for(int i = 1; i < vec.size(); i ++){
        if (d == vec[i]){
            return i;
        }
    }
    return -1;
}


template <class T>
T Sorts<T>::busqBinaria(vector<T>&v, int value){
    ordenaMerge(v);
    int i = 0;
    int j = v.size();
    while (i <= j){
        int mid = (i + j) / 2;
        if (value == v[mid]){
            return mid;
        }
        else if (value > v[mid]){
            i = mid + 1;
        }
        else if (value < v[mid]){
            j = mid - 1;
        }
    }
    return -1;
}

#endif