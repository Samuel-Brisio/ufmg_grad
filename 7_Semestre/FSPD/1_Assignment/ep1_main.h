#ifndef HEADER_ATOMIC_LOCK
#define HEADER_ATOMIC_LOCK

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXRESOURCES 8

const int Debug = 0;

// Estrutura de Dados para representar os recursos requisitados por uma thread
typedef struct threadRequest {
    int resource[8];
    int nResource; // Numero de recursos requisitados
} threadRequest_t;


// Estrutura de Dados que irá armezenar as informações das threads
typedef struct ThreadParameters {
    pthread_t pthread_id;
    int tid;
    int freeTime;
    int criticalTime;
    threadRequest_t requestResource;
    // Array com o tamnho igual ao número de recursos disponiveis
} threadInfo;

typedef struct threadLink{
    pthread_t pthread_id;
    threadRequest_t *information;
} threadLink_t;

// Estrutura de Dados para os Recursos
typedef struct environmentResources {
    int resouces[8];
    threadLink_t holdByThread[8];
    int numberThreadHaveResource;
} environmentResources_t;

environmentResources_t availableResources;

// Inicializa um array com o número maximo de threads que podemos ter
threadInfo threads[1000];


pthread_mutex_t getAvailableResource;

// Declaration of thread condition variable
pthread_cond_t freeResource;

// Convert retorna o primeiro inteiro em uma string
int getIntFromString(char **input, char **ptr);

// inicializa a estrutura de dados que você 
// definir para representar os recursos;
void init_recursos(void); 

// uma thread pede para reservar um conjunto de recursos,
// representados da forma que seu programa preferir;
void trava_recursos(threadRequest_t *resources);

// uma thread que já reservou alguns recursos sinaliza 
// que completou seu trabalho crítico, liberando os recursos. 
void libera_recursos();

// Função que as Thread irão executar
void *threadInit(void* arg);

// Função que verifica se os recursos requisitados então livres
int isResourceAvaliable(threadRequest_t requestResources);


#endif
