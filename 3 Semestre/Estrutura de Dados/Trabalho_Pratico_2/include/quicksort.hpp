#ifndef QUICKSORTHPP
#define QUICKSORTHPP

#include <iostream>

#include "insercao.hpp"
#include "pilha.hpp"

namespace qs {

    struct pair {
        int esq;
        int dir;
    };

    template <typename T>
    void swap(T &a, T &b, int id);

    template <typename T>
    void ordena_mediana(T &a, T &b, T &c, int id);

    template <typename T>
    int particao(T arr[], int inicio, int fim, int id);

    template<typename T>
    void quicksort(T arr[],int inicio, int fim, int id);
}


template <typename T>
void qs::swap(T &a, T &b, int id) {
    std::swap(a, b);
    escreveMemLog((long int) &a, sizeof(T), id);
    escreveMemLog((long int) &b, sizeof(T), id);
}

//ordena 
template <typename T>
void qs::ordena_mediana(T &a, T &b, T &c, int id) {

    if(c > b) swap(c, b, id);
    leMemLog((long int) &c, sizeof(T), id);
    leMemLog((long int) &b, sizeof(T), id);
    
    if(b > a) swap(b, a, id);
    leMemLog((long int) &b, sizeof(T), id);
    leMemLog((long int) &a, sizeof(T), id);
    
    if(c > b) swap(c, b, id);
    leMemLog((long int) &c, sizeof(T), id);
    leMemLog((long int) &b, sizeof(T), id);
}




template <typename T>
int qs::particao(T arr[], int inicio, int fim, int id) {

    // pivo mediana entre o inicio, meio e fim do vetor
    int indice_medio = (inicio + fim)/2;

    ordena_mediana(arr[inicio], arr[indice_medio], arr[fim], id);

    T pivo;

    bool tem_dois_ou_mais_elementos = fim - inicio + 1 >= 2;

    if(tem_dois_ou_mais_elementos) { 
        swap(arr[indice_medio], arr[fim - 1], id);
        pivo = arr[fim - 1];
        leMemLog((long int) &arr[fim - 1], sizeof(T), id);
        fim--;
        inicio++;
    }
    else pivo = arr[fim];
    

    int i = inicio - 1;

    for(int j = inicio; j < fim; j++) {
        if(!(pivo > arr[j])) {
            swap(arr[++i], arr[j], id);
        }
        leMemLog((long int) &pivo, sizeof(T), id);
        leMemLog((long int) &arr[j], sizeof(T), id);
    }

    if(tem_dois_ou_mais_elementos) swap(arr[++i], arr[fim], id);

    return i;
}

template<typename T>
void qs::quicksort(T arr[],int inicio, int fim, int id) {
    qs::pair item;
    Pilha<celula<qs::pair>, qs::pair> pilha;
    
    item.esq = inicio;
    item.dir = fim;
    pilha.empilha(item);

    int p;

    if(inicio >= fim) return;

    do {

        if(fim - inicio + 1 < 4) {
            Insercao(arr, inicio, fim, id);
            inicio = fim;
        }
        else {
            p = particao(arr, inicio, fim, id);
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