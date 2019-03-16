/*
 * client.cpp
 *
 *  Created on: Mar 9, 2019
 *      Author: Mihai
 */




// Client side C/C++ program to demonstrate Socket programming
//https://www.geeksforgeeks.org/socket-programming-cc/
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
//#define PORT 8080
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <errno.h>
#include <netdb.h>
#include <string>
#include <string.h>
#include <cstring>
#include "other.h"
#include <sstream>
#include <iostream>
using namespace std;

void print_ip(struct hostent);
std::string getexepath();
bool PostForm(int sock, FileContent *myFile);
string receive_data(int sock, char *buffer);

int main(int argc, char const *argv[])
{
    struct Server_Params serv;
    serv.PORT = atoi(argv[2]);

    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    //char const *name = argv[1];//"http://localhost";
    serv.name = argv[1];
    //char const *somepath = (string("/")+argv[4]).c_str();//"/index.html";
    serv.somepath= (string("/")+argv[4]).c_str();//"/index.html";
cout<<"client serv.somepath: " <<serv.somepath <<endl;    
//char const *command = argv[3];
    serv.command = argv[3];

    //cout <<"Connecting to server port: " << serv.PORT<<endl;
    //cout <<name<<endl;
    //cout <<somepath<<endl;
    //cout <<command<<endl;
    string get_http = "GET / HTTP/1.1\r\nHost: " + string(serv.name)+string(serv.somepath) + "\r\nConnection: close\r\n\r\n";//for Get HTTP
    string post_http = "POST / HTTP/1.1\r\nHost: " + string(serv.name) + "\r\nConnection: close\r\n\r\n";//for Get HTTP
    char buffer[1024] = {0};
    //char* buffer = new  char[serv.BUFFER_SIZE]();
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }
    struct hostent *host;

    host = gethostbyname(serv.name);
    char ip[100];
    struct in_addr **address_list;
    address_list = (struct in_addr **) host->h_addr_list;
    for (int i=0; address_list[i]!=NULL;i++)
    {
    	strcpy(ip, inet_ntoa(*address_list[i]));
    }
    strcpy(ip, "127.0.0.1");
    printf("%s resolved to %s\n\n", serv.name, ip);
    //print_ip(*host);
    //-----------------



    //-----------------
    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(serv.PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, ip, &serv_addr.sin_addr)<=0)//"127.0.0.1"
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    // send GET / HTTP
    if (string(serv.command)=="GET"){
    	send(sock, get_http.c_str(), strlen(get_http.c_str()),0 );
	string the_html = receive_data(sock, buffer);
	cout<<"client GET buffer is: " << buffer <<  endl;	
	cout << "Client Received HTML after GET on server: "<<endl<< the_html <<endl;
    }else if (string(serv.command)=="POST"){
    	//send POST
		string exec_path = getexepath();//retrieve current directory path
		string file_name = serv.somepath;//"about.html";//file to
		string content = freader(exec_path+"/" + file_name);
		//cout<<"content is: " << content << endl << " path "<<exec_path+"/"+file_name << endl;
		if (content.length()<20){
			perror("file not find. Please check the file name.\n");
			//perror(content);
			exit(EXIT_FAILURE);
		}
		else{
			FileContent* f = new FileContent(file_name, content);
			PostForm(sock, f);
			//recv(sock,buffer,10000,0);
			//cout<<buffer<<endl;
			string the_html = receive_data(sock, buffer);
			cout << "Client Received HTML after POST on server: "<<endl<< the_html <<endl;
		}
    }else{}



    return 0;
}

string receive_data(int sock, char *buffer){
    // recieve html
    string the_html;
    int dataLenght;
    while ((dataLenght = recv(sock,buffer,10000,0)) > 0){
       int i = 0;
       while (buffer[i] >= 32 || buffer[i] == '\n' || buffer[i] == '\r'){
    	   the_html+=buffer[i];
               i += 1;
            }
    }
    //cout << the_html;
    //send(sock , hello , strlen(hello) , 0 );
    //printf("Hello message sent\n");
    int valread = read( sock , buffer, 1024);
    //printf("%s\n",buffer );
    //closesocket(sock);
    return the_html;
}

bool PostForm(int sock, FileContent *myFile)
{
    //declare a buffer of variable size
	ostringstream FormBuffer;
	char Name[] = "name=";
    char Content[] = "content=";

    //char FormAction[] = "/g/g.php";

    // get: length of the actual content
    auto ContentLength = string(myFile->getContent()).length();

    // header
    //FormBuffer << "POST " << FormAction << " HTTP/1.1\n";
    FormBuffer << "POST " << " HTTP/1.1\n";
    FormBuffer << "Content-Type: application/x-www-form-urlencoded\n";
    FormBuffer << "Host: \n";
    FormBuffer << "Content-Length: " << std::to_string(ContentLength) << "\n\n";

    //name
    FormBuffer << Name << myFile->name;
    // content
    FormBuffer << Content << myFile->content;

    const auto str = FormBuffer.str();
    //printf("Current Form to PUT %s\n", str.c_str());

    return ( send(sock, str.data(), str.size(), NULL) >= str.size() );
}

void print_ip(struct hostent ip)
{
    printf("%s",ip.h_name);
    printf("%s",ip.h_aliases);
    printf("%s",ip.h_addrtype);
    printf("%s",ip.h_length);
    printf("%s",ip.h_addr_list);
	//	printf("%d.%d.%d.%d\n", bytes[3], bytes[2], bytes[1], bytes[0]);
}
