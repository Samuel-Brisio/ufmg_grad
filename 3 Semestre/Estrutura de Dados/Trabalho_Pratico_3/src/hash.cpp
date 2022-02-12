#include "hash.hpp"

Hash_String::Hash_String(long int &size, int &number_of_letters): table_size(size), n_letters(number_of_letters) {
    hashtable = new Cell_ptr[size];
    this->occupied = new bool[size]{0};
}

Hash_String::~Hash_String() {
    delete[] hashtable;
    delete[] occupied;
}

long int Hash_String::hash_it(std::string &str) {
    int hash = 0;

    int i = 0;
    for(auto c: str) {
        hash += int( (int(c - 'a' + 1)) * pow(n_letters, i) );
        i++;
    }

    return hash % table_size;
}

void Hash_String::insert(long int &hash, Pair &item) {

   hashtable[hash].value.inseri_no_fim(item);
}

void Hash_String::insert(std::string &key, Pair &item) {

    int hash = hash_it(key);

    while(occupied[hash]) {
        
        // The is already inside the hash table
        if(hashtable[hash].key.compare(key) == 0) {
            hashtable[hash].value.inseri_no_fim(item);
            return;
        }   
        hash += 1;
    }

    // This key is not inside the hash table
    hashtable[hash].key = key;
    hashtable[hash].value.inseri_no_fim(item);
    occupied[hash] = true;
}