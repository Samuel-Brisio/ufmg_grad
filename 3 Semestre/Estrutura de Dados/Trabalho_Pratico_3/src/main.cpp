#include <iostream>
#include <fstream>
#include <getopt.h>
#include <string>
#include <filesystem>

//External Library
#include "msgassert.h"
#include "memlog.h"

//Self implemented data struct
#include "new_list.hpp"
#include "unic_list.hpp"
#include "hash.hpp"

#define PROCESS_FILE_FOLDER "Processo/"
#define ALPHABET_LETTER 26
#define HASHTABLE_SIZE 1000000009

//function prototype
void parse_args(int &number, char **pametros);
int open_corpus(std::string folder);
void read_stopwords();
void to_lowercase(std::string &word);
bool is_stopword(std::string &word);
void remove_special_characters(std::string &word);
void inverse_index_gen();
void find_vocabulary();
void use_instruction();

//global variables
std::string input_name; // input file name
std::string output_name; // output file name 
std::string folder_path; // path for the folder that contais the corpus
int number_of_files; // number of files in the corpus
std::string stopwords_file_name;
Lista<Word> stopwords; // linked list that store the vocabulary
Unic_List<Word> vocabulary; // linked list that store the vocabulary
//todo   // list of files from the corpus
//todo   // list of files that contain only vocabulary words


int main(int argc, char **argv) {

    // separa os argumentos passados para o programa
    parse_args(argc, argv);

    //le o arquivo de stopwords
    read_stopwords();

    // abre os documentos
    number_of_files = open_corpus(folder_path);

    //gera o indice inverso
    //inverse_index_gen();

}

void parse_args(int &number, char **parameters) {
    extern char * optarg; //extern variable for getopt

    int c;

    while((c = getopt(number, parameters, "i:o:c:s:h")) != EOF) {
        switch (c)
        {
        case 'i':
            input_name.assign(optarg);
            break;
        case 'o':
            output_name.assign(optarg);
            break;
        case 'c':
            folder_path.assign(optarg);
            break;
        case 's':
            stopwords_file_name.assign(optarg);
            break;
        case 'h':
        default:
            use_instruction();
            break;
        }
    }

}

void use_instruction() {
    std::cout << "Instruction how to use" << std::endl;
    exit(1);
}

int open_corpus(std::string path) {
    int i = 0;

    for (const auto &doc : std::filesystem::directory_iterator(path)) {
        std::ifstream input_file;
        input_file.open(doc.path());
        erroAssert(input_file.is_open(), "Erro: nao foi possivel abrir o arquivo");
        
        std::string file_name = PROCESS_FILE_FOLDER;
        file_name.append(std::to_string(i));

        std::ofstream only_vocabulary_file;
        only_vocabulary_file.open(file_name);
        erroAssert(only_vocabulary_file.is_open(), "Erro: nao foi possivel abrir o arquivo");

        std::string word;

        while(input_file >> word) {
            to_lowercase(word);

            if(is_stopword(word)) continue;
            
            remove_special_characters(word);

            // if the variable word is empty
            if(word.size() == 0) continue;

            only_vocabulary_file << word << " ";
            Word elem;
            elem.chave = word;
            vocabulary.insert(elem);
        }
        
        input_file.close();
        only_vocabulary_file.close();
        i++;
    }

    return i;

}

void read_stopwords() {
    std::ifstream stopwords_file;
    stopwords_file.open(stopwords_file_name);

    erroAssert(stopwords_file.is_open(), "Erro: nao foi possivel abrir o arquivo de stopwords");

    Word word;
    while(stopwords_file >> word.chave) stopwords.inseri_no_fim(word);
}

void to_lowercase(std::string &word) {
    for(auto &c: word) {
        c = std::tolower(c);
    }
}

bool is_stopword(std::string &word) {
    Cell<Word> *aux = stopwords.get_primeiro_elemento();

    while(aux != nullptr) {
        if(word.compare(aux->item.chave) == 0) return true;
        aux = aux->prox;
    }
    return false;
}

void remove_special_characters(std::string &word) {
    int i = 0;
    int size = 0;

    int index_that_need_to_be_kept[100];
    
    for(auto c: word) {
        if((c >= 'a' && c <= 'z')) {
            index_that_need_to_be_kept[size] = i;
            size++;
        }
        i++;
    }

    std::string new_word = "";

    for(int j = 0; j < size; j++) {
        int index = index_that_need_to_be_kept[j];
        new_word.push_back(word[index]);
    }

    word.assign(new_word);
}
void inverse_index_gen() {

    long int size = HASHTABLE_SIZE;
    int number_of_letters = ALPHABET_LETTER;

    //creat a hash table that will store the inverse index
    hash::Hash_String_Pair inverse_index(size, number_of_letters);

    // creat a hash table to use in a one document
    hash::Hash_String_Int count_of_words(size, number_of_letters);
    
    //inicialize both hash table
    inverse_index.initialize(vocabulary);
    count_of_words.initialize(vocabulary);

    int i = 0;
    // laço externo intera sobre cada documento
    std::ifstream corpus[number_of_files];

    for(auto doc: corpus) {

        std::string file_name = PROCESS_FILE_FOLDER;
        file_name.append(std::to_string(i));
        
        doc.open(file_name);
        erroAssert(doc.is_open(), "Erro: nao foi possivel abrir o arquivo");

        std::string word;
        
        // read the word of the document to the end
        while(doc >> word) {
            count_of_words.increment(word);
        }

        //insert the count_of_words inside of invert_index
        for(int j = 0; j < size; j++) {  //elem -> keys and values
            
            // if the word dont show on the file
            if( == 0) continue;

            else {
                invert_index.insert(elem.key, i, elem.value);
                //or
                Item item(i, value);
                invert_index.insert(elem.keym, item);
            }
        }

        i++;
    }
}