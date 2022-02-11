#ifndef INSERCAOHPP
#define INSERCAOHPP

#include "memlog.h"

template <typename Elem>
void Insercao(Elem arr[], int inicio, int fim, int id) {
    int j;
    Elem aux;
    for (int i = inicio + 1; i <= fim; i++) {
        aux = arr[i];
        escreveMemLog((long int) &arr[i], sizeof(Elem), id);
        j = i - 1;

        while (( j >= 0 ) && (aux > arr[j])) {
            arr[j + 1] = arr[j];
            leMemLog((long int) &aux, sizeof(Elem), id);
            leMemLog((long int) &arr[j], sizeof(Elem), id);
            escreveMemLog((long int) &arr[j + 1], sizeof(Elem), id);
            j--;    
        }   
        arr[j + 1] = aux;
        escreveMemLog((long int) &arr[j + 1], sizeof(Elem), id);
    }
}

#endif