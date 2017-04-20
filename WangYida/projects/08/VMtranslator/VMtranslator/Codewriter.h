#pragma once
#ifndef CODEWRITER_H
#define CODEWRITER_H


void Init();		//OK
void Out(char *s);	//OK
void Deal();		//OK
void DealWithArithmetic();//OK
void DealWithMemory();//OK
void DealWithProgramFlow();//OK
void DealWithFunction();
void DealWithCallFunction();
void DealWithReturn();
void AddVMLabel(int n);//OK
void GotoVMLabel(char* s);//OK
void If_GotoLabel(char* s);//OK
void AtNormalSymbol(int i);//OK
void AddNormalSymbol(int i);//OK






#endif