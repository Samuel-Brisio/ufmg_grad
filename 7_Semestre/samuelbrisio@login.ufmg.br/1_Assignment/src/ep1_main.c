#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "spend_time.h"

#define MAXRESOURCES 8

const int Debug = 0;

// Estrutura de Dados para representar os recursos requisitados por uma thread
typedef struct threadRequest {
    int resource[8]; // Array com o tamnho igual ao número de recursos disponiveis
    int nResource; // Numero de recursos requisitados
} threadRequest_t;


// Estrutura de Dados que irá armezenar as informações de uma threada
typedef struct ThreadParameters {
    pthread_t pthread_id;  // id dado pela biblioteca pthread
    int tid; // id passado pela entrada
    int freeTime;
    int criticalTime;
    threadRequest_t requestResource; // Recursos Requisitados pela thread
} threadInfo;

// Usado para recuperar os recursos requisitidados por uma thread em execução
typedef struct threadLink{
    pthread_t pthread_id;
    threadRequest_t *information;
} threadLink_t;

// Estrutura de Dados para os Recursos

struct Resource
{
    int available;
    pthread_t holdByThread;
};

struct Resource availableResources[8];


// typedef struct environmentResources {
//     // Array no qual cada index representa se o recurso está disponivel ou não (0 -> livre | 1 -> Ocupado)
//     int resouces[8];
//     // Array que irá guardar as thread que tem alocados a elas
//     threadLink_t holdByThread[8];
//     int numberThreadHaveResource; // Número de thread que tem recursos alocados
// } environmentResources_t;

// environmentResources_t availableResources;

// Inicializa um array com o número maximo de threads que podemos ter
threadInfo threads[1000];

// Mutex para a seção critica
// Irá proteger a estrutura de dados availableResources
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


int main(){
    // Buffer para o input
    char input[100];
    
    // Conta o numero de threads
    int nThread = 0;

    // Inicializa os Recursos
    init_recursos();
    
    // inicializa os mutex
    pthread_mutex_init(&getAvailableResource, NULL);

    // inicializa a variavel de condição
    pthread_cond_init ( &freeResource, NULL );

    while (fgets(input, sizeof(input), stdin)) {
        // ponteiro para o restante da string a ser convertida para inteiro
        char *ptr = input;
        // Ponteiro para o restante anterior, utilizado para verificar se a string já chegou no final
        char *lastPtr = NULL;
        
        threadInfo *thread = &threads[nThread];

        thread->tid = getIntFromString(&ptr, &lastPtr);
        thread->freeTime = getIntFromString(&ptr, &lastPtr);
        thread->criticalTime = getIntFromString(&ptr, &lastPtr);

        // Numero de Recursos que a string irá utilizar
        thread->requestResource.nResource = 0;
    
        // A thread irá requisitar pelo menos um recurso
        // Por isso o do-while
        do
        {
            thread->requestResource.resource[thread->requestResource.nResource] = getIntFromString(&ptr, &lastPtr);
            if (Debug) {
                printf("Thread %d pegou recurso: %d Total de Recursos: %d\n",
                 thread->tid, 
                 thread->requestResource.resource[thread->requestResource.nResource], 
                 thread->requestResource.nResource+1);
            }

            thread->requestResource.nResource++;

            if(thread->requestResource.nResource == 8) {
                break;
            }
        } while (ptr != lastPtr);

        // Para saber se todos os inteiros do inicio de uma string foram adquiridos
        // A função getIntFromString é executada duas vezes no final
        // E portanto devemos subtrair menor um do numero de recursos da thread para conseguir o
        // Valor real
        thread->requestResource.nResource--;

        // Informações para debug
        if(Debug) {
            printf("Thread Info: %d -> ", thread->tid);
            printf("Numero de recursos: %d || ", thread->requestResource.nResource);
            int i;
            for(i = 0; i < thread->requestResource.nResource; i++) {
                printf("%d ", thread->requestResource.resource[i]);
            }
            printf("\n");
        }

        // Cria uma thread
        pthread_create(&thread->pthread_id, NULL, &threadInit, thread);

        nThread++;
    }
    int i;
    for (i = 0; i < nThread; i++) {
        pthread_join(threads[i].pthread_id, NULL);
    }

    return 0;
}

int getIntFromString(char **input, char **ptr) {
    // Ponteiro será utilizado para retornar o restante da string
    char *end;
    *ptr = *input;
    int number = strtol(*input, &end, 10);
    // Atualiza o inicio do restante  da string
    *input = end;
    return number;

}

// Rotina de execução da thread
void *threadInit(void* arg) {
    threadInfo self = *(threadInfo *)arg;

    spend_time(self.tid, NULL , self.freeTime);
    trava_recursos(&self.requestResource);     // a forma de representar os recursos é uma decisão do desenvolvedor
    spend_time(self.tid,"C",self.criticalTime);
    libera_recursos();            // note que cada thread deve ser ter sua lista de recursos registrada em algum lugar
    pthread_exit(NULL); 

}

void trava_recursos(threadRequest_t *requestResource) {

    pthread_mutex_lock( &getAvailableResource );
    
    // A variavel isResourceAvaliable representa a possibilidade
    // Da thread adquirir os recursos
    // 1 significa que a thread pode adquirir os recursos
    // E 0 significa que NÃO pode adquirir os recursos
    while(!isResourceAvaliable(*requestResource)) {
        pthread_cond_wait(&freeResource, &getAvailableResource);
    }

    // Adquire os Recursos
    // int i;    
    // for (i = 0; i < requestResource->nResource; i++) {
    //     availableResources.resouces[requestResource->resource[i]] = 0;
    // }
    for (int i = 0; i < requestResource->nResource; i++) {
        int requestResourceIdx = requestResource->resource[i];
        availableResources[requestResourceIdx].available = 0;
        availableResources[requestResourceIdx].holdByThread = pthread_self();
    }
    
    pthread_mutex_unlock( &getAvailableResource );
}

void init_recursos(void) {
    // int i = 0;
    // for(i = 0; i < MAXRESOURCES; i++) {
    //     availableResources.resouces[i] = 1;
    //     availableResources.numberThreadHaveResource = 0;
    //     availableResources.holdByThread[i].pthread_id = 0;
    // }
    for(int i = 0; i < MAXRESOURCES; i++) {
        availableResources[i].available = 1;
        availableResources[i].holdByThread = 0;
    }
}   

void libera_recursos() {
    pthread_mutex_lock( &getAvailableResource );
    
    pthread_t pid = pthread_self();
    
    int i;
    for(i = 0; i < MAXRESOURCES; i++) {
        // Se o id da thread q está com o recurso for o msm a thread atual
        if(availableResources[i].holdByThread == pid) {
            // Marca que a thread não está mais ocupando os recursos
            availableResources[i].available = 1;
            availableResources[i].holdByThread = 0;

        }
    }
    
    pthread_mutex_unlock( &getAvailableResource );
    pthread_cond_broadcast(&freeResource);
}

int isResourceAvaliable(threadRequest_t requestResources) {
    int canGetResource = 1;
    int i;
    for (i = 0; i < requestResources.nResource; i++) {
        // IF one of the resources is equal 0
        // then this resource is already used by another thread
        // So this thread cannot get the resouces
        int resourceIdx = requestResources.resource[i];
        if (availableResources[resourceIdx].available == 0) {
            canGetResource = 0;
            break;
        }
    }
    return canGetResource;
}