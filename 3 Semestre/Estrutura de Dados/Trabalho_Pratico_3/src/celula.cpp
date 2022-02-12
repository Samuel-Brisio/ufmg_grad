#include "celula.hpp"


Word::Word() : chave() {}

void Word::imprime(std::ostream &os) {
    os << chave << std::endl;
}

bool Word::operator == (Word const &right) const{
    return (chave.compare(right.chave) == 0);
}