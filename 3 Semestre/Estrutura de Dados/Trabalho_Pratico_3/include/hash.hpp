#ifndef HASHHPP
#define HASHHPP

#include <iostream>
#include "new_list.hpp"
#include "celula.hpp"
#include "cmath"

namespace hash {

    class Hash_String {
        public:
            Hash_String(long int &size, int &number_of_letters);
            ~Hash_String();

            long int hash_it(std::string &key);
            virtual long int get_hash(std::string &key); // remover implementação utiliza hashtable
            void remove(long int &hash);
        
        protected:
            bool *occupied;
            bool *has_value;
            long int table_size;
            int n_letters;
    };

    struct Cell_Pair
    {
        std::string key;
        Lista<Pair> value; 
    };

    class Hash_String_Pair: Hash_String {
        public:
            Hash_String_Pair(long int &size, int &number_of_letters);
            ~Hash_String_Pair();

            long int get_hash(std::string &key);

            void initialize(Lista<Word> &list);
            void insert(long int &hash, Pair &item);
            void insert(std::string &key, Pair &item);
            void increment(long int &hash, int &id);
            void print_all(std::ostream &os);

        private:
            Cell_Pair *hashtable;

    };

    struct Cell_Int
        {
            std::string key;
            int value; 

            Cell_Int();
        };


    class Hash_String_Int: Hash_String {
        public:
            Hash_String_Int(long int &size, int &number_of_letters);
            ~Hash_String_Int();

            long int get_hash(std::string &key);

            void initialize(Lista<Word> &list);
            void increment(std::string &key);
            void insert(long int &hash, int &item);
            void insert(std::string &key, int &item);

        private:
            Cell_Int *hashtable;
    };
}


#endif