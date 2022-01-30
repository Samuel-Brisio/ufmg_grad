#ifndef QUICKSORTHPP
#define QUICKSORTHPP

#include <iostream>

#include "insercao.hpp"
#include "pilha.hpp"
#include "celula.hpp"

namespace qs {

    struct pair {
        int esq;
        int dir;
    };

    template <typename T>
    void swap(T &a, T &b);

    template <typename T>
    void ordena_mediana(T &a, T &b, T &c);

    template <typename T>
    int particao(T arr[], int inicio, int fim);

    template<typename T>
    void quicksort(T arr[],int inicio, int fim);
}


template <typename T>
void qs::swap(T &a, T &b) {
    std::swap(a, b);
    escreveMemLog((long int) &a, sizeof(T), 0);
    escreveMemLog((long int) &b, sizeof(T), 0);
}

//ordena 
template <typename T>
void qs::ordena_mediana(T &a, T &b, T &c) {

    if(c > b) swap(c, b);
    leMemLog((long int) &c, sizeof(T), 0);
    leMemLog((long int) &b, sizeof(T), 0);
    
    if(b > a) swap(b, a);
    leMemLog((long int) &b, sizeof(T), 0);
    leMemLog((long int) &a, sizeof(T), 0);
    
    if(c > b) std::swap(c, b);
    leMemLog((long int) &c, sizeof(T), 0);
    leMemLog((long int) &b, sizeof(T), 0);
}




template <typename T>
int qs::particao(T arr[], int inicio, int fim) {

    // pivo mediana entre o inicio, meio e fim do vetor
    int indice_medio = (inicio + fim)/2;

    ordena_mediana(arr[inicio], arr[indice_medio], arr[fim]);

    T pivo;

    bool tem_dois_ou_mais_elementos = fim - inicio + 1 >= 2;

    if(tem_dois_ou_mais_elementos) { 
        swap(arr[indice_medio], arr[fim - 1]);
        pivo = arr[fim - 1];
        leMemLog((long int) &arr[fim - 1], sizeof(T), 0);
        fim--;
        inicio++;
    }
    else pivo = arr[fim];
    

    int i = inicio - 1;

    for(int j = inicio; j < fim; j++) {
        if(!(pivo > arr[j])) {
            swap(arr[++i], arr[j]);
        }
        leMemLog((long int) &pivo, sizeof(T), 0);
        leMemLog((long int) &arr[j], sizeof(T), 0);
    }

    if(tem_dois_ou_mais_elementos) swap(arr[++i], arr[fim]);

    return i;
}

template<typename T>
void qs::quicksort(T arr[],int inicio, int fim) {
    qs::pair item;
    Pilha<celula<qs::pair>, qs::pair> pilha;
    
    item.esq = inicio;
    item.dir = fim;
    pilha.empilha(item);

    int p;

    if(inicio >= fim) return;

    do {

        if(fim - inicio + 1 < 4) {
            Insercao(arr, inicio, fim);
            inicio = fim;
        }
        else {
            p = particao(arr, inicio, fim);
        }
        
        if(fim > inicio) {

            if ((p - inicio) > (fim - (p + 1) )) {
               
                item.esq = inicio;
                item.dir = p - 1;
                pilha.empilha(item);
                inicio = p + 1;
            }
            else {
                item.esq = p + 1;
                item.dir = fim;
                pilha.empilha(item);
                fim = p - 1;
            }
        }else {
            if(pilha.vazia()) return;
            item = pilha.desempilha();
            inicio = item.esq;
            fim = item.dir;
        }

    } while (!pilha.vazia());
}

#endif