#ifndef HASHHPP
#define HASHHPP

#include <iostream>
#include "new_list.hpp"
#include "celula.hpp"
#include "cmath"


namespace hash {

    using ull_int = unsigned long long int;
    using ul_int = unsigned long int; 

    class Hash_String {
        public:
            Hash_String(ul_int &size, int &number_of_letters);
            ~Hash_String();

            ul_int hash_it(std::string &key);
            virtual ul_int get_hash(std::string &key); // remover implementação utiliza hashtable
            void remove(ul_int &hash);
        
        protected:
            bool *occupied;
            bool *has_value;
            ul_int table_size;
            int n_letters;
    };

    struct Cell_Pair
    {
        std::string key;
        Lista<Pair> value; 
    };

    class Hash_String_Pair: Hash_String {
        public:
            Hash_String_Pair(ul_int &size, int &number_of_letters);
            ~Hash_String_Pair();

            ul_int get_hash(std::string &key);
            Cell<Pair>* get_first_element(ul_int &hash);
            int get_hash_size(ul_int hash);

            void initialize(Lista<Word> &list);
            void insert(ul_int &hash, Pair &item);
            void insert(std::string &key, Pair &item);
            void increment(ul_int &hash, int &id);
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
            Hash_String_Int(ul_int &size, int &number_of_letters);
            ~Hash_String_Int();

            ul_int get_hash(std::string &key);

            void initialize(Lista<Word> &list);
            void increment(std::string &key);
            void insert(ul_int &hash, int &item);
            void insert(std::string &key, int &item);

        private:
            Cell_Int *hashtable;
    };
}


#endif