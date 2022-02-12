#ifndef HASHHPP
#define HASHHPP

#include <iostream>
#include "new_list.hpp"
#include "celula.hpp"
#include "cmath"

struct Cell_ptr
{
    std::string key;
    Lista<Pair> value; 
};


class Hash_String {
    public:
        Hash_String(long int &size, int &number_of_letters);
        ~Hash_String();

        long int hash_it(std::string &str);
        void insert(long int &hash, Pair &item);
        void insert(std::string &key, Pair &item);
        void remove(long int &hash);
    
    private:
        Cell_ptr *hashtable;
        bool *occupied;
        long int table_size;
        int n_letters;
};







#endif