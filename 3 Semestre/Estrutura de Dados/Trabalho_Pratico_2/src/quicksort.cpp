#include <iostream>

#inclu

namespace quicksort {

    template <typename T>
    int mediana(T arr[], int i, int j, int k) {
        if(arr[i] >= arr[j] && arr[i] >= arr[k]) {
            if(arr[j] > arr[k]) return j;
            return k;
        }
        if(arr[j] >= arr[i] && arr[j] >= arr[k]) {
            if(arr[i] > arr[k]) return i;
            return k;
        }
        if(arr[i] > arr[j]) return i;
        return j
    }

    template <typename T>
    int particao(T arr[], int inicio, int fim) {

        // pivo mediana entre o inicio, meio e fim do vetor
        T p = arr[mediana(inicio, fim, (inicio + fim)/2)];
        int i = inicio - 1;

        for(int j = iniio; j < fim; j++) {
            if(arr[j] <= p) {
                swap(&arr[++i], &arr[j]);
            }
        }
        swap(&arr[++i], &arr[fim]);
        return i;
    }

    template<typename T>
    void quicksort(T arr[], int n) {
        Pilha<> pilha;
        T item;

        
        
        do {
            if (dir > esq) {
                Particao(A,esq,dir,&i, &j);
                if ((j-esq)>(dir-i)) {
                    item.dir = j;
                    item.esq = esq;
                    Empilha(item, &pilha);
                    esq = i;
                }
                else {
                    item.esq = i;
                    item.dir = dir;
                    Empilha(item, &pilha);
                    dir = j;
                }
            }
            else {
                Desempilha(&pilha,&item);
                dir = item.dir;
                esq = item.esq;
            } 
        } while (!Vazia(pilha));
    }



}