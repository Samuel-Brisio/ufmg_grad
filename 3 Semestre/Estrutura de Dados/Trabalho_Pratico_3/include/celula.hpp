#ifndef CELULAHPP
#define CELULAHPP

#include <iostream>
#include <string>
#include "celula.hpp"

// structs utlizadas para o armazenamento das stopwords e do vocabulario

struct Word {
    std::string chave;

    Word();
    void imprime(std::ostream &os = std::cout);

    bool operator == (Word const &right) const;
};

// structs used in hash

struct Item {
    std::string key;
    //Lista<Item> value;
};


#endif