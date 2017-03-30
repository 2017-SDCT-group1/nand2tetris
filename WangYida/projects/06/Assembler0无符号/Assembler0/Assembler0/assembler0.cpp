#include "assembler0.h"
#include <fstream>
#include <iostream>
#include <string>



char instruction[100];
char row[100];
int out[16];
int value;


void DealWithSingleRow(){
	std::ifstream fin("source.asm");
	while(fin.getline(row,100)){
	
		int L = strlen(row);
		if(L == 0 || (row[0] == '/' && row[1] == '/') )
			continue;						//忽略整行的注释或空行
		Simlplify();						//删去空格 
		Translate();						//编译
		Out();								//输出

	}
}

void Simlplify(){			//删去空格 
	int L = strlen(row);	
	for(int i = 0; i < L; i++){
		if(row[i] == ' '){
			for(int j = i; j < L; j++)
				row[j] = row[j + 1];
			i--;
			L--;
			row[L] = '\0';
		}
	}
	strcpy_s(instruction, row);
}

void Translate(){			//编译文件
	int Type = CommandType();
	switch (Type){
		case 'A' :{
			DealWithA();
			break;
		}
		case ('C' + 'J') :{
			DealWithCJ();
			break;
		}
		case ('C' + 'E') :{
			DealWithCE();
			break;
		}
	}
}

void Out(){					//输出文件
	std::ofstream fout("out.hack", std::ios::app);
	for(int i = 15; i >= 0; i--){
		fout << out[i];
	}
	fout << std::endl;
	//outfile.close();
}

int CommandType(){			//返回指令类型
	int L = strlen(instruction);
	if(instruction[0] == '@')
		return 'A';
	for(int i = 0; i < L; i++){
		if(instruction[i] == '=')
			return ('C' + 'E');
		if(instruction[i] == ';')
			return ('C' + 'J');
	}
	return 0;
}

void DealWithA(){	//编译A指令
	int L = strlen(instruction);
	value = 0;
	out[15] = 0;
	for(int i = 1; i < L; i++){
		value = value * 10 + instruction[i] - '0';
	}
	for(int i = 0; i <= 14; i++){
		out[i] = value % 2;
		value /=2;
	}
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

void DealWithCE(){			//编译
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

void DealWithCJ(){

}