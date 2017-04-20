#include<iostream>
#include<string>
#include<fstream>
#include"VMtranslator.h"
#include "Parser.h"
#include "Codewriter.h"
#include "Symboltable.h"

using namespace std;

void Init(){
	std::ofstream fout(OutputName, std::ios::app);

	fout << "@" << spinit <<std::endl;
	Out("D=A");
	Out("@SP");
	Out("M=D");
	fout << "@Sys.init" << std::endl << "0;JMP" << std::endl; 
}

void Out(char *s){
	std::ofstream fout(OutputName, std::ios::app);
	fout << s;
	fout << std::endl;
}

void Deal(){
	//cout << OutputName << std::endl << filename;
	if (CommandType() >= 101 && CommandType() <= 109)
		DealWithArithmetic();
	if(CommandType() == 110 || CommandType() == 111)
		DealWithMemory();
	if (CommandType() >= 112 && CommandType() <= 114)
		DealWithProgramFlow();
	if (CommandType() == 115)
		DealWithFunction();
	if (CommandType() == 116)
		DealWithCallFunction();
	if (CommandType() == 117)
		DealWithReturn();
	//to do

}

void DealWithArithmetic(){
	switch(CommandType() ){
	case 101 : {		//ADD_
		Out("@SP");
		Out("M=M-1");
		Out("@SP");
		Out("A=M");
		Out("D=M");
		Out("@SP");
		Out("M=M-1");
		Out("@SP");
		Out("A=M");
		Out("A=M");
		Out("D=D+A");
		Out("@SP");
		Out("A=M");
		Out("M=D");
		Out("@SP");
		Out("M=M+1");
		break;
			   }
	case 102 : {		//SUB_
		Out("@SP");
		Out("M=M-1");
		Out("@SP");
		Out("A=M");
		Out("D=M");
		Out("@SP");
		Out("M=M-1");
		Out("@SP");
		Out("A=M");
		Out("A=M");
		Out("D=D-A");
		Out("D=-D");
		Out("@SP");
		Out("A=M");
		Out("M=D");
		Out("@SP");
		Out("M=M+1");
		break;
			   }
	case 103 : {			//NEG_
		Out("@SP");
		Out("M=M-1");
		Out("@SP");
		Out("A=M");
		Out("M=-M");
		Out("@SP");
		Out("M=M+1");
		break;
			   }
	case 104 : {			//AND
		Out("@SP");
		Out("M=M-1");
		Out("@SP");
		Out("A=M");
		Out("D=M");
		Out("@SP");
		Out("M=M-1");
		Out("@SP");
		Out("A=M");
		Out("A=M");
		Out("D=D&A");
		Out("@SP");
		Out("A=M");
		Out("M=D");
		Out("@SP");
		Out("M=M+1");
		break;
			   }
	case 105 : {			//NOT_
		Out("@SP");
		Out("M=M-1");
		Out("@SP");
		Out("A=M");
		Out("M=!M");
		Out("@SP");
		Out("M=M+1");
		break;
			   }
	case 106 : {			//EQ_
		Out("@SP");
		Out("M=M-1");
		Out("@SP");
		Out("A=M");
		Out("D=M");
		Out("@SP");
		Out("M=M-1");
		Out("@SP");
		Out("A=M");
		Out("A=M");
		Out("D=D-A");
		AtNormalSymbol(At_NormalSymbol);
		Out("D;JEQ");
		Out("@SP");
		Out("A=M");
		Out("M=0");
		Out("@SP");
		Out("M=M+1");
		AtNormalSymbol(At_NormalSymbol);
		Out("0;JMP");
		AddNormalSymbol(Add_NormalSymbol);
		Out("@SP");
		Out("A=M");
		Out("M=-1");
		Out("@SP");
		Out("M=M+1");
		AddNormalSymbol(Add_NormalSymbol);
		break;
			   }
	case 107 : {			//GT_
		Out("@SP");
		Out("M=M-1");
		Out("@SP");
		Out("A=M");
		Out("D=M");
		Out("@SP");
		Out("M=M-1");
		Out("@SP");
		Out("A=M");
		Out("A=M");
		Out("D=D-A");
		Out("D=-D");
		AtNormalSymbol(At_NormalSymbol);
		Out("D;JGT");
		Out("@SP");
		Out("A=M");
		Out("M=0");
		Out("@SP");
		Out("M=M+1");
		AtNormalSymbol(At_NormalSymbol);
		Out("0;JMP");
		AddNormalSymbol(Add_NormalSymbol);
		Out("@SP");
		Out("A=M");
		Out("M=-1");
		Out("@SP");
		Out("M=M+1");
	    AddNormalSymbol(Add_NormalSymbol);
		break;
			   }
	case 108 : {			//LT_
		Out("@SP");
		Out("M=M-1");
		Out("@SP");
		Out("A=M");
		Out("D=M");
		Out("@SP");
		Out("M=M-1");
		Out("@SP");
		Out("A=M");
		Out("A=M");
		Out("D=D-A");
		Out("D=-D");
		AtNormalSymbol(At_NormalSymbol);
		Out("D;JLT");
		Out("@SP");
		Out("A=M");
		Out("M=0");
		Out("@SP");
		Out("M=M+1");
		AtNormalSymbol(At_NormalSymbol);
		Out("0;JMP");
		AddNormalSymbol(Add_NormalSymbol);
		Out("@SP");
		Out("A=M");
		Out("M=-1");
		Out("@SP");
		Out("M=M+1");
		AddNormalSymbol(Add_NormalSymbol);
		break;
			   }
	case 109 : {			//OR_
		Out("@SP");
		Out("M=M-1");
		Out("@SP");
		Out("A=M");
		Out("D=M");
		Out("@SP");
		Out("M=M-1");
		Out("@SP");
		Out("A=M");
		Out("A=M");
		Out("D=D|A");
		Out("@SP");
		Out("A=M");
		Out("M=D");
		Out("@SP");
		Out("M=M+1");
		break;
			   }
	default :
		break;
	}
}

