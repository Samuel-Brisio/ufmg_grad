#include <iostream>
#include <fstream>
#include <getopt.h>
#include <string>
#include <filesystem>

//External Library
#include "msgassert.h"
#include "memlog.h"
#include "insercao.hpp"

//Self implemented data struct
#include "new_list.hpp"
#include "unic_list.hpp"
#include "hash.hpp"


#define PROCESS_FILE_FOLDER "/home/samuelbrisio/Documents/UFMG/Projetos_github/ufmg_grad/3 Semestre/Estrutura de Dados/Trabalho_Pratico_3/Processo/"
#define ALPHABET_LETTER 26
#define HASHTABLE_SIZE 12400001

//function prototype
void parse_args(int &number, char **pametros);
int get_number_of_files(std::string path);
int open_corpus(std::string path, int documet_indexes[]);
int get_document_index(std::string str);
void read_stopwords();
void read_search_file();
void to_lowercase(std::string &word);
bool is_stopword(std::string &word);
void remove_special_characters(std::string &word);
void inverse_index_gen(hash::Hash_String_Pair &hashtable);
void find_vocabulary();
void use_instruction();
template <typename T>
T** create_matrix(int &rows, int &columns);
template <typename T>
void initialize_matrix(T **matrix, int &rows, int &columns);
template <typename T>
void delete_matrix(T **matrix, int &rows, int &columns);
void document_weight_gen(hash::Hash_String_Pair &hashtable, double **matrix, int &rows, int &columns);
void search_weight_gen(hash::Hash_String_Pair &hashtable, bool **matrix, int &rows, int &columns);
void search_sum_weight_gen(hash::Hash_String_Pair &hashtable, bool **matrix, int &rows, int &columns);
void search_sum_weights(double sum_matrix[], bool **search_matrix, double **weight_matrix, int indexes[]);
void search_sum_weights_norm(double sum[], double ** weight_matrix, int indexes[]);
void find_indexes(Unic_List<int> &indexes_list);
void find_index(std::string word, Unic_List<int> &indexes_list);
void list_to_array(int indexes[], Unic_List<int> &indexes_list);
void greater_relevance(double similarity_arr[], int document_index[]);

//global variables
std::string input_name; // input file name
std::string output_name; // output file name 
std::string folder_path; // path for the folder that contais the corpus
int number_of_files; // number of files in the corpus
std::string stopwords_file_name;
Lista<Word> stopwords; // linked list that store the vocabulary
Unic_List<Word> vocabulary; // linked list that store the vocabulary
Unic_List<Word> search_words; // Linked List that store the words that needed to be searched

