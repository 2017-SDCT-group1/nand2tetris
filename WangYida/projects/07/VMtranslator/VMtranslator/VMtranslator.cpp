#include<iostream>
#include<string>
#include<fstream>
#include"VMtranslator.h"

using namespace std;

#define NAME_ "source"
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
//to do

int Add_NormalSymbol = 0;
int At_NormalSymbol = 0;
char instruction[100];
char row[100];
char out[100];
char temp[100];

void Translate(){
	std::ifstream fin("source.vm");
	while(fin.getline(row,100) ){
		int L = strlen(row);
		if(L == 0 || (row[0] == '/' &&row[1] == '/') ){
			continue;
		}
		CleanLine();
		Deal();

	}
}

void CleanLine(){
	int L = strlen(row);
	for(int i = 0; i < L; i++){
		if(row[i] == ' '){
			for(int j = i; j < L; j++)
				row[j] = row[j + 1];
			i--;
			L--;
			row[L] = '\0';
		}
		if(row[i] == '/' && row[i + 1] == '/'){
			row[i] = '\0';
			break;
		}
	}
	strcpy_s(instruction, row);
}

void Out(char *s){
	std::ofstream fout("out.asm", std::ios::app);
	fout << s;
	fout << std::endl;
}

int CommandType(){
	int L = strlen(instruction);
	if(instruction[0] == 'a' && instruction[1] == 'd' && instruction[2] == 'd'){
		return ADD_;
	}
	if(instruction[0] == 's' && instruction[1] == 'u' && instruction[2] == 'b'){
		return SUB_;
	}
	if(instruction[0] == 'n' && instruction[1] == 'e' && instruction[2] == 'g'){
		return NEG_;
	}
	if(instruction[0] == 'a' && instruction[1] == 'n' && instruction[2] == 'd'){
		return AND_;
	}
	if(instruction[0] == 'n' && instruction[1] == 'o' && instruction[2] == 't'){
		return NOT_;
	}
	if(instruction[0] == 'e' && instruction[1] == 'q'){
		return EQ_;
	}
	if(instruction[0] == 'g' && instruction[1] == 't'){
		return GT_;
	}
	if(instruction[0] == 'l' && instruction[1] == 't'){
		return LT_;
	}
	if(instruction[0] == 'o' && instruction[1] == 'r'){
		return OR_;
	}
	if(instruction[0] == 'p' && instruction[1] == 'u'){
		return PUSH_;
	}
	if(instruction[0] == 'p' && instruction[1] == 'o'){
		return POP_;
	}
	//to do



}

void Deal(){
	/*
	std::ofstream fout("out.asm", std::ios::app);
	Out("256");
	Out("D=A");
	Out("@SP");
	Out("M=D");
	*/
	if (CommandType() >= 101 && CommandType() <= 109)
		DealWithArithmetic();
	if(CommandType() == 110 || CommandType() == 111)
		DealWithMemory();
	//to do

}

void AtNormalSymbol(int i){
	std::ofstream fout("out.asm",std::ios::app);
	fout << "@NormalSymbol";
	fout << i;
	fout << std::endl;
	At_NormalSymbol++;
}

