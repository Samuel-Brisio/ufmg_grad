#include "atomic_multiple_lock.h"
#include "spend_time.h"

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

        // Para saber se todas os inteiros do inicio de uma string foram adquiridos
        // A função getIntFromString é executada duas vezes no final
        // E portanto devemos subtrair menor um do numero de recursos da thread para conseguir o
        // Valor real
        thread->requestResource.nResource--;

        if(Debug) {
            printf("Thread Info: %d -> ", thread->tid);
            printf("Numero de recursos: %d || ", thread->requestResource.nResource);
            int i;
            for(i = 0; i < thread->requestResource.nResource; i++) {
                printf("%d ", thread->requestResource.resource[i]);
            }
            printf("\n");
        }

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

void *threadInit(void* arg) {
    threadInfo self = *(threadInfo *)arg;

    spend_time(self.tid, NULL , self.freeTime);
    trava_recursos(&self.requestResource);     // a forma de representar os recursos é uma decisão do desenvolvedor
    spend_time(self.tid,"C",self.criticalTime);
    libera_recursos();            // note que cada thread deve ser ter sua lista de recursos registrada em algum lugar
    pthread_exit(NULL); 

}

void trava_recursos(threadRequest_t *requestResource) {
    // A variavel getRosource representa a possibilidade
    // Da thread adquirir os recursos
    // 1 significa que a thread pode adquirir os recursos
    // E 0 significa que NÃO pode adquirir os recursos

    pthread_mutex_lock( &getAvailableResource );
    
    while(!isResourceAvaliable(*requestResource)) {
        pthread_cond_wait(&freeResource, &getAvailableResource);
    }

    int i;    
    for (i = 0; i < requestResource->nResource; i++) {
        availableResources.resouces[requestResource->resource[i]] = 0;
    }

    availableResources.holdByThread[availableResources.numberThreadHaveResource].pthread_id = pthread_self();
    availableResources.holdByThread[availableResources.numberThreadHaveResource].information = requestResource;
    availableResources.numberThreadHaveResource++;
    
    pthread_mutex_unlock( &getAvailableResource );
}

void init_recursos(void) {
    int i = 0;
    for(i = 0; i < MAXRESOURCES; i++) {
        availableResources.resouces[i] = 1;
        availableResources.numberThreadHaveResource = 0;
        availableResources.holdByThread[i].pthread_id = 0;
    }
}   

void libera_recursos() {
    // To Do
    pthread_mutex_lock( &getAvailableResource );
    
    pthread_t pid = pthread_self();
    threadRequest_t *requestResource;
    
    int i;
    for(i = 0; i < availableResources.numberThreadHaveResource; i++) {
        if(availableResources.holdByThread[i].pthread_id == pid) {
            requestResource = availableResources.holdByThread[i].information;

            // Marca que a thread não está mais ocupando os recursos
            availableResources.holdByThread[i].pthread_id = 0;

        }
    }
    
    for (i = 0; i < requestResource->nResource; i++) {
        availableResources.resouces[requestResource->resource[i]] = 1;
    }

    pthread_mutex_unlock( &getAvailableResource );
    pthread_cond_broadcast(&freeResource);
}

int isResourceAvaliable(threadRequest_t requestResources) {
    int canGetResource = 1;
    int i;
    for (i = 0; i < requestResources.nResource; i++) {
        // IF one of the resources is equal one
        // then this resource is already used by another thread
        // So this thread cannot get the resouces
        if (availableResources.resouces[requestResources.resource[i]] == 0) {
            canGetResource = 0;
            break;
        }
    }
    return canGetResource;
}