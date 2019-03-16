/*
 * other.h
 *
 *  Created on: Mar 9, 2019
 *      Author: Mihai
 */

#ifndef OTHER_H_
#define OTHER_H_
#include <string>
#include <string.h>

using namespace std;

string freader(string f);
string getFileName(string path);
void fsaver(string name, string f);
std::string getexepath();


struct Server_Params {
  const char *name;// = "http://localhost";
  int PORT;
  int const BUFFER_SIZE = 1024;
  const char *command;//="GET";
  const char *somepath;// = "index.html";
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
