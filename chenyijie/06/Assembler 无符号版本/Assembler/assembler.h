#pragma once
#ifndef ASSEMBLER_H
#define ASSEMBLER_H
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
private:
	int bin[16];
	char instruction[100];
};





#endif