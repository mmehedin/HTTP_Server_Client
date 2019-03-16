/*
 * multithread.cpp
 *
 *  Created on: Mar 13, 2019
 *      Author: Mihai
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <pthread.h>
#include "other.h"
using namespace std;
void *getThreadConnection(void *tid);//, string host_name, string, int *PORT);

int launchConnection(int number_clients){
	int socket_desc , new_socket , c , *new_sock, i;
	pthread_t sniffer_thread;
	//int *sniff = &sniffer_thread;
	for (i=1; i<=number_clients; i++) {
		int n = pthread_create(&sniffer_thread , NULL,  getThreadConnection , (void *)i);
		if(  n< 0)
		{
			perror("Error: thread not created");
			return 1;
		}
		sleep(3);
	}
	pthread_exit(NULL);
	return 0;
}


void * getThreadConnection(void * tid)//, string host_name, string, int *PORT)
{
    int tnumb = (uintptr_t)tid;
    int sock_desc;
    struct sockaddr_in serv_addr;
    char sbuff[1024],rbuff[1024];

    if((sock_desc = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        printf("Socket genesis failed \n");

    bzero((char *) &serv_addr, sizeof (serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("http://localhost");
    serv_addr.sin_port = htons(8888);

    if (connect(sock_desc, (struct sockaddr *) &serv_addr, sizeof (serv_addr)) < 0) {
        printf("Failed to connect to server\n");
    }

    printf("Thread number connected:%d\n", tnumb);
    while(1)
    {
        printf("For thread : %d\n", tnumb);
        fgets(sbuff, 1024 , stdin);
        send(sock_desc,sbuff,strlen(sbuff),0);

        if(recv(sock_desc,rbuff,1024,0)==0)
            printf("Error");
        else
           fputs(rbuff,stdout);

        bzero(rbuff,1024);
        sleep(2);
    }
    close(sock_desc);
    return 0;
}
