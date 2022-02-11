#ifndef CELULAHPP
#define CELULAHPP

#include <string>

// structs utlizadas para o armazenamento das stopwords

struct Stopword {
    std::string chave;

    Stopword();
};


struct Stopword_pointer {
    Stopword stopword;
    Stopword_pointer *prox;

    Stopword_pointer();
};



#endif