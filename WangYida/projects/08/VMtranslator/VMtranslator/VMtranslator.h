#pragma once
#ifndef VMTRANSLATOR_H
#define VMTRANSLATOR_H

//以下为宏定义
#define ADD_  101;
#define SUB_  102;
#define NEG_  103;
#define AND_  104;
#define NOT_  105;
#define EQ_  106;
#define GT_  107;
#define LT_  108;
#define OR_  109;
#define PUSH_  110;
#define POP_  111;
#define AddLabel_  112;
#define GotoLabel_  113;
#define if_GotoLabel_  114;
#define Function_  115;
#define CallFunction_  116;
#define Return_  117;
//to do

//以下为变量定义,分开到各个头文件太麻烦了，就放在一起了 Orz
extern int spinit;
extern int Add_NormalSymbol;// = 0;
extern int At_NormalSymbol;// = 0;
extern int VMLabelNumber;// = 0;
extern int FunctionSymbolNumber;// = 0;
extern int ReturnAddressNumber;// = 0；//returnaddress的数目
extern char instruction[100];
extern char row[100];
extern char temp[100];
extern char SymbolArea[500];// 初始："Sys"; //进入新函数时修改
extern char FunctionName[100];
extern char firstword[500];
extern char secondword[500];
extern char thirdword[500];
extern char OutputName[30];
extern char filename[30];

//以下为函数定义
void Translate();	//OK



#endif