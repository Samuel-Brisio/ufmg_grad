#ifndef HASHSTRINGHPP
#define HASHSTRINGHPP

#include <iostream>
#include "new_list.hpp"
#include "celula.hpp"
#include "cmath"
#include "msgassert.h"

namespace hash_string {

    struct Cell
    {
        std::string key;
        int frequency; 
    };


    class Hash_String_Int {
        public:
            Hash_String_Int(long int &size, int &number_of_letters);
            ~Hash_String_Int();

            long int hash_it(std::string &str);
            long int get_hash(std::string &str);

            void insert(long int &hash, std::string &key, int number);
            void remove(long int &hash);
        
        private:
            Cell *hashtable;
            bool *occupied;
            long int table_size;
            int n_letters;
    };
}

#endif