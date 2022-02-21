#ifndef UNICLISTHPP
#define UNICLISTHPP

#include "new_list.hpp"

template <typename T>
class Unic_List : public Lista<T> {
    public:
        Unic_List();
        ~Unic_List();

        bool insert(T &elem);

    private:

};

template <typename T>
Unic_List<T>::Unic_List(): Lista<T>() {
    std::cout << "chora" << std::endl;
}


template <typename T>
Unic_List<T>::~Unic_List() {

}

template <typename T>
bool Unic_List<T>::insert(T &elem) {
    Cell<T> *aux = this->inicio->prox;

    while(aux != nullptr) {
        if(aux->item == elem) return false;
        aux = aux->prox;
    }

    this->inseri_no_fim(elem);

    return true;
}



#endif