void DealWithMemory(){
	if(CommandType() == 110){		//PUSH_
		
		if(strcmp(secondword, "constant") == 0){				//constant
			std::ofstream fout(OutputName, std::ios::app);
			fout << "@" << thirdword << std::endl;
			Out("D=A");
			Out("@SP");
			Out("A=M");
			Out("M=D");
			Out("@SP");
			Out("M=M+1");
		}

		//if(instruction[4] == 'a' && instruction[5] == 'r' && instruction[6] == 'g'){	//argument
		if(strcmp(secondword, "argument") == 0){
			//for(int i = 0; i < (strlen(instruction) - 12); i++)
			//	temp[i] = instruction[i + 12];
			//temp[strlen(instruction) - 12] = '\0';
			std::ofstream fout(OutputName, std::ios::app);
			fout << "@" << thirdword << std::endl;
			Out("D=A");
			Out("@ARG");
			Out("A=M");
			Out("A=D+A");
			Out("D=M");
			Out("@SP");
			Out("A=M");
			Out("M=D");
			Out("@SP");
			Out("M=M+1");
		}
		
		//if(instruction[4] == 't' && instruction[5] == 'h' && instruction[6] == 'i'){	//this
		if(strcmp(secondword, "this") == 0){
			//for(int i = 0; i < (strlen(instruction) - 8); i++)
			//	temp[i] = instruction[i + 8];
			//temp[strlen(instruction) - 8] = '\0';
			std::ofstream fout(OutputName, std::ios::app);
			fout << "@" << thirdword << std::endl;
			Out("D=A");
			Out("@THIS");
			Out("A=M");
			Out("A=D+A");
			Out("D=M");
			Out("@SP");
			Out("A=M");
			Out("M=D");
			Out("@SP");
			Out("M=M+1");
		}

		//if(instruction[4] == 't' && instruction[5] == 'h' && instruction[6] == 'a'){	//that
		if(strcmp(secondword, "that") == 0){
			//for(int i = 0; i < (strlen(instruction) - 8); i++)
		//		temp[i] = instruction[i + 8];
			//temp[strlen(instruction) - 8] = '\0';
			std::ofstream fout(OutputName, std::ios::app);
			fout << "@" << thirdword << std::endl;
			Out("D=A");
			Out("@THAT");
			Out("A=M");
			Out("A=D+A");
			Out("D=M");
			Out("@SP");
			Out("A=M");
			Out("M=D");
			Out("@SP");
			Out("M=M+1");
		}

		//if(instruction[4] == 'l' && instruction[5] == 'o' && instruction[6] == 'c'){	//local
		if(strcmp(secondword, "local") == 0){
			//for(int i = 0; i < (strlen(instruction) - 9); i++)
			//	temp[i] = instruction[i + 9];
			//temp[strlen(instruction) - 9] = '\0';
			std::ofstream fout(OutputName, std::ios::app);
			fout << "@" << thirdword << std::endl;
			Out("D=A");
			Out("@LCL");
			Out("A=M");
			Out("A=D+A");
			Out("D=M");
			Out("@SP");
			Out("A=M");
			Out("M=D");
			Out("@SP");
			Out("M=M+1");
		}

		
		//if(instruction[4] == 't' && instruction[5] == 'e' && instruction[6] == 'm'){	//temp
		if(strcmp(secondword, "temp") == 0){
			//for(int i = 0; i < (strlen(instruction) - 8); i++)
			//	temp[i] = instruction[i + 8];
			//temp[strlen(instruction) - 8] = '\0';
			std::ofstream fout(OutputName, std::ios::app);
			fout << "@" << thirdword << std::endl;
			Out("D=A");
			Out("@5");
			Out("A=D+A");
			Out("D=M");
			Out("@SP");
			Out("A=M");
			Out("M=D");
			Out("@SP");
			Out("M=M+1");
		}

		//if(instruction[4] == 's' && instruction[5] == 't' && instruction[6] == 'a'){	//static
		if(strcmp(secondword, "static") == 0){
			//for(int i = 0; i < (strlen(instruction) - 10); i++)
			//	temp[i] = instruction[i + 10];
			//temp[strlen(instruction) - 10] = '\0';
			std::ofstream fout(OutputName, std::ios::app);
			fout << "@" << filename << "." << thirdword << std::endl;
			Out("D=M");
			Out("@SP");
			Out("A=M");
			Out("M=D");
			Out("@SP");
			Out("M=M+1");
		}

		//if(instruction[4] == 'p' && instruction[5] == 'o' && instruction[6] == 'i'){	//pointer
		if(strcmp(secondword, "pointer") == 0){
			//for(int i = 0; i < (strlen(instruction) - 11); i++)
			//	temp[i] = instruction[i + 11];
			//temp[strlen(instruction) - 11] = '\0';

			std::ofstream fout(OutputName, std::ios::app);
			fout << "@" << thirdword <<std::endl;
			Out("D=A");
			Out("@3");
			Out("D=D+A");
			Out("A=D");
			Out("D=M");
			Out("@SP");
			Out("A=M");
			Out("M=D");
			Out("@SP");
			Out("M=M+1");
		}


	}
	if(CommandType() == 111){		//POP_

		//if(instruction[3] == 'a' && instruction[4] == 'r' && instruction[5] == 'g'){	//argument
			//for(int i = 0; i < (strlen(instruction) - 11); i++)
			//	temp[i] = instruction[i + 11];
			//temp[strlen(instruction) - 11] = '\0';
		if(strcmp(secondword, "argument") == 0){
			std::ofstream fout(OutputName, std::ios::app);
			fout << "@" << thirdword << std::endl;
			Out("D=A");
			Out("@ARG");
			Out("A=M");
			Out("D=D+A");
			Out("@R14");
			Out("M=D");
			Out("@SP");
			Out("M=M-1");
			Out("A=M");
			Out("D=M");
			Out("@R13");
			Out("M=D");
			Out("@R14");
			Out("A=M");
			Out("M=D");
		}

		//if(instruction[3] == 't' && instruction[4] == 'h' && instruction[5] == 'i'){	//this
			//for(int i = 0; i < (strlen(instruction) - 7); i++)
			//	temp[i] = instruction[i + 7];
			//temp[strlen(instruction) - 7] = '\0';
		if(strcmp(secondword, "this") == 0){
			std::ofstream fout(OutputName, std::ios::app);
			fout << "@" << thirdword << std::endl;
			Out("D=A");
			Out("@THIS");
			Out("A=M");
			Out("D=D+A");
			Out("@R14");
			Out("M=D");
			Out("@SP");
			Out("M=M-1");
			Out("A=M");
			Out("D=M");
			Out("@R13");
			Out("M=D");
			Out("@R14");
			Out("A=M");
			Out("M=D");
		}

		//if(instruction[3] == 't' && instruction[4] == 'h' && instruction[5] == 'a'){	//that
		//	for(int i = 0; i < (strlen(instruction) - 7); i++)
		//		temp[i] = instruction[i + 7];
		//	temp[strlen(instruction) - 7] = '\0';
		if(strcmp(secondword, "that") == 0){
			std::ofstream fout(OutputName, std::ios::app);
			fout << "@" << thirdword << std::endl;
			Out("D=A");
			Out("@THAT");
			Out("A=M");
			Out("D=D+A");
			Out("@R14");
			Out("M=D");
			Out("@SP");
			Out("M=M-1");
			Out("A=M");
			Out("D=M");
			Out("@R13");
			Out("M=D");
			Out("@R14");
			Out("A=M");
			Out("M=D");
		}

		//if(instruction[3] == 'l' && instruction[4] == 'o' && instruction[5] == 'c'){	//local
		//	for(int i = 0; i < (strlen(instruction) - 8); i++)
		//		temp[i] = instruction[i + 8];
		//	temp[strlen(instruction) - 8] = '\0';
		if(strcmp(secondword, "local") == 0){
			std::ofstream fout(OutputName, std::ios::app);
			fout << "@" << thirdword << std::endl;
			Out("D=A");
			Out("@LCL");
			Out("A=M");
			Out("D=D+A");
			Out("@R14");
			Out("M=D");
			Out("@SP");
			Out("M=M-1");
			Out("A=M");
			Out("D=M");
			Out("@R13");
			Out("M=D");
			Out("@R14");
			Out("A=M");
			Out("M=D");
		}

		
		//if(instruction[3] == 't' && instruction[4] == 'e' && instruction[5] == 'm'){	//temp
		//	for(int i = 0; i < (strlen(instruction) - 7); i++)
		//		temp[i] = instruction[i + 7];
		//	temp[strlen(instruction) - 7] = '\0';
		if(strcmp(secondword, "temp") == 0){
			std::ofstream fout(OutputName, std::ios::app);
			fout << "@" << thirdword << std::endl;
			Out("D=A");
			Out("@5");
			Out("D=D+A");
			Out("@R13");
			Out("M=D");
			Out("@SP");
			Out("M=M-1");
			Out("A=M");
			Out("D=M");
			Out("@R13");
			Out("A=M");
			Out("M=D");
		}

	//	if(instruction[3] == 's' && instruction[4] == 't' && instruction[5] == 'a'){	//static
		//	for(int i = 0; i < (strlen(instruction) - 9); i++)
		//		temp[i] = instruction[i + 9];
		//	temp[strlen(instruction) - 9] = '\0';
		if(strcmp(secondword, "static") == 0){
			std::ofstream fout(OutputName, std::ios::app);
			fout << "@" << filename << "." << thirdword << std::endl;
			Out("D=A");
			Out("@R13");
			Out("M=D");
			Out("@SP");
			Out("M=M-1");
			Out("A=M");
			Out("D=M");
			Out("@R13");
			Out("A=M");
			Out("M=D");
		}

	//	if(instruction[3] == 'p' && instruction[4] == 'o' && instruction[5] == 'i'){	//pointer
	//		for(int i = 0; i < (strlen(instruction) - 10); i++)
		//		temp[i] = instruction[i + 10];
		//	temp[strlen(instruction) - 10] = '\0';
		if(strcmp(secondword, "pointer") == 0){
			std::ofstream fout(OutputName, std::ios::app);
			fout << "@" << thirdword <<std::endl;
			Out("D=A");
			Out("@3");
			Out("D=D+A");
			Out("@R13");
			Out("M=D");
			Out("@SP");
			Out("M=M-1");
			Out("A=M");
			Out("D=M");
			Out("@R13");
			Out("A=M");
			Out("M=D");

		}

	}

}

