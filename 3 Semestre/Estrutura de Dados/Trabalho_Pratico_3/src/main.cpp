#include <iostream>
#include <fstream>

#define PROCESSFILEFOLDER "Processo/"
#define ALPHABET_LETTER 26

//function prototype
void parse_args(int &number, char **pametros);
void open_corpus(std::string folder);
void inverse_index_gen();
void find_vocabulary();

//global variables
std::string path_folder; // path for the folder that contais the corpus
int number_of_files; // number of files in the corpus
//todo   // list of files from the corpus
//todo   // list of files that contain only vocabulaty words


int main(int argc, char **argv) {

    // separa os argumentos passados para o programa
    parse_args(argc, argv);

    // abre os documentos
    open_corpus();

    //le o arquivo de stopwords
    open_stopwords();

    //encontra o vocabulario
    find_vocabulary();

    //gera o indice inverso
    inverse_index_gen();



}

void parse_args(int &number, char **pametros) {
    

}

void open_corpus(std::string folder) {

}

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
            count_of_words.increment(word /*key*/);
            //or
            int value = count_of_words.get_value(word /*key*/);
            count_of_words.set_value(word /*key*/, value + 1);
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