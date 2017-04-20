#include<iostream>
#include<string>
#include<fstream>
#include"VMtranslator.h"
#include "Parser.h"
#include "Codewriter.h"
#include "Symboltable.h"

using namespace std;

int CommandType(){
	int L = strlen(instruction);
	//if(instruction[0] == 'a' && instruction[1] == 'd' && instruction[2] == 'd'){
	if(strcmp(firstword, "add") == 0){
		return ADD_;
	}
	//if(instruction[0] == 's' && instruction[1] == 'u' && instruction[2] == 'b'){
	if(strcmp(firstword, "sub") == 0){
		return SUB_;
	}
	//if(instruction[0] == 'n' && instruction[1] == 'e' && instruction[2] == 'g'){
	if(strcmp(firstword, "neg") == 0){
		return NEG_;
	}
	//if(instruction[0] == 'a' && instruction[1] == 'n' && instruction[2] == 'd'){
	if(strcmp(firstword, "and") == 0){
		return AND_;
	}
	//if(instruction[0] == 'n' && instruction[1] == 'o' && instruction[2] == 't'){
	if(strcmp(firstword, "not") == 0){
		return NOT_;
	}
	//if(instruction[0] == 'e' && instruction[1] == 'q'){
	if(strcmp(firstword, "eq") == 0){
		return EQ_;
	}
	//if(instruction[0] == 'g' && instruction[1] == 't'){
	if(strcmp(firstword, "gt") == 0){
		return GT_;
	}
	//if(instruction[0] == 'l' && instruction[1] == 't'){
	if(strcmp(firstword, "lt") == 0){
		return LT_;
	}
	//if(instruction[0] == 'o' && instruction[1] == 'r'){
	if(strcmp(firstword, "or") == 0){
		return OR_;
	}
	//if(instruction[0] == 'p' && instruction[1] == 'u'){
	if(strcmp(firstword, "push") == 0){
		return PUSH_;
	}
	//if(instruction[0] == 'p' && instruction[1] == 'o'){
	if(strcmp(firstword, "pop") == 0){
		return POP_;
	}
	//if(instruction[0] == 'l' && instruction[1] == 'a'){
	if(strcmp(firstword, "label") == 0){
		return AddLabel_;
	}
	//if(instruction[0] == 'g' && instruction[1] == 'o'){
	if(strcmp(firstword, "goto") == 0){
		return GotoLabel_;
	}
	//if(instruction[0] == 'i' && instruction[1] == 'f'){
	if(strcmp(firstword, "if-goto") == 0){
		return if_GotoLabel_;
	}
	//if(instruction[0] == 'f' && instruction[1] == 'u'){
	if(strcmp(firstword, "function") == 0){
		return Function_;
	}
	//if(instruction[0] == 'c' && instruction[1] == 'a'){
	if(strcmp(firstword, "call") == 0){
		return CallFunction_;
	}
	//if(instruction[0] == 'r' && instruction[1] == 'e'){
	if(strcmp(firstword, "return") == 0){
		return Return_;
	}
	//to do



}

void CleanLine(){
	int L = strlen(row);
	for(int i = 0; i < L; i++){
		/*if(row[i] == ' '){
			for(int j = i; j < L; j++)
				row[j] = row[j + 1];
			i--;
			L--;
			row[L] = '\0';
		}*/
		if(row[i] == '/' && row[i + 1] == '/'){
			row[i] = '\0';
			break;
		}
	}
	strcpy_s(instruction, row);

}
//Need repairing

void DivideWords(){
	int i;
	i = 0;
	while(instruction[i] != ' '){
		firstword[i] = instruction[i];
		i+=1;
	}
	firstword[i] ='\0';

	while(instruction[i] == ' ')
		i++;
	int j = 0;
	while(instruction[i] != ' '){
		secondword[j] = instruction[i];
		j++;
		i++;
	}
	secondword[j] = '\0';

	if(i < strlen(instruction)){
		while(instruction[i] == ' ')
			i++;
		int k = 0;
		while(instruction[i] != ' ' && instruction[i] != '\0'){
			thirdword[k] = instruction[i];
			k++;
			i++;
		}
		thirdword[k] = '\0';
	}
	cout << firstword <<"||"<<secondword<<"||"<<thirdword<<std::endl;
}
//Need tests