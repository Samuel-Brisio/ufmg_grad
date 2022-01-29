#ifndef PILHAHPP
#define PILHAHPP

#include <iostream>

template <typename T, typename Elem>
class Pilha {
    public:
        Pilha();

        void empilha(Elem &elem);
        Elem desempilha();

    private:
        T* inicio;
        int tamanho;

};


template <typename T, typename Elem>
Pilha<T, Elem>::Pilha() {
    inicio = nullptr;
    tamanho = 0;
}

template <typename T, typename Elem>
void Pilha<T, Elem>::empilha(Elem &elem) {
    T* tmp = new T(elem);
    
    tmp->next = inicio;
    inicio = tmp;

    tamanho++;
}

template <typename T, typename Elem>
Elem Pilha<T, Elem>::desempilha() {
    T* tmp = inicio;

    inicio = tmp->next;
    tamanho--;

    return tmp->elem;
}

#endif