#include "client.h"

int main(int argc, char *argv[]) {
    arg_parsing(argc, argv);

    signal (SIGINT, interrupt_handler);

    client_sockaddr_parse(server_addr, server_port, &storage);

    /*************************************************/
    /* Create a stream socket                        */
    /*************************************************/
    clientfd = socket(storage.ss_family, SOCK_STREAM, IPPROTO_TCP);
    if (clientfd < 0)
    {
      perror("socket");
      exit(-1);
    }

    /********************************************************************/
    /* Use the connect() function to establish a connection to the      */
    /* server.                                                          */
    /********************************************************************/
    struct sockaddr *addr = (struct sockaddr *)(&storage);
    if (connect(clientfd, addr, sizeof(storage)))
    {
        /*****************************************************************/
        /* Note: the res is a linked list of addresses found for server. */
        /* If the connect() fails to the first one, subsequent addresses */
        /* (if any) in the list can be tried if required.               */
        /*****************************************************************/
        printf("connect() failed");
        exit(1);
    }
    
    for (;;) {
    }

    close(clientfd); 
    close(serverfd);

    return 0;
}

void arg_parsing(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Number of Arguments passed: %d\n", argc);       
        printf("Number of arguments needed: 3\n");
        exit(1);
    }
    
    memset(server_addr, 0, sizeof(server_addr));
    sscanf(argv[1], "%s", server_addr);
    sscanf(argv[2], "%s", server_port);
}

void interrupt_handler (int signum) {
    close(serverfd);

    printf("socket connection closed\n");
    exit(0);
};