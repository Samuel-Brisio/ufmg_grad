#ifndef LISTAH
#define LISTAH

#include <iostream>
#include "msgassert.h"
#include "celula.hpp"

// T é a celula que será usada como pointer
// U é um Item que está contido dentro da célula
template <typename T, typename U>
class Lista {
    public:
        Lista();
        ~Lista();

        int get_tamanho();

        T* get_primeiro_elemento();
        T* get_ultimo_elemento();

        void inseri_no_inicio(U &chave);
        void inseri_no_fim(U &chave);

        U remove_no_inicio();

        void remove_tudo();
        void imprime_tudo(std::ostream &os);

    protected:
        int tamanho;
        T* inicio;
        T* fim;

};

template <typename T, typename U>
Lista<T, U>::Lista()
// Descrição: Inicializa os atributos
// Entrada: Nenhuma
// Saida: Nenhuma
{
    tamanho = 0;
    inicio = new (T);
    fim = inicio;
}


template <typename T, typename U>
Lista<T, U>::~Lista()
// Descricao: Desaloca a memória
// Entrada: Nenhuma
// Saida: Nenhuma
{
    remove_tudo();
    delete inicio;
}

template <typename T, typename U>
int Lista<T, U>::get_tamanho()
// Descricao: Retorna o tamanho da lista
// Entrada: Nenhuma
// Saida: tamanho
{
    return tamanho;
}

template <typename T, typename U>
T* Lista<T, U>::get_ultimo_elemento()
// Descricao: Retorna o porteiro do ultimo elemento da lista
// Entrada: Nenhuma
// Saida: fim
{
    return fim;
}

template <typename T, typename U>
void Lista<T, U>::inseri_no_inicio(U &elem)
// Descricao: Insere no inicio da lista
// Entrada: chave;
// Saida: Nenhuma
{
    //cria uma nova celula
    T *nova_celula = new(T);
    nova_celula->item = elem;

    //Insere o elemento no inicio da lista
    nova_celula->prox = inicio->prox;
    inicio->prox = nova_celula;
 
    tamanho++;

    // Quando for a primeira celula a ser inserida
    if(tamanho == 1) fim = nova_celula;
}

template <typename T, typename U>
void Lista<T, U>::inseri_no_fim(U &elem)
// Descricao: Insere o elemento no final da lista
// Entrada: chave
// Saida: Nenhuma
{
    //Caso a lista esteja vazia
    if(tamanho == 0) {
        inseri_no_inicio(elem);
        return;
    }

    //cria uma nova celula
    T *nova_celula = new(T);
    nova_celula->item = elem;

    //Insere o elemento no final da lista
    fim->prox = nova_celula;
    fim = nova_celula;

    tamanho++;
}

template <typename T, typename U>
U Lista<T, U>::remove_no_inicio()
// Descricao: Remove o primeiro elemento da lista
// Entrada: Nenhuma
// Saida: item
{
    T *aux_ptr;
    U item;

    if(tamanho == 0) throw "Lista Vazia";

    // retira o elemento o primeiro elemento da lista
    aux_ptr = inicio->prox;
    inicio->prox = aux_ptr->prox;
    tamanho--;

    // Caso o ultimo elemento restante da lista seja removido
    if(inicio->prox == nullptr) fim = inicio;

    item = aux_ptr->item;
    delete(aux_ptr);

    return item;

}

template <typename T, typename U>
void Lista<T, U>::remove_tudo()
// Descricao: Remove todos os elemetos da lista
// Entrada: Nenhuma
// Saida: Nenhuma
{
    while(tamanho != 0) remove_no_inicio();
}

template <typename T, typename U>
void Lista<T, U>::imprime_tudo(std::ostream &os)
// Descricao: Imprime todos os elementos da lista
// Entrada: Nenhuma
// Saida: Nenhuma
{
    T *aux = inicio->prox;

    while(aux != nullptr) {
        aux->item.imprime(os);
        aux = aux->prox;
    }
}

#endif