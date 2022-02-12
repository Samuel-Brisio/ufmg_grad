#ifndef UNICLISTHPP
#define UNICLISTHPP

#include "new_list.hpp"

template <typename T, typename U>
class Unic_List : public Lista<T, U> {
    public:
        Unic_List();
        ~Unic_List();

        bool insert(U &elem);

    private:

};

template <typename T, typename U>
Unic_List<T, U>::Unic_List(): Lista<T, U>() {}


template <typename T, typename U>
Unic_List<T, U>::~Unic_List() {

}

template <typename T, typename U>
bool Unic_List<T, U>::insert(U &elem) {
    T *aux = this->inicio->prox;

    while(aux != nullptr) {
        if(aux->item == elem) return false;
        aux = aux->prox;
    }

    this->inseri_no_fim(elem);

    return true;
}



#endif