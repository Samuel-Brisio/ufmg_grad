#ifndef HEADER_ATOMIC_LOCK
#define HEADER_ATOMIC_LOCK

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXRESOURCES 8

const int Debug = 0;

// Convert retorna o primeiro inteiro em uma string
int getIntFromString(char **input, char **ptr);

// inicializa a estrutura de dados que você 
// definir para representar os recursos;
void init_recursos(void); 

// uma thread pede para reservar um conjunto de recursos,
// representados da forma que seu programa preferir;
void trava_recursos(int resource[8], int nResource);

// uma thread que já reservou alguns recursos sinaliza 
// que completou seu trabalho crítico, liberando os recursos. 
void libera_recursos(int resource[8], int nResource);

// Função que as Thread irão executar
void *threadInit(void* arg);

// Estrutura de Dados para os Recursos
typedef struct mutexResource
{
    int status; // 0 Free || 1 Busy 
    pthread_mutex_t mutex;
} mutexResource_t;

mutexResource_t resources[8];

// Estrutura de Dados que irá armezenar as informações das threads
typedef struct ThreadParameters {
    pthread_t pthread_id;
    int tid;
    int freeTime;
    int criticalTime;
    // Array com o tamnho igual ao número de recursos disponiveis
    int resource[8];
    int nResource;// Numero de recursos requisitados

} threadInfo;

// Inicializa um array com o número maximo de threads que podemos ter
threadInfo threads[1000];


pthread_mutex_t testResource;
pthread_mutex_t resourceStatus;

#endif
