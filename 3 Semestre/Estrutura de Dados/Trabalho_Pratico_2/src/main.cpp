#include <stdio.h>
#include <iostream>
#include <fstream>
#include <ctype.h>
#include <cstring>
#include <cmath>
#include <string>
#include <chrono>
#include <unistd.h>

#include "msgassert.h"
#include "memlog.h"
#include "structs.hpp"
#include "heap.hpp"
#include "quicksort.hpp"

#define PATH "/tmp/"
#define OUTPUT_PATH ""
#define micro_s std::chrono::microseconds

int heap_id = 0;
char log_name[100];
int regem;


// Imprimi o array
template <typename T>
void imprimi_arr(T arr[], int n, int id, std::ostream &os = std::cout) {
    for(int i = 0; i < n; i++ ) {
        os << arr[i].url << " " << arr[i].chave << std::endl;
        escreveMemLog((long int) &arr[i], sizeof(T), id);
    }
}

// Verifica se uma string contém somente numeros
bool isNumber(char *str) {
    int i = 0;

    while(str[i] != '\0') {
        if(!isdigit(str[i])) return false;
        i++;
    }
    return true;
}

// Le a entrada e salva os dados em um array
int le_entidade(Url_views arr[] , int const &number, int id, std::istream &is) {
    
    erroAssert(number > 0, "Quantidade de memória invalida");
    
    int i = 0;
    
    //Le "number" entradas ou menos, caso não tenha mais entrada
    while(is >> arr[i].url >> arr[i].chave) {
        escreveMemLog((long int)&arr[i], sizeof(Url_views), id);
        i++;  
        if(i >= number) break;
    }
    
    return i;
}

void escreve_arquivo(Url_views arr[], int &numb, int id, std::string name) {
    
    erroAssert(numb > 0, "Numero de elementos invalidos");
    
    std::ofstream outfile(PATH + name);

    erroAssert(outfile.is_open(), "Erro: não foi possivel abrir o aquivo ");

    imprimi_arr(arr, numb, id,outfile);

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
    
    Url_views arr[number];
    int entidades = number;
    int rodada = 0;

    while(entidades == number)  {

        //salva os dados da entrada em um arr
        entidades = le_entidade(arr, number, rodada, is);

        if(entidades == 0) break;

        // Ordena o array
        qs::quicksort(arr, 0, entidades - 1, rodada);

        std::string nome = ("rodada-") + std::to_string(rodada);
        nome.append(".txt");

        // Salva os dados do array em um arquivo externo
        if(entidades != 0) escreve_arquivo(arr, entidades, rodada, nome);
        
        rodada++;
    }

    return rodada;
}

// intercala n arquivos
void intercala(int &number, int rodada, std::string nome_arquivo_de_entrada, std::string nome_arquivo_de_saida) {

    //heap datastruct 
    Heap<Url_views_tape> heap(number, heap_id);
    heap_id++;
    // array de fitas
    std::ifstream fitas[number];
    Url_views_tape tmp;
    std::string input;

    for(int i = 0; i < number; i++) {
        std::string nome = nome_arquivo_de_entrada + std::to_string(rodada + i);
        nome.append(".txt");

        fitas[i].open(nome);
        erroAssert(fitas[i].is_open(), "Erro: nao foi possivel abrir o arquivo");
    }

    for(int i = 0; i < number; i++) {
        getline(fitas[i], input);
        get_input(input, tmp.url, tmp.chave);
        tmp.fita = i;
        heap.insere(tmp);
    }

    std::ofstream outFile(nome_arquivo_de_saida);
    erroAssert(outFile.is_open(), "Erro: nao foi possivel abrir o arquivo de saida");

    while(!heap.vazio()) {
        Url_views_tape tmp;
        tmp = heap.remove();

        outFile << tmp.url << " " << tmp.chave << std::endl;

        if(getline(fitas[tmp.fita], input)) {
            get_input(input, tmp.url, tmp.chave);
            heap.insere(tmp);
        }
    }

    //fechar os arquivos
    for(int i = 0; i < number; i++) {
        fitas[i].close();
    }
    outFile.close();

}

