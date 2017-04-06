#include <iostream>
#include "assembler.h"
#include <fstream>
#include <string>
#include <cctype>

using namespace std;


char instruction[100];
char row[100];
char temp_symbol[50];
DataSymbol datasymbols[1000];
InstructionSymbol instructionsymbols[1000];
int linenumber;
int instructionsymbols_number = 0;
int datasymbols_number;
int scan_time;
int value;
int out[16];
int Ponggame;

void DealAsLine(){
	scan_time++;
	std::ifstream fin("source.asm");
	linenumber = -1;
	while(fin.getline(row,100)){
		linenumber++;
		int L = strlen(row);
		if(L == 0 || (row[0] == '/' && row[1] == '/') ){
			linenumber--;
			continue;
		}
		CleanLine();
		Translate();
		if( (scan_time == 2) && (CommandType() != 'S') )
			Out();

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
	strcpy_s(instruction,row);
}

void Out(){
	std::ofstream fout("out.hack", std::ios::app);
	for(int i = 15; i >=0; i--){
		fout << out[i];
	}
	fout << std::endl;
}

int CommandType(){
	int L = strlen(instruction);
	if(instruction[0] == '@')
		return 'A';
	if(instruction[0] == '(')
		return 'S';
	for(int i = 0; i < L; i++){
		if(instruction[i] == '=')
			return ('C' + 'E');
		if(instruction[i] == ';')
			return ('C' + 'J');
	}
	return 0;
}

void Translate(){
	int Type = CommandType();
	switch(Type){
	case 'A' :{
		DealWithA();
		break;
			  }
	case 'S' :{
		DealWithSy();
		break;
			  }
	case ('C' + 'E') :{
		DealWithCE();
		break;
					  }
	case ('C' + 'J') :{
		DealWithCJ();
		break;
					  }
	default :
		break;
	}
}

void DealWithA(){
	if(isdigit(instruction[1]) )
		DealWithANormal();
	else
		DealWithASymbol();
}

void DealWithANormal(){
	int L = strlen(instruction);
	value = 0;
	out[15] = 0;
	for(int i = 1; i < L; i++)
		value = value * 10 + instruction[i] - '0';
	for(int i = 0; i <= 14; i++){
		out[i] = value % 2;
		value /= 2;
	}
}

void DealWithASymbol(){
	int i = 1;
	while(instruction[i] != '\0'){
		temp_symbol[i - 1] = instruction[i];
		i++;
	}
	temp_symbol[i - 1] = '\0';
	if(scan_time == 1){
		if(!IsDataSymbol(temp_symbol)){
			AddDataSymbol(temp_symbol);
		}
	}
	if(scan_time == 2){
		if(IsInstructionSymbol(temp_symbol)){
			value = GetInstructionAddress(temp_symbol);
			out[15] = 0;
			for(int j = 0; j <= 14; j++){
				out[j] = value % 2;
				value /= 2;
			}
		}
		if(IsDataSymbol(temp_symbol)){
			value = GetDataAddress(temp_symbol);
			out[15] = 0;
			for(int j = 0; j <= 14; j++){
				out[j] = value % 2;
				value /= 2;
			}
		}
		if(!IsInstructionSymbol(temp_symbol) && !IsDataSymbol(temp_symbol)){
			AddDataSymbol(temp_symbol);
			value = GetDataAddress(temp_symbol);
			out[15] = 0;
			for(int j = 0; j <= 14; j++){
				out[j] = value % 2;
				value /= 2;
			}
		}

	}
} 
	
void DealWithCE(){
	int i = 0;
	bool A, M, D;
	A = M = D = false;
	out[3] = out[4] = out[5] = out[0] = out[1] = out[2] = 0;//jump域 & 初始化dest域
	out[13] = out[14] = out[15] = 1;	
	while(instruction[i] != '='){		//处理dest域
		if(instruction[i] == 'A'){
			A = true;
			out[5] = 1;
		}
		if(instruction[i] == 'M'){
			M = true;
			out[3] = 1;
		}
		if(instruction[i] == 'D'){
			D = true;
			out[4] = 1;
		}
		i++;
	}
	//以下处理comp域Orz
	int j = 0;
	while(instruction[j] != '='){
		j++;
	}
	j++;

	if(instruction[j] == '0')
		Comp("0101010");
	if(instruction[j] == '1')
		Comp("0111111");
	if(instruction[j] == 'D')
		Comp("0001100");
	if(instruction[j] == 'A')
		Comp("0110000");
	if(instruction[j] == 'M')
		Comp("1110000");

	if(instruction[j] == '-' && instruction[j + 1] == '1')
		Comp("0111010");
	if(instruction[j] == '-' && instruction[j + 1] == 'D')
		Comp("0001111");
	if(instruction[j] == '-' && instruction[j + 1] == 'A')
		Comp("0110011");
	if(instruction[j] == '-' && instruction[j + 1] == 'M')
		Comp("1110011");

	if(instruction[j] == '!' && instruction[j + 1] == 'D')
		Comp("0001101");
	if(instruction[j] == '!' && instruction[j + 1] == 'A')
		Comp("0110001");
	if(instruction[j] == '!' && instruction[j + 1] == 'M')
		Comp("1110001");

	if(instruction[j] == 'D' && instruction[j + 2] == '1' && instruction[j + 1] == '+')
		Comp("0011111");
	if(instruction[j] == 'D' && instruction[j + 2] == '1' && instruction[j + 1] == '-')
		Comp("0001110");

	if(instruction[j] == 'A' && instruction[j + 1] == '+' && instruction[j + 2] == '1')
		Comp("0110111");
	if(instruction[j] == 'M' && instruction[j + 1] == '+' && instruction[j + 2] == '1')
		Comp("1110111");

	if(instruction[j] == 'A' && instruction[j + 1] == '-' && instruction[j + 2] == '1')
		Comp("0110010");
	if(instruction[j] == 'M' && instruction[j + 1] == '-' && instruction[j + 2] == '1')
		Comp("1110010");

	if(instruction[j] == 'A' && instruction[j + 1] == '-' && instruction[j + 2] == 'D')
		Comp("0000111");
	if(instruction[j] == 'M' && instruction[j + 1] == '-' && instruction[j + 2] == 'D')
		Comp("1000111");

	if(instruction[j] == 'D' && instruction[j + 1] == '-' && instruction[j + 2] == 'A')
		Comp("0010011");
	if(instruction[j] == 'D' && instruction[j + 1] == '-' && instruction[j + 2] == 'M')
		Comp("1010011");

	if(instruction[j] == 'D' && instruction[j + 1] == '+' && instruction[j + 2] == 'A')
		Comp("0000010");
	if(instruction[j] == 'D' && instruction[j + 1] == '+' && instruction[j + 2] == 'M')
		Comp("1000010");

	if(instruction[j] == 'D' && instruction[j + 1] == '&' && instruction[j + 2] == 'A')
		Comp("0000000");
	if(instruction[j] == 'D' && instruction[j + 1] == '&' && instruction[j + 2] == 'M')
		Comp("1000000");

	if(instruction[j] == 'D' && instruction[j + 1] == '|' && instruction[j + 2] == 'A')
		Comp("0010101");
	if(instruction[j] == 'D' && instruction[j + 1] == '|' && instruction[j + 2] == 'M')
		Comp("1010101");

}

void Comp(char a[7]){
	out[12] = a[0] - '0';
	out[11] = a[1] - '0';
	out[10] = a[2] - '0';
	out[9]  = a[3] - '0';
	out[8]  = a[4] - '0';
	out[7]  = a[5] - '0';
	out[6]  = a[6] - '0';
}

void DealWithSy(){
	linenumber--;
	if(scan_time == 1){
		int L = strlen(instruction);
		for(int i = 1; i <= (L - 2); i++)
			temp_symbol[i - 1] = instruction[i];
		temp_symbol[strlen(instruction) - 2] = '\0';
		AddInstructionSymbol(temp_symbol);
	}
}

void DealWithCJ(){
	out[5] = out[4] = out[3] =  0;//dest域
	out[13] = out[14] = out[15] = 1;
	//以下处理comp域
	int j = 0;
	if(instruction[j] == '0')
		Comp("0101010");
	if(instruction[j] == '1')
		Comp("0111111");
	if(instruction[j] == 'D')
		Comp("0001100");
	if(instruction[j] == 'A')
		Comp("0110000");
	if(instruction[j] == 'M')
		Comp("1110000");

	if(instruction[j] == '-' && instruction[j + 1] == '1')
		Comp("0111010");
	if(instruction[j] == '-' && instruction[j + 1] == 'D')
		Comp("0001111");
	if(instruction[j] == '-' && instruction[j + 1] == 'A')
		Comp("0110011");
	if(instruction[j] == '-' && instruction[j + 1] == 'M')
		Comp("1110011");

	if(instruction[j] == '!' && instruction[j + 1] == 'D')
		Comp("0001101");
	if(instruction[j] == '!' && instruction[j + 1] == 'A')
		Comp("0110001");
	if(instruction[j] == '!' && instruction[j + 1] == 'M')
		Comp("1110001");

	if(instruction[j] == 'D' && instruction[j + 2] == '1' && instruction[j + 1] == '+')
		Comp("0011111");
	if(instruction[j] == 'D' && instruction[j + 2] == '1' && instruction[j + 1] == '-')
		Comp("0001110");

	if(instruction[j] == 'A' && instruction[j + 1] == '+' && instruction[j + 2] == '1')
		Comp("0110111");
	if(instruction[j] == 'M' && instruction[j + 1] == '+' && instruction[j + 2] == '1')
		Comp("1110111");

	if(instruction[j] == 'A' && instruction[j + 1] == '-' && instruction[j + 2] == '1')
		Comp("0110010");
	if(instruction[j] == 'M' && instruction[j + 1] == '-' && instruction[j + 2] == '1')
		Comp("1110010");

	if(instruction[j] == 'A' && instruction[j + 1] == '-' && instruction[j + 2] == 'D')
		Comp("0000111");
	if(instruction[j] == 'M' && instruction[j + 1] == '-' && instruction[j + 2] == 'D')
		Comp("1000111");

	if(instruction[j] == 'D' && instruction[j + 1] == '-' && instruction[j + 2] == 'A')
		Comp("0010011");
	if(instruction[j] == 'D' && instruction[j + 1] == '-' && instruction[j + 2] == 'M')
		Comp("1010011");

	if(instruction[j] == 'D' && instruction[j + 1] == '+' && instruction[j + 2] == 'A')
		Comp("0000010");
	if(instruction[j] == 'D' && instruction[j + 1] == '+' && instruction[j + 2] == 'M')
		Comp("1000010");

	if(instruction[j] == 'D' && instruction[j + 1] == '&' && instruction[j + 2] == 'A')
		Comp("0000000");
	if(instruction[j] == 'D' && instruction[j + 1] == '&' && instruction[j + 2] == 'M')
		Comp("1000000");

	if(instruction[j] == 'D' && instruction[j + 1] == '|' && instruction[j + 2] == 'A')
		Comp("0010101");
	if(instruction[j] == 'D' && instruction[j + 1] == '|' && instruction[j + 2] == 'M')
		Comp("1010101");

	//以下处理jump域:
	int i = 0;
	while(instruction[i] != ';')
		i++;
	i++;
	if(instruction[i] == 'J' && instruction[i + 1] == 'G' && instruction[i + 2] == 'T'){
		out[2] = 0;
		out[1] = 0;
		out[0] = 1;
	}
	if(instruction[i] == 'J' && instruction[i + 1] == 'E' && instruction[i + 2] == 'Q'){
		out[2] = 0;
		out[1] = 1;
		out[0] = 0;
	}
	if(instruction[i] == 'J' && instruction[i + 1] == 'G' && instruction[i + 2] == 'E'){
		out[2] = 0;
		out[1] = 1;
		out[0] = 1;
	}
	if(instruction[i] == 'J' && instruction[i + 1] == 'L' && instruction[i + 2] == 'T'){
		out[2] = 1;
		out[1] = 0;
		out[0] = 0;
	}
	if(instruction[i] == 'J' && instruction[i + 1] == 'N' && instruction[i + 2] == 'E'){
		out[2] = 1;
		out[1] = 0;
		out[0] = 1;
	}
	if(instruction[i] == 'J' && instruction[i + 1] == 'L' && instruction[i + 2] == 'E'){
		out[2] = 1;
		out[1] = 1;
		out[0] = 0;
	}
	if(instruction[i] == 'J' && instruction[i + 1] == 'M' && instruction[i + 2] == 'P'){
		out[2] = 1;
		out[1] = 1;
		out[0] = 1;
	}
	if(instruction[i] == '\0'){
		out[2] = 0;
		out[1] = 0;
		out[0] = 0;
	}
}

void AddInstructionSymbol(char* s){
	strcpy_s(instructionsymbols[instructionsymbols_number].name,s);
	instructionsymbols[instructionsymbols_number].number = linenumber + 1;
	instructionsymbols_number++;
}

bool IsInstructionSymbol(char* s){
	for(int i = 0; i < instructionsymbols_number; i++){
		if(strcmp(s, instructionsymbols[i].name) == 0)
			return true;
	}
	return false;
}

int GetInstructionAddress(char* s){	
	for(int i = 0; i < instructionsymbols_number; i++){
		if(strcmp(s, instructionsymbols[i].name) == 0)
			return instructionsymbols[i].number;
	}
	return NULL;
}

void AddDataSymbol(char* s){
	strcpy_s(datasymbols[datasymbols_number].name,s);
	datasymbols[datasymbols_number].number = 16 + datasymbols_number;
	datasymbols[datasymbols_number].validity = true;
	datasymbols_number++;
}

bool IsDataSymbol(char* s){
	//if(IsInstructionSymbol(s))
	//	return false;
	for(int i = 0; i < datasymbols_number; i++){
		if(strcmp(s, datasymbols[i].name) == 0 && datasymbols[i].validity == true)
			return true;
	}
	for(int i = 900; i < 950; i++){
		if(strcmp(s, datasymbols[i].name) == 0 && datasymbols[i].validity == true)
			return true;
	}
	return false;
}

int GetDataAddress(char* s){	
	for(int i = 0; i < datasymbols_number; i++){
		if(strcmp(s, datasymbols[i].name) == 0)
			return datasymbols[i].number;
	}
	for(int i = 900; i < 950; i++){
		if(strcmp(s, datasymbols[i].name) == 0)
			return datasymbols[i].number;
	}
	return NULL;
}

void Delete(){
	for(int i = 0; i < instructionsymbols_number; i++){
		for(int j = 0; j < datasymbols_number; j++){
			if(strcmp(instructionsymbols[i].name,datasymbols[j].name) == 0)
				datasymbols[j].validity = false;
		}
	}
	for(int i = 0; i < instructionsymbols_number; i++){
		for(int j = 900; j < 950; j++){
			if(strcmp(instructionsymbols[i].name,datasymbols[j].name) == 0)
				datasymbols[j].validity = false;
		}
	}
}
