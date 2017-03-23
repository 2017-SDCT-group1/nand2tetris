#pragma once
#ifndef ASSEMBLER_H
#define ASSEMBLER_H
struct Symbol
{
	char  name[20];
	int value;
};
class Assembler
{
public:
	Assembler() {};
	~Assembler() {};
	void Getline();
	void Translate();
	void Output();
	void SetC(char x[6]);
	void Setjump(char x[3]);
	bool NewSymbol(char* c);
	void AddSymbol(char* c);
	int Get_SymbolValue(char* c);
	void First_SCAN();
	bool NewLabelSymbol(char *c);
	void AddLabelSymbol(char* c);
	int Get_LabelSymbolValue(char *c);
	void Debug();
	bool InSymbol(char *);
	bool InLabelSymbol(char *);
private:
	int bin[16];
	char instruction[100];
	Symbol symbol[1000];
	Symbol label[1000];
	int symbol_number = 0;
	int labelsymbol_number = 0;
	int line = 0;
};


#endif