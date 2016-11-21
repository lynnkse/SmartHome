#include "../inc/Parser_t.h"
#include <cstring>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>

Parser_t::Parser_t():m_currLineNum(0), m_fs(0){}

Parser_t::~Parser_t()
{
	if(m_fs) delete m_fs; //because last m_fs is not deleted in ProcessFile()
}

string Parser_t::GetNextLine() 
{
	if(m_fs->eof()) throw("EOF reached");
	else if(m_fs->fail()) throw("fail opening file");
	else if(m_fs->bad()) throw("bad file");
	
	string line;
	getline(*m_fs, line);
	++m_currLineNum;	
	return line;
}

void Parser_t::ProcessFile(const string& _fileName)
{
	if(m_fs) delete m_fs;
	
	m_fs = new ifstream(_fileName.c_str());
	m_currLineNum = 0;
	m_fileName = _fileName;
}







































