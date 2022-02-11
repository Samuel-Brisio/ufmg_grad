#include "celula.hpp"


Stopword::Stopword() : chave() {}

void Stopword::imprime(std::ostream &os) {
    std::cout << chave << std::endl;
}

Stopword_pointer::Stopword_pointer() : item(), prox(nullptr) {}