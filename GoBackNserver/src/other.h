/*
 * other.h
 *
 *  Created on: Mar 9, 2019
 *      Author: Mihai
 */

#ifndef OTHER_H_
#define OTHER_H_
#include <string>
using namespace std;

string freader(string f);
string getFileName(string path, int ret);
void fsaver(string name, string f);
std::string getexepath();
void sendHeader(int socket, int leng);
int launchConnection(int number_clients);
void * getThreadConnection(void * tid);

struct Server_Params {
  string const HOST_NAME = "http://localhost";
  int PORT;
  int const BUFFER_SIZE = 1024;
};


class FileContent
{
	private:
		int length;
	public:
		string content;
		string name;
		FileContent(string name, string content);
		string getContent();
		string getName();
		void setFile(char *name, char *content);
		~FileContent();//destructor
		void showFile();
	};

#endif /* OTHER_H_ */