int main(int argc, char **argv) {

    // separa os argumentos passados para o programa
    parse_args(argc, argv);

    //le o arquivo de stopwords
    read_stopwords();

    // read the search file and store the search words in search_words list
    read_search_file();
    
    // count the number of files
    number_of_files = get_number_of_files(folder_path);

    //document index store the index
    // because non sequencial file name
    int document_indexes[number_of_files];
    
    // open the corpus
    // remove the stopwords and invalid words
    // remove special characters
    // save the acceptable words
    open_corpus(folder_path, document_indexes);

    unsigned long int size = HASHTABLE_SIZE;
    int number_of_letters = ALPHABET_LETTER;

    //creat a hash table that will store the inverse index
    hash::Hash_String_Pair inverse_index(size, number_of_letters);

    //inicialize both hash table
    inverse_index.initialize(vocabulary);

    //inverse index generator
    inverse_index_gen(inverse_index);

    std::ofstream inverse_file("/home/samuelbrisio/Documents/UFMG/Projetos_github/ufmg_grad/3 Semestre/Estrutura de Dados/Trabalho_Pratico_3/outros/invert_index");
    erroAssert(inverse_file.is_open(), "Error: couldn't open the file");

    inverse_index.print_all(inverse_file);

    //find -the document weight
    int rows = vocabulary.get_tamanho();
    int columns = number_of_files;
    double **document_weight = nullptr;

    document_weight = create_matrix<double>(rows, columns);
    initialize_matrix<double>(document_weight, rows, columns);
    document_weight_gen(inverse_index, document_weight, rows, columns);

    //find the indexes of search_words in document_weight
    Unic_List<int> indexes_list;
    find_indexes(indexes_list);

    int indexes[indexes_list.get_tamanho()]{0};

    // copy the data from indexes_list to indexes
    list_to_array(indexes, indexes_list);

    int arr[] = {121, 149, 166, 112};
    for(int i: indexes) {
        for(int j: arr) {
            std::cout << i << " , " << j << ": " << document_weight[i][j] << std::endl;
        }
    }

    //find the search weight
    bool **search_weight;
    rows = indexes_list.get_tamanho();
    columns = number_of_files;

    search_weight = create_matrix<bool>(rows, columns);
    initialize_matrix<bool> (search_weight, rows, columns);
    search_weight_gen(inverse_index, search_weight, rows, columns);

    //matrix to store the weight sum
    double search_sum[number_of_files]{0};

    //sum of the weights 
    search_sum_weights(search_sum, search_weight, document_weight, indexes);

    search_sum_weights_norm(search_sum, document_weight, indexes);

    greater_relevance(search_sum, document_indexes);

    delete_matrix(document_weight, rows, columns);
    delete_matrix(search_weight, rows, columns);

    return 0;
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

int get_number_of_files(std::string path) {
    int count = 0;

    for(const auto &doc : std::filesystem::directory_iterator(path)) count++;

    return count;
}


int open_corpus(std::string path, int document_indexes[]) {

    int count = 0;

    for(const auto &doc : std::filesystem::directory_iterator(path)) {

        //open the document
        std::ifstream input_file;
        input_file.open(doc.path());
        erroAssert(input_file.is_open(), "Erro: nao foi possivel abrir o arquivo");
        

        //archive's name that will contain the acceptable words
        std::string file_name = PROCESS_FILE_FOLDER;
        file_name.append(std::to_string(count));

        document_indexes[count] = get_document_index(doc.path().filename());

        // open file that will only have acceptable words
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
        
        count++;
        input_file.close();
        only_vocabulary_file.close();
    }
    return count;
}

int get_document_index(std::string str) {
    size_t pos = str.find(".txt");
    if(pos != std::string::npos) {
        str.erase(str.begin() + pos, str.end());
    }

    return std::stoi(str);
}

void read_stopwords() {
    std::ifstream stopwords_file;
    stopwords_file.open(stopwords_file_name);

    erroAssert(stopwords_file.is_open(), "Erro: nao foi possivel abrir o arquivo de stopwords");

    Word word;
    while(stopwords_file >> word.chave) stopwords.inseri_no_fim(word);
}

void read_search_file() {
    std::ifstream search_file(input_name);
    erroAssert(search_file.is_open(), "Error: could not open the file");

    Word word;
    while(search_file >> word.chave) {
        search_words.inseri_no_fim(word);
    }
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
        if(std::isdigit(c)) {
            word.assign("");
            return;
        }
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

void inverse_index_gen(hash::Hash_String_Pair &hashtable) {

    // laço externo intera sobre cada documento

    for(int i = 0; i < number_of_files; i++) {

        std::string file_name = PROCESS_FILE_FOLDER;
        file_name.append(std::to_string(i));
        
        std::ifstream doc(file_name);
        erroAssert(doc.is_open(), "Erro: nao foi possivel abrir o arquivo");

        std::string word;
        
        // read the word of the document to the end
        while(doc >> word) {
            unsigned long int hash = hashtable.get_hash(word);
            erroAssert(hash > 0, "Error: word not find");

            hashtable.increment(hash, i);
        }

        doc.close();
    }

}

template <typename T>
T** create_matrix(int &rows, int &columns) {
    T **matrix = new T*[rows];

    for(int i = 0; i < rows; i++) {
        matrix[i] = new T[columns];
    }

    return matrix;

}

template <typename T>
void initialize_matrix(T **matrix, int &rows, int &columns) {
    std::ofstream debug("/home/samuelbrisio/Documents/UFMG/Projetos_github/ufmg_grad/3 Semestre/Estrutura de Dados/Trabalho_Pratico_3/outros/debug.txt");
    erroAssert(debug.is_open(), "Erro");

    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < columns; j++) {
            matrix[i][j] = 0;
            debug << i << " " << j << std::endl;
        }
    }
}

template <typename T>
void delete_matrix(T **matrix, int &rows, int &columns) {
    for(int i = 0; i < rows; i++) {
        delete[] matrix[i];
    }

    delete[] matrix;

    matrix = nullptr;
}

/*
loop over vocabulary, for each word find its hash
then get the first element of the invert index list with that hash
and find the number of documents that this word appears
calculate the weight of the term frequency in the document
*/
void document_weight_gen(hash::Hash_String_Pair &hashtable, double **matrix, int &rows, int &columns) {
    Cell<Word> *ptr = vocabulary.get_primeiro_elemento();
    
    for(int i = 0; i < rows; i++) {

        unsigned long int hash = hashtable.get_hash(ptr->item.chave);
        erroAssert(hash > 0, "Error: invalid hash");

        Cell<Pair> *frequency = hashtable.get_first_element(hash);

        int num_of_docs_that_have_the_term = hashtable.get_hash_size(hash);
        
        int arr[] = {121, 149, 166, 112};
        
        for(int j = 0; j < columns; j++) {
            if(frequency == nullptr) break;
            if(frequency->item.id != j) continue;
            
            bool is_search_word = i == 395 || i == 336;
            bool is_document = false;

            for(int e: arr) is_document = e == j ? true : is_document;

            matrix[i][j] = frequency->item.frequency * std::log( (double)(number_of_files) / num_of_docs_that_have_the_term);

            // apagar
            if(is_search_word && is_document) std::cout << i << " , " << j << ": " << matrix[i][j] << ", frequency :" << frequency->item.frequency << std::endl;
            // apagar

            frequency = frequency->prox;
        }
        ptr = ptr->prox;
    }
    std::cout << "------------------------------------------------------------------" << std::endl;
}

