#ifndef PILHAHPP
#define PILHAHPP

#include <iostream>


template <typename T, typename Elem>
class Pilha {
    public:
        Pilha();
        ~Pilha();

        void empilha(Elem elem);
        Elem desempilha();

        bool vazia();

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
Pilha<T, Elem>::~Pilha() {
    while(!vazia()) {
        desempilha();
    }
}

template <typename T, typename Elem>
void Pilha<T, Elem>::empilha(Elem elem) {
    T* tmp = new T(elem);
    
    tmp->next = inicio;
    inicio = tmp;

    tamanho++;
}

template <typename T, typename Elem>
Elem Pilha<T, Elem>::desempilha() {
    
    avisoAssert(tamanho > 0, "Lista está vazia");

    T* tmp = inicio;

    inicio = tmp->next;
    tamanho--;

    return tmp->elem;
}

template <typename T, typename Elem>
bool Pilha<T, Elem>::vazia() {
    return tamanho == 0;
}

#endif