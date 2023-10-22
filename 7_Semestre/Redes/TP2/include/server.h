#ifndef MY_SERVER_H
#define MY_SERVER_H

#include "common.h"

int DEBUG = 0;

// Input Variable
int IP_version; // 0 -> IPv4, 1 -> IPv6 
int SERVER_PORT; // Porta Usada pelo Servidor

// Client Varibles
int clientfd;
socklen_t client_length; /* length of client structure received on accept */

// Server Varibles
int serverfd; // socket file descriptor
struct sockaddr_storage storage;
char send_buf[80];
char recv_buf[80];

void arg_parsing(int argc, char *argv[]);
void load_input(char *filename);
int close_conection();

// Signal Handler
void interrupt_handler (int signum);

#endif
