#ifndef MY_CLIENT_H
#define MY_CLIENT_H

#include "common.h"

int DEBUG = 0;

// Input Variable
char server_addr[100]; // server address
char server_port[10]; // Porta Usada pelo Servidor

// Server Variables


// Client Varibles
int len, rtnVal;
int serverfd; // socket file descriptor
int clientfd;
char send_buf[80];
char recv_buf[80];
struct sockaddr_storage storage;
socklen_t client_length; /* length of client structure received on accept */

void arg_parsing(int argc, char *argv[]);
void interrupt_handler (int signum);

#endif