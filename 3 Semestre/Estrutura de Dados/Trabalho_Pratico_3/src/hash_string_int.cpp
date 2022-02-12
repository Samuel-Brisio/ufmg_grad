#include "hash_string_int.hpp"

Hash_String_Int::Hash_String_Int(long int &size, int &number_of_letters): table_size(size), n_letters(number_of_letters) {
    hashtable = new Cell_ptr[size];
    this->occupied = new bool[size]{0};
}

Hash_String_Int::~Hash_String_Int() {
    delete[] hashtable;
    delete[] occupied;
}

long int Hash_String_Int::hash_it(std::string &str) {
    int hash = 0;

    int i = 0;
    for(auto c: str) {
        hash += int( (int(c - 'a' + 1)) * pow(n_letters, i) );
        i++;
    }

    return hash % table_size;
}

long int Hash_String_Int::get_hash(std::string &str) {
    long int hash = hash_it(str);

     while(occupied[hash]) {
        
        // The is already inside the hash table
        if(hashtable[hash].key.compare(key) == 0) {
            hashtable[hash].value.inseri_no_fim(item);
            return hash;
        }   
        hash += 1;
    }

    avisoAssert(false, "Chave ainda não foi incluida no hash table");
    return -1;
}

void Hash_String_Int::insert(long int &hash, std::string &key, Pair &item) {

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