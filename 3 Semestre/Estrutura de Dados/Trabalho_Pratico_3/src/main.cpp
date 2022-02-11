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

#define PROCESSFILEFOLDER "Processo/"
#define ALPHABET_LETTER 26

//function prototype
void parse_args(int &number, char **pametros);
int open_corpus(std::string folder);
void read_stopwords();
void inverse_index_gen();
void find_vocabulary();
void use_instruction();

//global variables
std::string input_name; // input file name
std::string output_name; // output file name 
std::string folder_path; // path for the folder that contais the corpus
int number_of_files; // number of files in the corpus
std::string stopwords_file_name;
Lista<Stopword_pointer, Stopword> stopwords; // Lista encadeada que irá armazenar as stopwords
//todo   // list of files from the corpus
//todo   // list of files that contain only vocabulaty words


int main(int argc, char **argv) {

    // separa os argumentos passados para o programa
    parse_args(argc, argv);

    //le o arquivo de stopwords
    read_stopwords();

    // abre os documentos
    number_of_files = open_corpus(folder_path);

    /*
    

    //encontra o vocabulario
    find_vocabulary();

    //gera o indice inverso
    inverse_index_gen();
    */


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

    for (const auto & entry : std::filesystem::directory_iterator(path)) {
    std::cout << entry.path() << std::endl;
    i++;
    }

    return i;

}

void read_stopwords() {
    return;
}

/*
void find_vocabulary() {
    //Creat new files with only the words from vocabulary
    //todo

    std::string words;

    for(int i = 0; i < number_of_files; i++) {
        while(original_documents[i] >> word) {

            if(is_stopword(word)) continue;

            remove_special_chracters(word);

            to_lowercase(word);

            only_vocabulary_files[i] << word << " ";
            
            //insert the word in the vocabulary list
            //the list accept only unic elements
            vocabulaty.add(word);
        }

    }
}

void inverse_index_gen() {

    int vocabulary_size = //todo

    // creat hash table
    //Hash invert_index
    //todo

    // creat a hash table to use in a one document
    // Hash<int> count_of_words
    // todo

    int i = 0;
    // laço externo intera sobre cada documento
    for(auto doc: only_vocabulaty_files) {

        int i = 0;
        //le as palavras do documento até o final do arquivo
        while(doc >> word) {
            count_of_words.increment(word); //word -> key
            //or
            int value = count_of_words.get_value(word); // word -> key
            count_of_words.set_value(word, value + 1);
        }

        //insert the count_of_words, inside of invert_index
        for(auto elem: count_words) {  //elem -> keys and values
            
            // if the word dont show on the file
            if(elem.value == 0) continue;

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

*/