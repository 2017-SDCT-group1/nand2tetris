#pragma once
#ifndef ASSEMBLER_H
#define ASSEMBLER_H

typedef struct
{
	char name[50];
	int number;
	bool validity;
}DataSymbol;

typedef struct
{
	char name[50];
	int number;
}InstructionSymbol;


extern char instruction[100];
extern char row[100];
extern char temp_symbol[50];
extern DataSymbol datasymbols[1000];
extern InstructionSymbol instructionsymbols[1000];

extern int linenumber;
extern int instructionsymbols_number;
extern int datasymbols_number;
extern int scan_time;
extern int value;
extern int out[16];
extern int Ponggame;

//以下为函数Orz
void DealAsLine();	//OK
void CleanLine();	//OK
void Translate();	//OK
void Out();			//OK
void DealWithA();	//OK
void DealWithANormal();	//OK	
void DealWithCE();	//OK
void Comp(char a[7]);	//OK
void DealWithASymbol();	//OK
void DealWithCJ();	//OK
void DealWithSy();	//OK
void AddInstructionSymbol(char* s);	//OK
void AddDataSymbol(char* s);	//OK
void Delete();	//OK

bool IsInstructionSymbol(char* s); //OK
bool IsDataSymbol(char* s);	//OK

int CommandType();	//OK
int GetDataAddress(char* s);	//OK
int GetInstructionAddress(char* s);	//OK

#endif