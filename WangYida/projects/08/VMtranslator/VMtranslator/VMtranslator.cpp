#include<iostream>
#include<string>
#include<fstream>
#include"VMtranslator.h"
#include "Parser.h"
#include "Codewriter.h"
#include "Symboltable.h"

using namespace std;

int spinit = 256;
int Add_NormalSymbol = 0;
int At_NormalSymbol = 0;
int VMLabelNumber = 0;
int FunctionSymbolNumber = 0;
int ReturnAddressNumber = 0; //returnaddress的数目
char instruction[100];
char row[100];
char temp[100];
char SymbolArea[500] = "Sys"; //进入新函数时修改
char FunctionName[100] = "Sys.init";
char firstword[500];
char secondword[500];
char thirdword[500];
char OutputName[30] = "out.asm";
char filename[30] = "StackTest.vm";


void Translate(){
	
	

	cin >> filename;
	getchar();
	strcpy_s(SymbolArea,filename);
	std::ifstream fin(filename);
	while(fin.getline(row,100) ){
		int L = strlen(row);
		if(L == 0 || (row[0] == '/' &&row[1] == '/') ){
			continue;
		}
		CleanLine();
		DivideWords();
		Deal();

	}
}
