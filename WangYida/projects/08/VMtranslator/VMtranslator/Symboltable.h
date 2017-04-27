#pragma once
#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

typedef struct{
	int LabelNumber;
	char LabelName[50];
}VMLabel;

typedef struct{
	char FunctionName[50];
	int StartAddress;
}FunctionSymbol;

extern VMLabel Label[500];
extern FunctionSymbol Function[100];





#endif