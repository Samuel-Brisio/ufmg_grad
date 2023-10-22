#include "server.h"

int main(int argc, char *argv[]) {

    arg_parsing(argc, argv);

    signal(SIGINT, interrupt_handler);

    if(server_sockaddr_parse(IP_version, SERVER_PORT, &storage) == 1) {
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

    /* accept is a blocking call and the call would stop further invocation of
    code till a client connection is accepted */
    client_length = sizeof(client_addr);
    
    for (;;) {
        clientfd = accept(serverfd, (struct sockaddr *)&client_addr, &client_length);
        printf("client connected\n");

        if (clientfd < 0) {
            printf("Unable to connect to Client FD\n");
            exit(1);
        }

        /* read and write data from/to client socket */
        for (;;) {
        }
        printf("client disconnected\n");    
        close(clientfd);
    }

    close(serverfd);
    return 0;
}

void arg_parsing(int argc, char *argv[]) {
    int opt;

    if (argc < 5) {
        printf("Number of Arguments: %d\n", argc);       
        exit(1);
    }

    if (strcmp("v4", argv[1]) == 0) IP_version = 0;
    else if (strcmp("v6", argv[1]) == 0) IP_version = 1;
    else {
        printf("Invalid Ip version\n");
        exit(1);
    }

    sscanf(argv[2], "%d", &SERVER_PORT);

    while ((opt = getopt(argc, argv, "i:")) != -1) {
        switch (opt) {
        case 'i': 
            // printf("%s\n", optarg);
            strcpy(filename, optarg); 
            break;
        
        default:
            fprintf(stderr, "Usage: %s [-i] [files...]\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }
}

void interrupt_handler (int signum) {
    close(serverfd);

    printf("socket connection closed\n");
    exit(0);
}