void DealWithProgramFlow(){
	switch (CommandType())
	{
	case 112 : {
		AddVMLabel(VMLabelNumber);
		break;
			   }
	case 113 : {
		
		GotoVMLabel(secondword);
		break;
			   }
	case 114 : {
		If_GotoLabel(secondword);
		break;
			   }
	default:
		break;
	}
}

void DealWithFunction(){		//设定开始地址

	strcpy_s(FunctionName, secondword);

	std::ofstream fout(OutputName, std::ios::app);

	fout << "(" << secondword << ")" << std::endl;

	int n = atoi(thirdword);
	for(int i = 0; i < n; i++){
		Out("@0");
		Out("D=A");
		Out("@SP");
		Out("A=M");
		Out("M=D");
		Out("@SP");
		Out("M=M+1");
	}

}

void DealWithCallFunction(){


	std::ofstream fout(OutputName, std::ios::app);
	
	fout << "@" << "return." << ReturnAddressNumber << std::endl;
	Out("D=A");
	Out("@SP");
	Out("A=M");
	Out("M=D");
	Out("@SP");
	Out("M=M+1");

	Out("@LCL");
	Out("D=M");
	Out("@SP");
	Out("A=M");
	Out("M=D");
	Out("@SP");
	Out("M=M+1");

	Out("@ARG");
	Out("D=M");
	Out("@SP");
	Out("A=M");
	Out("M=D");
	Out("@SP");
	Out("M=M+1");

	Out("@THIS");
	Out("D=M");
	Out("@SP");
	Out("A=M");
	Out("M=D");
	Out("@SP");
	Out("M=M+1");

	Out("@THAT");
	Out("D=M");
	Out("@SP");
	Out("A=M");
	Out("M=D");
	Out("@SP");
	Out("M=M+1");

	Out("@SP");
	Out("D=M");
	Out("@5");
	Out("D=D-A");
	int n = atoi(thirdword);
	fout << "@" << n <<std::endl;
	Out("D=D-A");
	Out("@ARG");
	Out("M=D");
	

	Out("@SP");
	Out("D=M");
	Out("@LCL");
	Out("M=D");

	fout << "@" << secondword << std::endl;
	Out("0;JMP");

	fout << "(" << "return." << ReturnAddressNumber << ")" << std::endl;
	ReturnAddressNumber++;
}

