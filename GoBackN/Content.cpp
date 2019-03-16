/*
 * Content.cpp
 *
 *  Created on: Mar 10, 2019
 *      Author: Mihai
 */
#include <iostream>
#include <iomanip>
#include <string>
#include "other.h"
using namespace std;


FileContent::FileContent(string name, string content)
{
	this->name = name;
	this->content = content;
}

void FileContent::setFile(char *name, char *content)
{
	name = new char[strlen(name)+1];
	strcpy(name, name);
	content = new char[strlen(content)+1];
	strcpy(content, content);
	}

FileContent::~FileContent(){

}

void FileContent::showFile(){
	printf("File name is %s\n", this->name.c_str());
	printf("File content is %s\n", this->content.c_str());

}

string FileContent::getContent(){
	return content;
}

string FileContent::getName(){
	return name;
}
