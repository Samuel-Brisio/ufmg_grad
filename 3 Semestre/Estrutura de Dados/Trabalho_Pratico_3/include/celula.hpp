#ifndef CELULAHPP
#define CELULAHPP

#include <iostream>
#include <string>

// structs utlizadas para o armazenamento das stopwords

struct Stopword {
    std::string chave;

    Stopword();
    void imprime(std::ostream &os = std::cout);
};


struct Stopword_pointer {
    Stopword item;
    Stopword_pointer *prox;

    Stopword_pointer();
};



#endif