void DealWithReturn(){

	Out("@LCL");
	Out("D=M");
	Out("@FRAME");
	Out("M=D");

	Out("@5");
	Out("A=D-A");
	Out("D=M");
	Out("@RET");
	Out("M=D");

	Out("@SP");
	Out("M=M-1");
	Out("A=M");
	Out("D=M");
	Out("@ARG");
	Out("A=M");
	Out("M=D");
	



	Out("@ARG");
	Out("D=M");
	Out("@SP");
	Out("M=D+1");

	Out("@FRAME");
	Out("D=M");
	Out("D=D-1");
	Out("@FRAME");
	Out("M=D");
	Out("A=D");
	Out("D=M");
	Out("@THAT");
	Out("M=D");

	Out("@FRAME");
	Out("D=M");
	Out("D=D-1");
	Out("@FRAME");
	Out("M=D");
	Out("A=D");
	Out("D=M");
	Out("@THIS");
	Out("M=D");

	Out("@FRAME");
	Out("D=M");
	Out("D=D-1");
	Out("@FRAME");
	Out("M=D");
	Out("A=D");
	Out("D=M");
	Out("@ARG");
	Out("M=D");

	Out("@FRAME");
	Out("D=M");
	Out("D=D-1");
	Out("@FRAME");
	Out("M=D");
	Out("A=D");
	Out("D=M");
	Out("@LCL");
	Out("M=D");

	Out("@RET");
	Out("A=M");
	Out("0;JMP");
	
	
}



