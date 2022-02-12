#ifndef CELULAHPP
#define CELULAHPP

#include <iostream>
#include <string>

// structs utlizadas para o armazenamento das stopwords

struct Word {
    std::string chave;

    Word();
    void imprime(std::ostream &os = std::cout);

    bool operator == (Word const &right) const;
};


struct Word_pointer {
    Word item;
    Word_pointer *prox;

    Word_pointer();
};



#endif