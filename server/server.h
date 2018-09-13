/********************************************************************************
 * Files         : server.h
 * Description   : 该文件为server端提供必要的头文件和定义
 ********************************************************************************/
#ifndef SERVER_H
#define SERVER_H

#include <glib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>

#define OURPORT 8088
#define MAX_USERS 10 
#define MAX_LEN 2048

int check(char * username,char *password);
void insert(char * username,char *password);

#endif