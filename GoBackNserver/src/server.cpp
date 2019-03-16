/*
 * server.cpp
 *
 *  Created on: Mar 9, 2019
 *      Author: Mihai
 */


// Server side C/C++ program to demonstrate Socket programming
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <string>
#include <regex>
#include <iostream>
#include <map>
#include <signal.h>
#include "other.h"
//#define PORT 8080
using namespace std;


std::map<std::string, std::string> http_request;
//std::string getexepath();
void throw_error(char *message);
void graceful_shutdown(int socket_file, int new_socket, char *message);//gracefull shutdown
bool sendToClient(int socket, const void *data, int leng);
void handler(int num);

int socket_file, new_socket, valread;

///Status
const std::string ok = "HTTP/1.1 200 OK\r\n";
const std::string bad_request = "HTTP/1.1 404 Not Found\r\n";

int main(int argc, char const *argv[])
{
    signal(SIGINT, handler);//handling the gracefull shutdown
    struct Server_Params serv;
	/*cout << "You have entered " << argc
	         << " arguments:" << "\n";

	    for (int i = 0; i < argc; ++i)
	        cout << argv[i] << "\n";
	        */
    serv.PORT = atoi(argv[1]);
    //int socket_file, new_socket, valread;
    //const char *PORT = argv[0];
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    //char* buffer = new  char[serv.BUFFER_SIZE]();
    char* buffer = new  char[1024]();
    //char* buffer[1024]={0}; // initialize all with NULL
    //buffer = {0};
    //char const *ok = "200 OK";

    // Create socket file
    socket_file = socket(AF_INET, SOCK_STREAM, 0);
    if ( socket_file== 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    cout << "Socket created..."<<endl;
    // Forcefully attaching socket to the port 8080
    if (setsockopt(socket_file, SOL_SOCKET, SO_REUSEADDR,// | SO_REUSEPORT,
                                                  &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    cout << "Port bound" << endl;

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( serv.PORT );

    // Attaching socket
    if (bind(socket_file, (struct sockaddr *)&address,sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(socket_file, 5) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    while(1){
		if ((new_socket = accept(socket_file, (struct sockaddr *)&address,
						   (socklen_t*)&addrlen))<0)
		{
			perror("accept");
			exit(EXIT_FAILURE);
		}
		valread = read( new_socket , buffer, serv.BUFFER_SIZE);
		//printf("%s\n", buffer);

		//char path[1]={0};

		//for (int i=0;buffer[i]!=NULL;i++){
		//	path[i]=buffer[i];
		//}
		//cout << "valread = " << valread<< endl;
		string path(buffer);



		//strcpy(buffer, path);
		//printf("%s\n",string(path));
		//printf("%s\n", path);

		string file_name = getFileName(path, 1); // retrieving path to file if any provide
		//cout <<"Filename to retrieve is: " << file_name << endl;
		string method_name = getFileName(path, 0); //retrieving method in request
		string exec_path = getexepath();
		//For GET
		if (string(method_name) == "GET"){
			//cout << "Get"<<endl;

			if (file_name.empty()){
				//cout << "File not found" << endl;
				//send(new_socket , bad_request.c_str() , bad_request.length() , 0 );

				//cout << exec_path;

				string content = freader(exec_path+"/index.html");
				if (content.length()<20){
					send(new_socket , bad_request.c_str() , bad_request.length() , 0 );
				}
				else{

                                        sendHeader(new_socket, content.length());
					int n= write(new_socket , content.c_str() , content.length());
					if(n<0)
						throw_error("Error while trying to write to socket!");

					send(new_socket , ok.c_str() , ok.length() , 0 );
					printf("200 OK sent\n");

				}
			}
			else{


				string content = freader(exec_path+"/"+file_name);
				if (content == "Not found" || content.length()<20){
					send(new_socket , bad_request.c_str() , bad_request.length() , 0 );
				}
				//long fsize = ftell(file_opened); //we need an opened file
				int fsize = content.length();
				cout << endl << "file size is: " <<fsize <<endl;
				if (fsize<20){
					//send(new_socket , bad_request.c_str() , bad_request.length() , 0 );
					write(new_socket , bad_request.c_str() , bad_request.length());
					cout << "404 sent to client" << endl;
				}
				else{
					send(new_socket , ok.c_str() , ok.length() , 0 );
					printf("200 OK sent\n");
					//int n =write(new_socket , content.c_str() , content.length());
					sendHeader(new_socket, fsize);
					bool n = sendToClient(new_socket , content.c_str() , fsize);
					if(n== false )
					   throw_error("Error while trying to write to socket!");
				}
			}
		}
		else if(string(method_name) == "POST"){
			cout << "POST" <<endl;
			//send(new_socket , string("POST received").c_str() , string("POST received").length() , 0 );
			string content = getFileName(path, 2);
			//cout << content << endl;
			fsaver(file_name, content);
			//send(new_socket , content.c_str() , content.length() , 0 );
			sendHeader(new_socket, content.length());

			bool n = sendToClient(new_socket , content.c_str() , content.length());

		}
		else{

		}
    }
    //gracefull shutdown
    graceful_shutdown(socket_file, new_socket, "Gracefull server shutdown....");
    //printf("%s",mystr.c_str());
    return 0;
}


void throw_error(char *message)
{
    perror(message);
    exit(0);
}


void handler(int num)
{

  //switch (num)
  //{
    //case SIGTERM:
    	cout<<"shutting down signal "<< num <<" started"<<endl;
    	graceful_shutdown(socket_file, new_socket, "Gracefull server shutdown....");
    	exit(num);

      //break;
  //}
}

void graceful_shutdown(int socket_file, int new_socket, char *message){
    shutdown(new_socket, 0); //no more connection accepted
    close(new_socket);
    close(socket_file);
    cout<<endl<<endl;
    cout << message << endl;
}

//this method delivers the header
void sendHeader(int socket, int leng){
	 write(socket, "HTTP/1.1 200 OK\r\n", string("HTTP/1.1 200 OK\r\n").length());
	 char clen[40];
	 sprintf(clen, "Content-length: %ld\r\n", leng);
	 write(socket, clen, strlen(clen));
	 write(socket, "Content-Type: text/html\r\n", string("Content-Type: text/html\r\n").length());
	 write(socket, "Connection: close\r\n\r\n", string("Connection: close\r\n\r\n").length());
}

//this method responds to GET by delivering the file requested
bool sendToClient(int socket, const void *data, int leng){
	 const char *sent_data = (const char*) data;
	 while (leng > 0){
	   int num = send(socket, sent_data, leng, 0);
	  if(num<=0)
	     return false;
	  sent_data += num;
	  leng -= num;
	}

	return true;
}

//this method responds to POST
bool receiveFromClient(){

}
