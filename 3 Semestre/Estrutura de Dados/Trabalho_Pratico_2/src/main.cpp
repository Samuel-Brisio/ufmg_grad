#include <stdio.h>
#include <iostream>
#include <fstream>
#include "msgassert.h"
#include "quicksort.hpp"
#include "celula.hpp"
#include "aux_function.hpp"
#include "heap.hpp"

#define PATH "/tmp/"


// Le a entrada e salva os dados em um array
int le_entidade(Celula arr[] , int const &number, std::istream &is) {
    
    erroAssert(number > 0, "Quantidade de memória invalida");
    
    int i = 0;
    
    //Le "number" entradas ou menos, caso não tenha mais entrada
    while(is >> arr[i].url >> arr[i].chave) {
        i++;  
        if(i >= number) break;
    }
    
    return i;
}

void escreve_arquivo(Celula arr[], int &numb, std::string name) {
    
    erroAssert(numb > 0, "Numero de elementos invalidos");
    
    std::ofstream outfile(PATH + name);

    if(!outfile.is_open()) {
        std::cout << "Erro: não foi possivel abrir o aquivo " << PATH + name << std::endl;
        exit(-5); 
    }

    imprimi_arr(arr, numb, outfile);

    outfile.close();
}


// obtem os dados necessários atravez do getline 
void get_input(std::string &input, std::string &str, int &number) {
    size_t pos = input.find(" ");
    str = input.substr(0, pos);
    number = std::stoi(input.substr(pos+1));
}

// Sepera a entrada em diversas fitas ordenadas
int gera_rodadas(int number, std::istream &is = std::cin) {

    erroAssert(number > 0, "Quantidade de memória invalida");
    
    Celula arr[number];
    int entidades = number;
    int rodada = 0;

    while(entidades == number)  {

        //salva os dados da entrada em um arr
        entidades = le_entidade(arr, number, is);

        // Ordena o array
        quick::quickSort(arr, 0, entidades - 1);

        std::string nome = ("rodada-") + std::to_string(rodada);
        nome.append(".txt");

        // Salva os dados do array em um arquivo externo
        if(entidades != 0) escreve_arquivo(arr, entidades, nome);
        
        rodada++;
    }

    return rodada;

}

void intercala(int &number, Heap<urlViews_fita> &heap) {
    
    std::ifstream fitas[number];
    urlViews_fita tmp;
    std::string input;

    for(int i = 0; i < number; i++) {
        std::string nome = ("rodada-") + std::to_string(i);
        nome.append(".txt");

        fitas[i].open(PATH + nome);
    }

    for(int i = 0; i < number; i++) {
        getline(fitas[i], input);
        get_input(input, tmp.url, tmp.chave);
        tmp.fita = i;
        heap.insere(tmp);
    }

    std::ofstream outFile("output/saida_esperada.txt");
    erroAssert(outFile.is_open(), "Erro: nao foi possivel abrir o arquivo de saida");

    while(!heap.vazio()) {
        urlViews_fita tmp;
        tmp = heap.remove();

        outFile << tmp.url << " " << tmp.chave << std::endl;

        if(getline(fitas[tmp.fita], input)) {
            get_input(input, tmp.url, tmp.chave);
            heap.insere(tmp);
        }
    }

    //fechar os arquivos

    
}

void parse_args(char **argv , std::string &name, std::string &out_name, int &memoria, int &n_fitas) {
    name = argv[1];
    out_name = argv[2];
    memoria = std::atoi(argv[2]);
    n_fitas = std::atoi(argv[3]);
}

int main(int argc, char **argv) {

    if(argc < 4) {
        std::cout << "numero de argumentos invalido" << std::endl;
        return -1;
    }

    std::cout << argc << " " << argv[1] << std::endl;
    
    std::string nome; // nome do arquivo de entrada
    std::string nome_saida; // nome do arquivo de saida
    int memoria_tamanho; // tamanho da memória, ou a quantidade de entidades por arquivo
    int n_fitas; // Quandidade de fitas que devem ser geradas
    
    parse_args(argv, nome, nome_saida,memoria_tamanho, n_fitas);

    std::ifstream file;

    file.open(nome);

    if(!file.is_open()) {
        std::cout << "Erro: nao foi possivel abrir o arquivo " << nome << std::endl;
        return -2;
    }

    n_fitas = gera_rodadas(memoria_tamanho, file);

    //heap datastruct 
    Heap<urlViews_fita> heap(n_fitas);

    intercala(n_fitas, heap);

    file.close();

    return 0;
}