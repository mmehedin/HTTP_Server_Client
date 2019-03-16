/*
 * freader.cpp
 *
 *  Created on: Mar 9, 2019
 *      Author: Mihai
 */

//export string fread(string f)
#include "other.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#define F "example.txt"
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#include <arpa/inet.h>
#include <unistd.h>
using namespace std;


string freader(string f) {
  //ofstream myfile;
  ifstream myfile;
  string line;
  string content;
  cout <<"freader path is: "<< f <<endl;
  myfile.open (f);//("example.txt");
  //myfile << "Writing this to a file.\n";
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
      //cout << line << '\n';
      content.append(line);
    }
    myfile.close();
    //cout << "freader Read file " << f;
    cout << "freader Content is: " << content;
    return content;
  }
  else cout << "Unable to open file";

  return "Not found";

}


string getexepath()
  {
	string s_cwd(getcwd(NULL,0));
	return s_cwd;
  }

void fsaver(string name, string f) {
	string exec_path = getexepath();
	std::ofstream out(exec_path+"/"+name);
	out << f;
	out.close();
	//cout << "saved " << exec_path+"/"+name <<endl;

}


