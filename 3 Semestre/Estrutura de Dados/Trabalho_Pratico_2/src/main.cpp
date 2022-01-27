#include <stdio.h>
#include <iostream>
#include <fstream>
#include <ctype.h>
#include <cstring>
#include <cmath>

#include "msgassert.h"
#include "quicksort.hpp"
#include "celula.hpp"
#include "heap.hpp"

#define PATH "/tmp/"
#define OUTPUT_PATH "output/"

// Imprimi o array
template <typename T>
void imprimi_arr(T arr[], int n, std::ostream &os = std::cout) {
    for(int i = 0; i < n; i++ ) {
        os << arr[i].url << " " << arr[i].chave << std::endl;
    }
}

// Retorna uma string com a mensagem de erro
char* errorMensage(char c) {
    switch (c)
    {
    case 'n':
        return "Erro: Argumentos 3 e 4 precisam ser numericos";
    case 'f':
        return "Erro: Nao foi possivel abrir o arquivo";
    default:
        return "Parametro ainda nao definido";
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

void intercala(int &number, std::string nome_arquivo_de_saida) {

    //heap datastruct 
    Heap<urlViews_fita> heap(number);
    // array de fitas
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

    std::ofstream outFile(OUTPUT_PATH + nome_arquivo_de_saida);
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
    for(int i = 0; i < number; i++) {
        fitas[i].close();
    }
    outFile.close();

}


// Função utilizada no intercala_rodadas_maior_fitas
void intercala(int &number, int rodada, std::string nome_arquivo_de_entrada, std::string nome_arquivo_de_saida) {

    //heap datastruct 
    Heap<urlViews_fita> heap(number);
    // array de fitas
    std::ifstream fitas[number];
    urlViews_fita tmp;
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
        urlViews_fita tmp;
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

// 
// intercala quando o numero de rodadas for maior que o numero de fitas
void intercala_rodadas_maior_fitas(int nFitas, int nRodadas, std::string nomeSaida) {
    // quantidade de vezes que o intercala será executado
    int repete = std::ceil(nRodadas / double(nFitas));
    int prox_rodada = 0;
    int rodada_restante = nRodadas;
    int numero_de_intercalacoes = 0;
    std::string nome_intermediario_outfile = PATH + std::string("intermediario");

    do {
        numero_de_intercalacoes++;

        for(int i = 0; i < repete; i++) {
            // gera o nome da fita intermediaria
            std::string nome = nome_intermediario_outfile;
            nome.append(std::to_string(numero_de_intercalacoes) + std::string("-") + std::to_string(i) + std::string(".txt"));

            int restante = rodada_restante - prox_rodada;
            if(restante < nFitas) {
                if(numero_de_intercalacoes == 1) {
                    intercala(restante, prox_rodada, PATH + std::string("rodada-"), nome);
                }
                else intercala(restante, prox_rodada, nome_intermediario_outfile + std::to_string(numero_de_intercalacoes - 1) + std::string("-"), nome);    
            }
            else {
                if(numero_de_intercalacoes == 1) {
                    intercala(nFitas, prox_rodada, PATH + std::string("rodada-"), nome);
                }
                else intercala(nFitas, prox_rodada, nome_intermediario_outfile + std::to_string(numero_de_intercalacoes - 1) + std::string("-"), nome);
            }
            prox_rodada += nFitas;
        }

        rodada_restante = repete;
        prox_rodada = 0;
        repete = std::ceil(repete / double(nFitas));

    } while(rodada_restante > nFitas);

    intercala(rodada_restante, prox_rodada, nome_intermediario_outfile + std::to_string(numero_de_intercalacoes) + std::string("-"), OUTPUT_PATH + nomeSaida);

}


// Verifica, trata e salva os argumentos passados para o programa
void parse_args(char **argv , std::string &name, std::string &out_name, int &memoria, int &n_fitas) {
    // Verificar se o arquivo é ponto txt
    name = argv[1];
    out_name = argv[2];
    
    erroAssert(isNumber(argv[3]), errorMensage('n'));
    memoria = std::atoi(argv[3]);
    erroAssert(memoria > 0, "Numero de entidades por fita invalido, valor informado eh negativo ou nulo");

    erroAssert(isNumber(argv[4]), errorMensage('n'));
    n_fitas = std::atoi(argv[4]);
    erroAssert(n_fitas > 0, "Numero de fitas invalido, valor informado é negativo ou nulo");
}

int main(int argc, char **argv) {

    if(argc < 5) {
        std::cout << "numero de argumentos invalido" << std::endl;
        return -1;
    }
    
    std::string nome_entrada; // nome do arquivo de entrada
    std::string nome_saida; // nome do arquivo de saida
    int memoria_tamanho; // tamanho da memória, ou a quantidade de entidades por arquivo
    int n_fitas; // Quandidade de fitas que devem ser geradas
    
    parse_args(argv, nome_entrada, nome_saida,memoria_tamanho, n_fitas);

    std::ifstream file;

    file.open(nome_entrada);

    if(!file.is_open()) {
        std::cout << "Erro: nao foi possivel abrir o arquivo " << nome_entrada << std::endl;
        return -2;
    }

    int n_rodadas = gera_rodadas(memoria_tamanho, file);

    // se o numero de rodadas for maior que o numero de fitas
    if(n_rodadas > n_fitas) {
        intercala_rodadas_maior_fitas(n_fitas, n_rodadas, nome_saida);
    }

    else intercala(n_rodadas, nome_saida);

    file.close();

    return 0;
}