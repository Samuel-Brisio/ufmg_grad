#ifndef LISTAH
#define LISTAH

#include <iostream>
#include "msgassert.h"
#include "celula.hpp"

template <typename T>
struct Cell {
    T item;
    Cell *prox;

    Cell(): item(), prox(nullptr) {}
};

// U é um Item que está contido dentro da célula
template <typename U>
class Lista {
    public:
        Lista();
        ~Lista();

        int get_tamanho();

        Cell<U>* get_primeiro_elemento();
        Cell<U>* get_ultimo_elemento();

        void inseri_no_inicio(U &elem);
        void inseri_no_fim(U &elem);

        U remove_no_inicio();

        void remove_tudo();
        void imprime_tudo(std::ostream &os = std::cout);

    protected:
        int tamanho;
        Cell<U>* inicio;
        Cell<U>* fim;

};

template <typename U>
Lista<U>::Lista()
// Descrição: Inicializa os atributos
// Entrada: Nenhuma
// Saida: Nenhuma
{
    tamanho = 0;
    inicio = new (Cell<U>);
    fim = inicio;
}


template <typename U>
Lista<U>::~Lista()
// Descricao: Desaloca a memória
// Entrada: Nenhuma
// Saida: Nenhuma
{
    remove_tudo();
    delete inicio;
}

template <typename U>
int Lista<U>::get_tamanho()
// Descricao: Retorna o tamanho da lista
// Entrada: Nenhuma
// Saida: tamanho
{
    return tamanho;
}

template <typename U>
Cell<U>* Lista<U>::get_primeiro_elemento() {
    return inicio->prox;
}

template <typename U>
Cell<U>* Lista<U>::get_ultimo_elemento()
// Descricao: Retorna o porteiro do ultimo elemento da lista
// Entrada: Nenhuma
// Saida: fim
{
    return fim;
}

template <typename U>
void Lista<U>::inseri_no_inicio(U &elem)
// Descricao: Insere no inicio da lista
// Entrada: chave;
// Saida: Nenhuma
{
    //cria uma nova celula
    Cell<U> *nova_celula = new(Cell<U>);
    nova_celula->item = elem;

    //Insere o elemento no inicio da lista
    nova_celula->prox = inicio->prox;
    inicio->prox = nova_celula;
 
    tamanho++;

    // Quando for a primeira celula a ser inserida
    if(tamanho == 1) fim = nova_celula;
}

template <typename U>
void Lista<U>::inseri_no_fim(U &elem)
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
    Cell<U> *nova_celula = new(Cell<U>);
    nova_celula->item = elem;

    //Insere o elemento no final da lista
    fim->prox = nova_celula;
    fim = nova_celula;

    tamanho++;
}

template <typename U>
U Lista<U>::remove_no_inicio()
// Descricao: Remove o primeiro elemento da lista
// Entrada: Nenhuma
// Saida: item
{
    Cell<U> *aux_ptr;
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

template <typename U>
void Lista<U>::remove_tudo()
// Descricao: Remove todos os elemetos da lista
// Entrada: Nenhuma
// Saida: Nenhuma
{
    while(tamanho != 0) remove_no_inicio();
}

template <typename U>
void Lista<U>::imprime_tudo(std::ostream &os)
// Descricao: Imprime todos os elementos da lista
// Entrada: Nenhuma
// Saida: Nenhuma
{
    Cell<U> *aux = inicio->prox;

    while(aux != nullptr) {
        aux->item.imprime(os);
        aux = aux->prox;
    }
}

#endif