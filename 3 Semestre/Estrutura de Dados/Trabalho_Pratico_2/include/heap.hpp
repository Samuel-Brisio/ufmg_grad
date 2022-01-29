#ifndef HEAPHPP
#define HEAPHPP

#include <iostream>
#include <array>
#include "heapsort_k.hpp"
#include "memlog.h"
#include "msgassert.h"


template <typename T>
class Heap {
    public:
        Heap(int n, int id);
        ~Heap();

        void insere(T &elem); // insere um elemento no vetor e o ordena
        T remove(); // remove o maior elemento do vetor, a.k.a ultímo elemento

        bool vazio();
        
        void imprimi(std::ostream &os = std::cout);

    private:
        int id;
        int max_tam;
        int tamanho;
        int inicio;
        int fim;
        T *arr;        
};

template <typename T>
Heap<T>::Heap(int n, int id) {
    this->id = id;
    max_tam = n;
    tamanho = 0;
    inicio = 0;
    fim = -1;
    this->arr = new T[n];
}

template <typename T>
Heap<T>::~Heap() {
    delete[] arr;
}


template <typename T>
void Heap<T>::insere(T &elem) {
    
    erroAssert(fim >= -1 && fim < max_tam, "Array cheio");
    
    fim++;
    tamanho++;
    arr[fim] = elem;
    escreveMemLog( (long int) &arr[fim], sizeof(T), id);
    heapSort(arr, fim + 1);
}

template <typename T>
T Heap<T>::remove() {
    
    erroAssert(fim >= -1 && tamanho >= 0, "array vazio");

    T aux = arr[fim];
    leMemLog((long int) &arr[fim], sizeof(T), id);
    fim--;
    tamanho--;
    return aux;
}

template <typename T>
void Heap<T>::imprimi(std::ostream &os) {
    
    for(int i = inicio; i <= fim; i++) {
        os << arr[i].chave << std::endl;
        leMemLog((long int) &arr[i].chave, sizeof(int), id);
    }
}

template <typename T>
bool Heap<T>::vazio() {
    return tamanho == 0;
}

#endif