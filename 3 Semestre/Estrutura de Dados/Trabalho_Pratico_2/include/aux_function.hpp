#ifndef AUXFUNCTIONHPP
#define AUXFUNCTIONHPP

#include <fstream>
#include <iostream>
#include <celula.hpp>
#include <heap.hpp>

template <typename T>
void le_entrada(T arr[],int n, std::istream &is = std::cin) {
    for(int i = 0; i < n; i++) {
        is >> arr[i].url >> arr[i].chave;
    }
}

void le_entrada(int arr[], int n, std::istream &is = std::cin) {
    for(int i = 0; i < n; i++) {
        is >> arr[i];
    }
}

void le_entrada_heap(Heap<Celula> &heap, int n, std::istream &is = std::cin) {
    for(int i = 0; i < n; i++) {
        Celula aux;
        is >> aux.url >> aux.chave;
        heap.insere(aux);
    }
}

template <typename T>
void imprimi_arr(T arr[], int n, std::ostream &os = std::cout) {
    for(int i = 0; i < n; i++ ) {
        os << arr[i].url << " " << arr[i].chave << std::endl;
    }
}

void imprimi_arr(int arr[], int n, std::ostream &os = std::cout) {
    for(int i = 0; i < n; i++) {
        os << arr[i] << std::endl;
    }
}

#endif