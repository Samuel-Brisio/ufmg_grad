#include "hash.hpp"

// Structs

hash::Cell_Int::Cell_Int(): key(), value(0) {}

//**********************************************************************************************************************************************************

// Hash_String

hash::Hash_String::Hash_String(hash::ul_int &size, int &number_of_letters): table_size(size), n_letters(number_of_letters) {
    this->occupied = new bool[size]{0};
    this->has_value = new bool[size]{0};
}

hash::Hash_String::~Hash_String() {
    delete[] occupied;
    delete[] has_value;
}

hash::ul_int hash::Hash_String::hash_it(std::string &key) {
    hash::ull_int hash = 0;

    int i = 0;
    for(auto c: key) {
        hash += (hash::ull_int)( (int(c - 'a' + 1)) * pow(n_letters, i) );
        if(i > 6) break;
        i++;
    }

    return hash % table_size;
}

hash::ul_int hash::Hash_String::get_hash(std::string &key) {

    erroAssert(false, "This method get_hash need to be specified by inheritance");
    return 0;
}

void hash::Hash_String::remove(ul_int &hash) {
    erroAssert(false, "This method get_hash need to be specified by inheritance");
}


//*******************************************************************************************************************************************************

// Hash_String_Pair

hash::Hash_String_Pair::Hash_String_Pair(hash::ul_int &size, int &number_of_letters)
    : Hash_String(size, number_of_letters) 
    {
        hashtable = new Cell_Pair[size];
    }

hash::Hash_String_Pair::~Hash_String_Pair() {
    delete[] hashtable;
}

hash::ul_int hash::Hash_String_Pair::get_hash(std::string &key) {
    
    hash::ul_int hash = hash_it(key);

     while(occupied[hash]) {
        
        // The is already inside the hash table
        if(hashtable[hash].key.compare(key) == 0) return hash;
        hash += 1;
    }

    avisoAssert(false, "Chave ainda não foi incluida no hash table");
    return 0;
}

Cell<Pair>* hash::Hash_String_Pair::get_first_element(hash::ul_int &hash) {
    return hashtable[hash].value.get_primeiro_elemento();
}

int hash::Hash_String_Pair::get_hash_size(hash::ul_int hash) {
    return hashtable[hash].value.get_tamanho();
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

void hash::Hash_String_Pair::insert(hash::ul_int &hash, Pair &item) {

   hashtable[hash].value.inseri_no_fim(item);
   occupied[hash] = true;
   has_value[hash] = true;
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
    has_value[hash] = true;
}

void hash::Hash_String_Pair::increment(hash::ul_int &hash, int &id) {
    Cell<Pair>* ptr = hashtable[hash].value.get_primeiro_elemento();

    //search for the element with the id
    while(ptr != nullptr) {
        if(ptr->item.id == id) break;
        ptr = ptr->prox;
    }

    //if element not find, insert it
    if(ptr == nullptr) {
        Pair aux(id, 0);
        insert(hash, aux);
    }

    ptr = hashtable[hash].value.get_ultimo_elemento();

    ptr->item.frequency++;
}

void hash::Hash_String_Pair::print_all(std::ostream &os = std::cout) {
    for(int i = 0; i < this->table_size; i++) {
        if(has_value[i]) {
            os << hashtable[i].key << " ---> ";
            hashtable[i].value.imprime_tudo(os);
            os << std::endl;
        }
    }
}


// ********************************************************************************************************************************************************

//Hash_String_Int

hash::Hash_String_Int::Hash_String_Int(hash::ul_int &size, int &number_of_letters)
    : Hash_String(size, number_of_letters) 
    {
        hashtable = new Cell_Int[size];
    }

hash::Hash_String_Int::~Hash_String_Int() {
    delete[] hashtable;
}

hash::ul_int hash::Hash_String_Int::get_hash(std::string &key) {
    
    hash::ul_int hash = hash_it(key);

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

void hash::Hash_String_Int::insert(hash::ul_int &hash, int &number) {

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