void AtNormalSymbol(int i){
	std::ofstream fout(OutputName,std::ios::app);
	fout << "@" << SymbolArea << ".";
	fout << i;
	fout << std::endl;
	At_NormalSymbol++;
}

void AddNormalSymbol(int i){
	std::ofstream fout(OutputName,std::ios::app);
	fout << "(" << SymbolArea << "."; 
	fout << i;
	fout << ")";
	fout << std::endl;
	Add_NormalSymbol++;
}

void AddVMLabel(int n){
	
	std::ofstream fout(OutputName, std::ios::app);
	fout << "(" << FunctionName << "$" << secondword << ")" << std::endl;
	Label[VMLabelNumber].LabelNumber = VMLabelNumber;
	strcpy_s(Label[VMLabelNumber].LabelName, secondword);
	VMLabelNumber++;
}

void GotoVMLabel(char* s){
	
	std::ofstream fout(OutputName, std::ios::app);
	fout << "@" << FunctionName << "$" << s << std::endl;
	Out("0;JMP");
}

void If_GotoLabel(char* s){
	
	std::ofstream fout(OutputName, std::ios::app);
	Out("@SP");
	Out("M=M-1");
	Out("A=M");
	Out("D=M");
	fout << "@" << FunctionName << "$" << s << std::endl;
	Out("D;JNE");
}