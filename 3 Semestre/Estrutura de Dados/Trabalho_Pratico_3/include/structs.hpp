#ifndef CELULAHPP
#define CELULAHPP

#include <iostream>
#include <string>
#include "structs.hpp"

// structs utlizadas para o armazenamento das stopwords e do vocabulario

struct Word {
    std::string chave;

    Word();
    void imprime(std::ostream &os = std::cout);

    bool operator == (Word const &right) const;
};

// structs used in hash

struct Pair {
    int id;
    int frequency;

    Pair();
    Pair(int id, int number);

    void imprime(std::ostream &os = std::cout);
};


#endif