#include "atomic_multiple_lock.h"
#include "spend_time.h"

int main(){
    // Buffer para o input
    char input[50];
    
    // Conta o numero de threads
    int nThread = 0;

    // Inicializa os Recursos
    init_recursos();

    
    // inicializa os mutex
    pthread_mutex_init(&testResource, NULL);
    pthread_mutex_init(&resourceStatus, NULL);

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
        thread->nResource = 0;
    
        // A thread irá requisitar pelo menos um recurso
        do
        {
            thread->resource[thread->nResource] = getIntFromString(&ptr, &lastPtr);
            thread->nResource++;
        } while (ptr != lastPtr);

        // Para saber se todas os inteiros do inicio de uma string foram adquiridos
        // A função getIntFromString é executada duas vezes no final
        // E portanto devemos subtrair menor um do numero de recursos da thread para conseguir o
        // Valor real
        thread->nResource--;

        if(Debug) {
            printf("Thread Info: %d -> ", thread->tid);
            printf("Numero de recursos: %d || ", thread->nResource);
            int i;
            for(i = 0; i < thread->nResource; i++) {
                printf("%d ", thread->resource[i]);
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

    trava_recursos(self.resource, self.nResource);     // a forma de representar os recursos é uma decisão do desenvolvedor
    spend_time(self.tid,"C",self.criticalTime);
    libera_recursos(self.resource, self.nResource);            // note que cada thread deve ser ter sua lista de recursos registrada em algum lugar
    pthread_exit(NULL); 

}

void trava_recursos(int resource[8], int nResource) {
    // A variavel getRosource representa a possibilidade
    // Da thread adquirir os recursos
    // 1 significa que a thread pode adquirir os recursos
    // E 0 significa que NÃO pode adquirir os recursos
    int getResource = 1;
    do
    {
        pthread_mutex_lock( &testResource );
        getResource = 1;
        int i;
        for (i = 0; i < nResource; i++) {
            // IF one of the resources is equal one
            // then this resource is already used by another thread
            // So this thread cannot get the resouces
            if (resources[resource[i]].status== 1) {
                getResource = 0;
                break;
            }
        }

        // if the thread can get the resources
        // then we update his status
        pthread_mutex_lock(&resourceStatus);
        if (getResource) {
            for (i = 0; i < nResource; i++) {
                resources[resource[i]].status = 1;
            }
        }
        pthread_mutex_unlock(&resourceStatus);
        
        pthread_mutex_unlock( &testResource );
    } while (!getResource);
    
    
}

void init_recursos(void) {
    int i = 0;
    for(i = 0; i < MAXRESOURCES; i++)
        resources[i].status = 0;
}

void libera_recursos(int resource[8], int nResource) {
    pthread_mutex_lock(&resourceStatus);
    int i;
    for (i = 0; i < nResource; i++) {
        resources[resource[i]].status = 0;
    }
    pthread_mutex_unlock(&resourceStatus);
}