// intercala quando o numero de rodadas for maior que o numero de fitas
void intercala_rodadas_maior_fitas(int nFitas, int nRodadas, std::string nomeSaida) {
    
    erroAssert(nFitas >= 2, "Erro: o numero de fitas deve ser igual ou maior a dois");
    erroAssert(nRodadas > 0, "Erro: o numero de rodadas deve ser maior que um");

    // quantidade de vezes que o intercala será executado no loop do for
    int repete = std::ceil(nRodadas / double(nFitas));

    // Guarda o indice do proximo arquivo a ser intercalo    
    int prox_rodada = 0;

    // quantas rodadas ainda restam, utlizado no for loop
    int rodada_restante = nRodadas;

    // Quantas vezes o while loop foi executado  
    int numero_de_intercalacoes = 0;

    // estrutura de como será os nomes dos arquivos intermediarios
    std::string nome_intermediario_outfile = PATH + std::string("intermediario");
    
    //variaveis de controle
    bool e_primeira_intercalacao;

    do {
        numero_de_intercalacoes++;
        e_primeira_intercalacao = numero_de_intercalacoes == 1;

        for(int i = 0; i < repete; i++) {

            // gera o nome da fita intermediaria
            std::string nome = nome_intermediario_outfile;
            nome.append(std::to_string(numero_de_intercalacoes) + std::string("-") + std::to_string(i) + std::string(".txt"));

            // Quantos arquivos serão lidos no intercala
            int n_aquivos;
            if(rodada_restante > nFitas) n_aquivos = nFitas;
            else n_aquivos = rodada_restante;

            if(e_primeira_intercalacao) {
                intercala(n_aquivos, prox_rodada, PATH + std::string("rodada-"), nome);
            }
            else intercala(n_aquivos, prox_rodada, nome_intermediario_outfile + std::to_string(numero_de_intercalacoes - 1) + std::string("-"), nome);

            prox_rodada += nFitas;  
            rodada_restante -= nFitas;          
        }

        rodada_restante = repete;
        prox_rodada = 0;
        repete = std::ceil(repete / double(nFitas));

    } while(rodada_restante > nFitas);

    intercala(rodada_restante, prox_rodada, nome_intermediario_outfile + std::to_string(numero_de_intercalacoes) + std::string("-"), OUTPUT_PATH + nomeSaida);
}


// Verifica, trata e salva os argumentos passados para o programa
void parse_args(int &argc, char **argv , std::string &name, std::string &out_name, int &memoria, int &n_fitas) {

    name = argv[1];
    out_name = argv[2];
    
    erroAssert(isNumber(argv[3]), "Erro: O terceiro parametro não é um numero");
    memoria = std::atoi(argv[3]);
    erroAssert(memoria > 0, "Numero de entidades por fita invalido, valor informado eh negativo ou nulo");
    erroAssert(isNumber(argv[4]), "Erro: O terceiro parametro não é um numero");
    n_fitas = std::atoi(argv[4]);
    erroAssert(n_fitas > 1, "Numero de fitas invalido, valor informado e menor que 1");

    // caso o nome do arquivo de log seja passado como parametro
    if(argc == 6) {
        std::strcpy(log_name, argv[5]);
        regem = 1;
    }
    else {
        strcpy(log_name, "log.txt");
        regem = 0;
    }
}

int main(int argc, char **argv) {

    auto start = std::chrono::steady_clock::now();

    if(argc < 5) {
        std::cout << "numero de argumentos invalido" << std::endl;
        return -1;
    }

    std::string nome_entrada; // nome do arquivo de entrada
    std::string nome_saida; // nome do arquivo de saida
    int memoria_tamanho; // tamanho da memória, ou a quantidade de entidades por arquivo
    int n_fitas; // Quandidade de fitas que devem ser geradas

    parse_args(argc, argv, nome_entrada, nome_saida, memoria_tamanho, n_fitas);
    
    iniciaMemLog(log_name);

    if(regem)  ativaMemLog();
    else desativaMemLog();

    std::ifstream file;

    file.open(nome_entrada);

    if(!file.is_open()) {
        std::cout << "Erro: nao foi possivel abrir o arquivo " << nome_entrada << std::endl;
        return -2;
    }

    defineFaseMemLog(0);

    int n_rodadas = gera_rodadas(memoria_tamanho, file);

    auto mid = std::chrono::steady_clock::now();
    defineFaseMemLog(1);
    heap_id = n_rodadas + 1;

    // se o numero de rodadas for maior que o numero de fitas
    if(n_rodadas > n_fitas) {
        intercala_rodadas_maior_fitas(n_fitas, n_rodadas, nome_saida);
    }
    else if (n_rodadas == 1) {
        // copia rodada para o arquivo de saida
    }

    else intercala(n_rodadas, 0, PATH + std::string("rodada-"), OUTPUT_PATH + nome_saida);
    
    file.close();

    auto end = std::chrono::steady_clock::now();

    auto fase_1 = std::chrono::duration_cast<micro_s>(mid - start).count();
    auto fase_2 = std::chrono::duration_cast<micro_s>(end - mid).count();
    auto total = fase_1 + fase_2;
    std::cout << fase_1 << " " << fase_2 << " " <<total << std::endl;

    return finalizaMemLog();
}