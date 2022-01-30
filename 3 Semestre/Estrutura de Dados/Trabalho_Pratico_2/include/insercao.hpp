#ifndef INSERCAOHPP
#define INSERCAOHPP

template <typename Elem>
void Insercao(Elem arr[], int inicio, int fim) {
    int j;
    Elem aux;
    for (int i = inicio + 1; i <= fim; i++) {
        aux = arr[i];
        j = i - 1;

        while (( j >= 0 ) && (aux > arr[j])) {
            arr[j + 1] = arr[j];
            j--;    
        }   
        arr[j + 1] = aux;
    }
}

#endif