void AddNormalSymbol(int i){
	std::ofstream fout("out.asm",std::ios::app);
	fout << "(NormalSymbol";
	fout << i;
	fout << ")";
	fout << std::endl;
	Add_NormalSymbol++;
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
		if(instruction[4] == 'c' && instruction[5] == 'o' && instruction[6] == 'n'){	//constant
			for(int i = 0; i < (strlen(instruction) - 12); i++)
				temp[i] = instruction[i + 12];
			temp[strlen(instruction) - 12] = '\0';
			std::ofstream fout("out.asm", std::ios::app);
			fout << "@" << temp << std::endl;
			Out("D=A");
			Out("@SP");
			Out("A=M");
			Out("M=D");
			Out("@SP");
			Out("M=M+1");
		}

		if(instruction[4] == 'a' && instruction[5] == 'r' && instruction[6] == 'g'){	//argument
			for(int i = 0; i < (strlen(instruction) - 12); i++)
				temp[i] = instruction[i + 12];
			temp[strlen(instruction) - 12] = '\0';
			std::ofstream fout("out.asm", std::ios::app);
			fout << "@" << temp << std::endl;
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

		if(instruction[4] == 't' && instruction[5] == 'h' && instruction[6] == 'i'){	//this
			for(int i = 0; i < (strlen(instruction) - 8); i++)
				temp[i] = instruction[i + 8];
			temp[strlen(instruction) - 8] = '\0';
			std::ofstream fout("out.asm", std::ios::app);
			fout << "@" << temp << std::endl;
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

		if(instruction[4] == 't' && instruction[5] == 'h' && instruction[6] == 'a'){	//that
			for(int i = 0; i < (strlen(instruction) - 8); i++)
				temp[i] = instruction[i + 8];
			temp[strlen(instruction) - 8] = '\0';
			std::ofstream fout("out.asm", std::ios::app);
			fout << "@" << temp << std::endl;
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

		if(instruction[4] == 'l' && instruction[5] == 'o' && instruction[6] == 'c'){	//local
			for(int i = 0; i < (strlen(instruction) - 9); i++)
				temp[i] = instruction[i + 9];
			temp[strlen(instruction) - 9] = '\0';
			std::ofstream fout("out.asm", std::ios::app);
			fout << "@" << temp << std::endl;
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

		
		if(instruction[4] == 't' && instruction[5] == 'e' && instruction[6] == 'm'){	//temp
			for(int i = 0; i < (strlen(instruction) - 8); i++)
				temp[i] = instruction[i + 8];
			temp[strlen(instruction) - 8] = '\0';
			std::ofstream fout("out.asm", std::ios::app);
			fout << "@" << temp << std::endl;
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

		if(instruction[4] == 's' && instruction[5] == 't' && instruction[6] == 'a'){	//static
			for(int i = 0; i < (strlen(instruction) - 10); i++)
				temp[i] = instruction[i + 10];
			temp[strlen(instruction) - 10] = '\0';
			std::ofstream fout("out.asm", std::ios::app);
			fout << "@" << NAME_ << "." << temp << std::endl;
			Out("D=M");
			Out("@SP");
			Out("A=M");
			Out("M=D");
			Out("@SP");
			Out("M=M+1");
		}

		if(instruction[4] == 'p' && instruction[5] == 'o' && instruction[6] == 'i'){	//pointer
			for(int i = 0; i < (strlen(instruction) - 11); i++)
				temp[i] = instruction[i + 11];
			temp[strlen(instruction) - 11] = '\0';
			std::ofstream fout("out.asm", std::ios::app);
			fout << "@" << temp <<std::endl;
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

		if(instruction[3] == 'a' && instruction[4] == 'r' && instruction[5] == 'g'){	//argument
			for(int i = 0; i < (strlen(instruction) - 11); i++)
				temp[i] = instruction[i + 11];
			temp[strlen(instruction) - 11] = '\0';
			std::ofstream fout("out.asm", std::ios::app);
			fout << "@" << temp << std::endl;
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

		if(instruction[3] == 't' && instruction[4] == 'h' && instruction[5] == 'i'){	//this
			for(int i = 0; i < (strlen(instruction) - 7); i++)
				temp[i] = instruction[i + 7];
			temp[strlen(instruction) - 7] = '\0';
			std::ofstream fout("out.asm", std::ios::app);
			fout << "@" << temp << std::endl;
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

		if(instruction[3] == 't' && instruction[4] == 'h' && instruction[5] == 'a'){	//that
			for(int i = 0; i < (strlen(instruction) - 7); i++)
				temp[i] = instruction[i + 7];
			temp[strlen(instruction) - 7] = '\0';
			std::ofstream fout("out.asm", std::ios::app);
			fout << "@" << temp << std::endl;
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

		if(instruction[3] == 'l' && instruction[4] == 'o' && instruction[5] == 'c'){	//local
			for(int i = 0; i < (strlen(instruction) - 8); i++)
				temp[i] = instruction[i + 8];
			temp[strlen(instruction) - 8] = '\0';
			std::ofstream fout("out.asm", std::ios::app);
			fout << "@" << temp << std::endl;
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

		
		if(instruction[3] == 't' && instruction[4] == 'e' && instruction[5] == 'm'){	//temp
			for(int i = 0; i < (strlen(instruction) - 7); i++)
				temp[i] = instruction[i + 7];
			temp[strlen(instruction) - 7] = '\0';
			std::ofstream fout("out.asm", std::ios::app);
			fout << "@" << temp << std::endl;
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

		if(instruction[3] == 's' && instruction[4] == 't' && instruction[5] == 'a'){	//static
			for(int i = 0; i < (strlen(instruction) - 9); i++)
				temp[i] = instruction[i + 9];
			temp[strlen(instruction) - 9] = '\0';
			std::ofstream fout("out.asm", std::ios::app);
			fout << "@" << NAME_ << "." << temp << std::endl;
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

		if(instruction[3] == 'p' && instruction[4] == 'o' && instruction[5] == 'i'){	//pointer
			for(int i = 0; i < (strlen(instruction) - 10); i++)
				temp[i] = instruction[i + 10];
			temp[strlen(instruction) - 10] = '\0';
			std::ofstream fout("out.asm", std::ios::app);
			fout << "@" << temp <<std::endl;
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



