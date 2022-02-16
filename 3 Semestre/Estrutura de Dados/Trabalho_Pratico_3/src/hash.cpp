#include "hash.hpp"

// Structs

hash::Cell_Int::Cell_Int(): key(), value(0) {}

//**********************************************************************************************************************************************************

// Hash_String

hash::Hash_String::Hash_String(long int &size, int &number_of_letters): table_size(size), n_letters(number_of_letters) {
    this->occupied = new bool[size]{0};
}

hash::Hash_String::~Hash_String() {
    delete[] occupied;
}

long int hash::Hash_String::hash_it(std::string &key) {
    int hash = 0;

    int i = 0;
    for(auto c: key) {
        hash += int( (int(c - 'a' + 1)) * pow(n_letters, i) );
        i++;
    }

    return hash % table_size;
}

long int hash::Hash_String::get_hash(std::string &key) {

    erroAssert(false, "This method get_hash need to be specified by inheritance");
    return -1;
}



//*******************************************************************************************************************************************************

// Hash_String_Pair

hash::Hash_String_Pair::Hash_String_Pair(long int &size, int &number_of_letters)
    : Hash_String(size, number_of_letters) 
    {
        hashtable = new Cell_Pair[size];
    }

hash::Hash_String_Pair::~Hash_String_Pair() {
    delete[] hashtable;
}

long int hash::Hash_String_Pair::get_hash(std::string &key) {
    
    long int hash = hash_it(key);

     while(occupied[hash]) {
        
        // The is already inside the hash table
        if(hashtable[hash].key.compare(key) == 0) return hash;
        hash += 1;
    }

    avisoAssert(false, "Chave ainda não foi incluida no hash table");
    return -1;
}

void hash::Hash_String_Pair::initialize(Lista<Word> &list) {

    Cell<Word> *aux = list.get_primeiro_elemento();
    int hash;

    while(aux != nullptr) {
        std::string word = aux->item.chave;
        hash = hash_it(word);

        // While dont find a free position on the table
        while(occupied[hash]) hash += 1;

        hashtable[hash].key = word;
        occupied[hash] = true;

        aux = aux->prox;
    }
}

void hash::Hash_String_Pair::insert(long int &hash, Pair &item) {

   hashtable[hash].value.inseri_no_fim(item);
}

void hash::Hash_String_Pair::insert(std::string &key, Pair &item) {

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


// ********************************************************************************************************************************************************

//Hash_String_Int

hash::Hash_String_Int::Hash_String_Int(long int &size, int &number_of_letters)
    : Hash_String(size, number_of_letters) 
    {
        hashtable = new Cell_Int[size];
    }

hash::Hash_String_Int::~Hash_String_Int() {
    delete[] hashtable;
}

long int hash::Hash_String_Int::get_hash(std::string &key) {
    
    long int hash = hash_it(key);

     while(occupied[hash]) {
        
        // The is already inside the hash table
        if(hashtable[hash].key.compare(key) == 0) return hash;
        hash += 1;
    }

    avisoAssert(false, "Chave ainda não foi incluida no hash table");
    return -1;
}

void hash::Hash_String_Int::initialize(Lista<Word> &list) {

    Cell<Word> *aux = list.get_primeiro_elemento();
    int hash;

    while(aux != nullptr) {
        std::string word = aux->item.chave;
        hash = hash_it(word);

        // While dont find a free position on the table
        while(occupied[hash]) hash += 1;

        hashtable[hash].key = word;
        occupied[hash] = true;

        aux = aux->prox;
    }
}

void hash::Hash_String_Int::increment(std::string &key) {
    int hash = get_hash(key);

    hashtable[hash].value++;
}

void hash::Hash_String_Int::insert(long int &hash, int &number) {

   hashtable[hash].value = (number);
}

void hash::Hash_String_Int::insert(std::string &key, int &number) {

    int hash = hash_it(key);

    while(occupied[hash]) {
        
        // The is already inside the hash table
        if(hashtable[hash].key.compare(key) == 0) {
            hashtable[hash].value = number;
            return;
        }   
        hash += 1;
    }

    // This key is not inside the hash table
    hashtable[hash].key = key;
    hashtable[hash].value = number;
    occupied[hash] = true;
}
