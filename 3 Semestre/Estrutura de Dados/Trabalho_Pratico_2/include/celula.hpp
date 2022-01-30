#ifndef CELULAHPP
#define CELULAHPP

#include <iostream>

// estrutura de dados utilizado na pilha
template <typename T>
struct celula 
{
    T elem;
    celula* next;
    
    celula() {
        next = nullptr;
    }
    
    celula(T elem) {
        this->elem = elem;
        next = nullptr;
        
    }
};

struct Celula
{
    std::string url;
    int chave;

    void operator = (const Celula &right) {
        url = right.url;
        chave = right.chave;
    }

    bool operator > (const Celula &right) const {
        if (chave > right.chave) return true;
        if (chave == right.chave && url.compare(right.url) < 0) return true;
        return false; 
    }
    
};

struct urlViews_fita {
    std::string url;
    int chave;
    int fita;

    void operator = (const urlViews_fita &right) {
        url = right.url;
        chave = right.chave;
        fita = right.fita;
    }

    bool operator > (const urlViews_fita &right) {
        if(chave > right.chave) return true;
        if(chave == right.chave) 
            if (url.compare(right.url) < 0) return true;
        return false; 
    }
};

#endif