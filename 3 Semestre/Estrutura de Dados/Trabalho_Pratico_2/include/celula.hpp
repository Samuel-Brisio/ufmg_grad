#ifndef CELULAHPP
#define CELULAHPP

#include <iostream>

struct Celula
{
    std::string url;
    int chave;

    void operator = (const Celula &right) {
        url = right.url;
        chave = right.chave;
    }

    bool operator > (const Celula &right) const {
        return chave > right.chave || (!(chave > right.chave) && url.compare(right.url) < 0); 
    }
};

struct urlViews_fita {
    std::string url;
    int chave;
    int fita;

    void operator = (const Celula &right) {
        url = right.url;
        chave = right.chave;
    }

    bool operator > (const urlViews_fita &right) {
        if(chave > right.chave) return true;
        if(chave == right.chave) 
            if (url.compare(right.url) < 0) return true;
        return false; 
    }
};

#endif