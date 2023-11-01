#include "server.h"

int main(int argc, char *argv[]) {

    signal(SIGINT, interrupt_handler);

    if(server_sockaddr_parse(argv[1], argv[2], &storage) == 1) {
        perror("server sockaddr parse");
        exit(-1);
    }


    /*************************************************/
    /* Create a stream socket                        */
    /*************************************************/
    serverfd = socket(storage.ss_family, SOCK_STREAM, IPPROTO_TCP);
    if (serverfd < 0)
    {
      perror("socket");
      exit(-1);
    }
    
    /*************************************************/
    /* Bind to the local address                     */
    /*************************************************/
    struct sockaddr *addr = (struct sockaddr *)(&storage);
    if(bind(serverfd, addr, sizeof(storage)) != 0){
        printf("bind() failed\n");
        exit(-1);
    }


    /*************************************************/
    /* accept upto 5 pending requests                */
    /* and make the server socket a passive socket   */
    /*************************************************/
    if (listen(serverfd, 5) == -1) {
            printf("Listen Failed\n");
            exit(1);
    }

    
    for (;;) {
        /* accept is a blocking call and the call would stop further invocation of
        code till a client connection is accepted */

        struct sockaddr_storage cstorage;
        struct sockaddr *caddr = (struct sockaddr *) (&cstorage);
        client_length = sizeof(struct sockaddr_storage);

        clientfd = accept(serverfd, (struct sockaddr *)&caddr, &client_length);
        printf("client connected\n");

        if (clientfd < 0) {
            printf("Unable to connect to Client\n");
            exit(1);
        }

        struct client_data *cdata = malloc(sizeof(struct client_data));
        if (!cdata) {
            printf("malloc");
            exit(1);
        }
        cdata->csock = clientfd;
        memcpy(&(cdata->storage), &storage, sizeof(storage));

        pthread_t tid;
        pthread_create(&tid, NULL, client_thread, cdata); 
  
        
    }

    close(serverfd);
    return 0;
}

void * client_thread(void *data) {
    struct client_data *cdata = (struct client_data *) data;
    struct sockaddr *cadddr = (struct sockaddr *)(&cdata->storage);

    // TODO APLICATION RUN HERE
    /* read and write data from/to client socket */
    for (;;) {
    
    }


    printf("client disconnected\n");    
    close(clientfd);

    // Tenho que dar um free na memoria

    pthread_exit(EXIT_SUCCESS);
}


void interrupt_handler (int signum) {
    close(serverfd);

    printf("socket connection closed\n");
    exit(0);
}