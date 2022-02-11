#ifndef STRUCTSHPP
#define STRUCTSHPP

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

struct Url_views
{
    std::string url;
    int chave;

    void operator = (const Url_views &right) {
        url = right.url;
        chave = right.chave;
    }

    bool operator > (const Url_views &right) const {
        if (chave > right.chave) return true;
        if (chave == right.chave && url.compare(right.url) < 0) return true;
        return false; 
    }
    
};

struct Url_views_tape {
    std::string url;
    int chave;
    int fita;

    void operator = (const Url_views_tape &right) {
        url = right.url;
        chave = right.chave;
        fita = right.fita;
    }

    bool operator > (const Url_views_tape &right) {
        if(chave > right.chave) return true;
        if(chave == right.chave) 
            if (url.compare(right.url) < 0) return true;
        return false; 
    }
};

#endif