#ifndef INSERCAOHPP
#define INSERCAOHPP

#include "memlog.h"

template <typename Elem>
void Insercao(Elem arr[], int indexes[], int inicio, int fim, int id) {
    int j;
    Elem aux;
    int i_aux;
    for (int i = inicio + 1; i <= fim; i++) {
        aux = arr[i];
        i_aux = indexes[i];
        escreveMemLog((long int) &arr[i], sizeof(Elem), id);
        j = i - 1;

        while (( j >= 0 ) && (aux > arr[j])) {
            arr[j + 1] = arr[j];
            indexes[j + 1] =  indexes[j];
            leMemLog((long int) &aux, sizeof(Elem), id);
            leMemLog((long int) &arr[j], sizeof(Elem), id);
            escreveMemLog((long int) &arr[j + 1], sizeof(Elem), id);
            j--;    
        }
        //swap    
        arr[j + 1] = aux;
        indexes[j + 1] = i_aux;
        escreveMemLog((long int) &arr[j + 1], sizeof(Elem), id);
    }
}

#endif