/*
loop over search_words list, for each word find its hash
then get the first element of the invert index list
loop over the elements of this hash
*/
void search_weight_gen(hash::Hash_String_Pair &hashtable, bool **matrix, int &rows, int &columns) {
    Cell<Word> *ptr = search_words.get_primeiro_elemento();
    
    for(int i = 0; i < rows; i++) {
        unsigned long int hash = hashtable.get_hash(ptr->item.chave);
        erroAssert(hash > 0, "Error: invalid hash");

        Cell<Pair> *hash_elem = hashtable.get_first_element(hash);
        
        for(int j = 0; j < columns; j++) {
        
            if(hash_elem == nullptr || hash_elem->item.id != j) continue;

            erroAssert(hash_elem->item.id >= j, "Error: unordered index");
            matrix[i][j] = true;
            hash_elem = hash_elem->prox;
        }
        ptr = ptr->prox;
    }
}

// find the word indexes of the search words and words that contain search word
void find_indexes(Unic_List<int> &indexes_list) {
    Cell<Word> *ptr = search_words.get_primeiro_elemento();
    int rows = search_words.get_tamanho();

    for(int i = 0; i < rows; i++) {
        erroAssert(ptr != nullptr, "Error: null pointer");
        find_index(ptr->item.chave, indexes_list);
        ptr = ptr->prox;
    }
}

void find_index(std::string word, Unic_List<int> &indexes_list) {
    Cell<Word> *ptr = vocabulary.get_primeiro_elemento();
    int count = 0;

    while(ptr != nullptr) {
        if(ptr->item.chave.find(word) != std::string::npos) {
            indexes_list.insert(count);
            search_words.insert(ptr->item);
            std::cout << ptr->item.chave << std::endl;
        }
        ptr = ptr->prox;
        count++;
    }
}

void list_to_array(int indexes[], Unic_List<int> &indexes_list) {
    Cell<int> *ptr = indexes_list.get_primeiro_elemento();
    int count = 0;

    while(ptr != nullptr) {
        indexes[count] = ptr->item;
        ptr = ptr->prox;
        count++;
    }

    erroAssert(count <= indexes_list.get_tamanho(), "Error: count is bigger than indexes_list size");
}

void search_sum_weights(double sum_matrix[], bool **search_matrix, double **weight_matrix, int indexes[]) {
    int rows = search_words.get_tamanho();
    int columns = number_of_files;
    
    for(int i = 0; i < rows; i++) {        
        //indexes -> have the search_words indexes on the matrix 
        int index = indexes[i];

        for(int j = 0; j < columns; j++) {
            sum_matrix[j] += search_matrix[i][j] ? weight_matrix[index][j] : 0; 
        }
    }

}

void search_sum_weights_norm(double sum[], double ** weight_matrix, int indexes[]) {
    
    // create the wd and calculate
    double wd[number_of_files]{0};
    int rows = vocabulary.get_tamanho();
    int columns = number_of_files;

    // for each documest, square weight sum
    for(int i = 0; i < columns; i++) {
        for(int j = 0;  j < rows; j++) {
            wd[i] += pow(weight_matrix[j][i], 2);
        }
    }

    // square root of the sum
    for(int i = 0; i < columns; i++) {
        wd[i] = sqrt(wd[i]);
    }

    // Normalization divide the sum array by wd
    for(int i = 0; i < columns; i++) {
        sum[i] = sum[i] / wd[i];
    }
}

void greater_relevance(double similarity_arr[], int document_index[]) {
    // if the number_of_files is less than 10 range is equal number_of_files, else range is equal 10
    int range = number_of_files < 10 ? number_of_files : 10;

    std::ofstream ranking_file(output_name);
    erroAssert(ranking_file.is_open(), "Erro: Couldn't open the file");

    for(int i = 0; i < number_of_files; i++) {
        ranking_file << "( " << document_index[i] << " ,  " << similarity_arr[i] << " ,  " << i << " )" << "\t"; 
    }

    ranking_file << std::endl;

    Insercao<double>(similarity_arr, document_index, 0, number_of_files - 1, 0);

    for(int i = 0; i < range; i++) {
        if(similarity_arr[i] == 0) continue;
        //ranking_file << document_index[i] << " ";
        ranking_file << "( " << document_index[i] << " ,  " << similarity_arr[i] << " )" << "\t"; 
    }
    ranking_file << std::endl;

    ranking_file.close();
}