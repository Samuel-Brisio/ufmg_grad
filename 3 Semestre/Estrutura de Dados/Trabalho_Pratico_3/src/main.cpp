#include <iostream>

#define PROCESSFILEFOLDER "Processo/"

//function prototype
void open_corpus(std::string folder);
void inverse_index_gen();
void find_vocabulary();

//global variables
std::string path_folder;


int main() {

    // separa os argumentos passados para o programa
    parse_args();

    // abre os documentos
    open_corpus();

    //le o arquivo de stopwords
    open_stopwords();

    //encontra o vocabulario
    find_vocabulary();

    //gera o indice inverso
    inverse_index_gen();

}

void open_corpus(std::string folder) {

}

void find_vocabulary() {

}

void inverse_index_gen() {
    // cria a tabela hash
    //todo


    // laço externo intera sobre cada documento
    for(auto doc: corpus) {

        //le as palavras do documento até o final do arquivo
        while(doc >> word) {
            // caso a palavra seja uma stopword
            if(is_stopword()) continue;
            
            
            else {
                

            }
        }
    }
}