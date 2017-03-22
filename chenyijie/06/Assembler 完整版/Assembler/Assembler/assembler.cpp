#include "assembler.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

void Assembler::Getline()
{
	std::ifstream fin("in.asm");
	char buf[100];
	line = 0;
	while (fin.getline(buf, sizeof(buf)))
	{
		int len = strlen(buf);
		//格式化指令 去除空格
		if ((buf[0] == '/' && buf[1] == '/') || len ==0)
		{
			continue;//过滤注释
		}
		for (int i = 0; i < len; i++)
		{
			if (buf[i] == ' ')
			{
				for (int j = i; j < len - 1; j++)
				{
					buf[j] = buf[j + 1];
				}
				buf[len - 1] = '\0';
				len--;
				i--;
			}
		}
		for (int i = 0; i < len - 1; i++)
		{
			if (buf[i] == '/' && buf[i + 1] == '/')
			{
				buf[i] = '\0';
				break;
			}
		}
		cout << line << ": "<<buf << endl;
		strcpy(instruction, buf);
		Translate();
	}
}

void Assembler::Translate()
{
	int number = 0;
	int len = strlen(instruction);
	for (int i = 0; i < 16; i++)
	{
		bin[i] = 0;
	}
	if (instruction[0] == '(')
	{
		return;
		char label_symbol[30];
		for (int i = 1; i < len - 1; i++)
		{
			label_symbol[i - 1] = instruction[i];
		}
		label_symbol[len - 2] = '\0';
		if (NewSymbol(label_symbol))
		{
			AddLabelSymbol(label_symbol);
		}
	
	}


	//翻译A指令
	if (instruction[0] == '@')
	{
		line++;
		bool hasbeentranslate = false;
		bin[15] = 0;
		if (!(instruction[1] <= '9' && instruction[1] >= '0'))
		{
			if (len == 3)
			{

				if (instruction[1] == 'S' && instruction[2] == 'P')
				{
					number = 0;
					hasbeentranslate = true;
				}

				if (instruction[1] == 'R' && instruction[2] == '0')
				{
					number = 0; hasbeentranslate = true;
				}
				if (instruction[1] == 'R' && instruction[2] == '1')
				{
					number = 1; hasbeentranslate = true;
				}
				if (instruction[1] == 'R' && instruction[2] == '2')
				{
					number = 2; hasbeentranslate = true;
				}
				if (instruction[1] == 'R' && instruction[2] == '3')
				{
					number = 3; hasbeentranslate = true;
				}
				if (instruction[1] == 'R' && instruction[2] == '4')
				{
					number = 4; hasbeentranslate = true;
				}
				if (instruction[1] == 'R' && instruction[2] == '5')
				{
					number = 5; hasbeentranslate = true;
				}
				if (instruction[1] == 'R' && instruction[2] == '6')
				{
					number = 6; hasbeentranslate = true;
				}
				if (instruction[1] == 'R' && instruction[2] == '7')
				{
					number = 7; hasbeentranslate = true;
				}
				if (instruction[1] == 'R' && instruction[2] == '8')
				{
					number = 8; hasbeentranslate = true;
				}
				if (instruction[1] == 'R' && instruction[2] == '9')
				{
					number = 9; hasbeentranslate = true;
				}
			}
			if (len == 4)
			{

				if (instruction[1] == 'L' && instruction[2] == 'C' && instruction[3] == 'L')
				{
					number = 1; hasbeentranslate = true;
				}
				if (instruction[1] == 'A' && instruction[2] == 'R' && instruction[3] == 'G')
				{
					number = 2; hasbeentranslate = true;
				}
				if (instruction[1] == 'K' && instruction[2] == 'B' && instruction[3] == 'D')
				{
					number = 24576; hasbeentranslate = true;
				}
				if (instruction[1] == 'R' && instruction[2] == '1' && instruction[3] == '0')
				{
					number = 10; hasbeentranslate = true;
				}
				if (instruction[1] == 'R' && instruction[2] == '1' && instruction[3] == '1')
				{
					number = 11; hasbeentranslate = true;
				}
				if (instruction[1] == 'R' && instruction[2] == '1' && instruction[3] == '2')
				{
					number = 12; hasbeentranslate = true;
				}
				if (instruction[1] == 'R' && instruction[2] == '1' && instruction[3] == '3')
				{
					number = 13; hasbeentranslate = true;
				}
				if (instruction[1] == 'R' && instruction[2] == '1' && instruction[3] == 'a')
				{
					number = 14; hasbeentranslate = true;
				}
				if (instruction[1] == 'R' && instruction[2] == '1' && instruction[3] == '5')
				{
					number = 15; hasbeentranslate = true;
				}
			}
			if (len == 5)
			{
				if (instruction[1] == 'T' && instruction[2] == 'H' && instruction[3] =='I' && instruction[4] =='S')
				{
					number = 3; hasbeentranslate = true;
				}
				if (instruction[1] == 'T' && instruction[2] == 'H' && instruction[3] == 'A' && instruction[4] == 'T')
				{
					number = 4; hasbeentranslate = true;
				}
			}
			if (len > 5)
			{
				if (instruction[1] == 'S' && instruction[2] == 'C' && instruction[3] == 'R' && instruction[4] == 'E' && instruction[5] == 'E' && instruction[6] == 'N')
				{
					number = 16384; hasbeentranslate = true;
				}
			}
			

			if (!hasbeentranslate)
			{
				char symbol_[30];
				for (int i = 1; i < len; i++)
				{
					symbol_[i - 1] = instruction[i];
				}
				symbol_[len - 1] = '\0';

				if (NewSymbol(symbol_) && !InLabelSymbol(symbol_))
				{
					AddSymbol(symbol_);
				}
				if (InSymbol(symbol_))
				{
					number = Get_SymbolValue(symbol_);
				}
				if (InLabelSymbol(symbol_))
				{
					number = Get_LabelSymbolValue(symbol_);
				}
				
			}
		}
		else
		{
			for (int j = 1; j <= len - 1; j++)
			{
				number = number * 10 + instruction[j] - '0';
			}
		}
		cout <<"A指令：" <<number << endl;


		if (number > 32767)
		{
			std::cout << "ERROR AT A-INSTRUCTION: VALUE MORE THAN 2^15";
			system("pause");
			exit(0);
		}

		for (int i = 0; i <= 14; i++)
		{
			bin[i] = number % 2;
			number = number / 2;
		}
	}

	//翻译C指令
	int pos_EQU = 0, pos_SEM = 0;
	if (instruction[0]!='@')
	{
		line++;
		bin[15] = bin[14] = bin[13] = 1;

		bool is_EQU = false, is_SEM = false;

		for (int i = 0; i < len; i++)
		{
			if (instruction[i] == '=')
			{
				is_EQU = true;
				pos_EQU = i;
			}
			if (instruction[i] == ';')
			{
				is_SEM = true;
				pos_SEM = i;
			}
		}
		if (is_EQU)
		{
			bool is_A, is_M, is_D;
			is_A = is_D = is_M = false;

			for (int i = 0; i < pos_EQU; i++)
			{
				if (instruction[i] == 'A')
				{
					is_A = true;
				}
				if (instruction[i] == 'M')
				{
					is_M = true;
				}
				if (instruction[i] == 'D')
				{
					is_D = true;
				}
			}
			if (is_A)
			{
				bin[5] = 1;
			}
			if (is_M)
			{
				bin[3] = 1;
			}
			if (is_D)
			{
				bin[4] = 1;
			}

		}
		else
		{
			bin[3] = bin[4] = bin[5] = 0;
		}
		//有等号计算目的地

		int pos_comp;
		if (is_EQU)
		for (int i = pos_EQU+1; i<len; i++)
		{
			if (instruction[i] == ';')
			{
				pos_comp = i-1;
				break;
			}
			if (instruction[i+1] == '\0')
			{
				pos_comp = i;
				break;
			}
		}
		
		if (!is_EQU && is_SEM)
		{
			pos_EQU = -1;
			for (int i = 0; i < len; i++)
			{
				if (instruction[i] == ';')
				{
					pos_comp = i - 1;
					break;
				}
				if (instruction[i + 1] == '\0')
				{
					pos_comp = i;
					break;
				}
			}

		}
		//test
		cout << "C指令:";
		for (int i = pos_EQU+1; i <= pos_comp; i++)
		{
			cout << instruction[i];
		}
		cout << endl;

		int len_comp = pos_comp - pos_EQU;
		cout << "指令长度："<< pos_comp - pos_EQU << endl;
		int a;//bin[12]
		//下面翻译计算指令
		switch (len_comp)
		{
		case 1:
			switch (instruction[pos_comp])
			{
			case '0':
				a = 0;
				SetC("101010");
				break;
			case '1':
				a = 0;
				SetC("111111");
			case 'D':
				a = 0;
				SetC("001100");
				 break;
			case 'A':
				a = 0;
				SetC("110000");
				break;
			case 'M':
				a = 1;
				SetC("110000");
				break;
			default:
				break;
			}
			break;
		case 2:
			char t[3];
			t[0] = instruction[pos_EQU + 1];
			t[1] = instruction[pos_comp];
			t[2] = '\0';
			if (strcmp(t, "-1") == 0)
			{
				a = 0;
				SetC("111010");
			}
			if (strcmp(t, "!D") == 0)
			{
				a = 0;
				SetC("001101");
			}
			if (strcmp(t, "!A") == 0)
			{
				a = 0;
				SetC("110001");
			}
			if (strcmp(t, "-D") == 0)
			{
				a = 0;
				SetC("001111");
			}
			if (strcmp(t, "-A") == 0)
			{
				a = 0;
				SetC("110011");
			}
			if (strcmp(t, "!M") == 0)
			{
				a = 1;
				SetC("110001");
			}
			if (strcmp(t, "-M") == 0)
			{
				a = 1;
				SetC("110011");
			}
			break;
		case 3:
			char s[4];
			s[0] = instruction[pos_EQU + 1];
			s[1] = instruction[pos_EQU + 2];
			s[2] = instruction[pos_EQU + 3];
			s[3] = '\0';
			if (strcmp(s, "D+1")==0 || strcmp(s,"1+D")==0)
			{
				a = 0;
				SetC("011111");
			}
			if (strcmp(s, "A+1") == 0 || strcmp(s, "1+A") == 0)
			{
				a = 0;
				SetC("110111");
			}if (strcmp(s, "D-1") == 0 || strcmp(s, "") == 0)
			{
				a = 0;
				SetC("001110");
				
			}if (strcmp(s, "A-1") == 0 || strcmp(s, "") == 0)
			{
				a = 0;
				SetC("110010");
			}if (strcmp(s, "D+A") == 0 || strcmp(s, "A+D") == 0)
			{
				a = 0;
				SetC("000010");
			}if (strcmp(s, "D-A") == 0 || strcmp(s, "") == 0)
			{
				a = 0;
				SetC("010011");
			}if (strcmp(s, "A-D") == 0 || strcmp(s, "") == 0)
			{
				a = 0;
				SetC("000111");
			}if (strcmp(s, "D&A") == 0 || strcmp(s, "A&D") == 0)
			{
				a = 0;
				SetC("000000");
			}if (strcmp(s, "D|A") == 0 || strcmp(s, "A|D") == 0)
			{
				a = 0;
				SetC("010101");
			}if (strcmp(s, "M+1") == 0 || strcmp(s, "1+M") == 0)
			{
				a = 1;
				SetC("110111");
			}if (strcmp(s, "M-1") == 0 || strcmp(s, "") == 0)
			{
				a = 1;
				SetC("110010");
			}if (strcmp(s, "D+M") == 0 || strcmp(s, "M+D") == 0)
			{
				a = 1;
				SetC("000010");
			}if (strcmp(s, "D-M") == 0 || strcmp(s, "") == 0)
			{
				a = 1;
				SetC("010011");
			}if (strcmp(s, "M-D") == 0 || strcmp(s, "") == 0)
			{
				a = 1;
				SetC("000111");
			}if (strcmp(s, "D&M") == 0 || strcmp(s, "M&D") == 0)
			{
				a = 1;
				SetC("000000");
			}if (strcmp(s, "D|M") == 0 || strcmp(s, "M|D") == 0)
			{
				a = 1;
				SetC("010101");
			}
			break;
		default:
			break;
		}//翻译成对应命令

		bin[12] = a;




		//翻译跳转指令
		if (is_SEM)
		{
			char x[4];
			x[0] = instruction[pos_SEM + 1];
			x[1] = instruction[pos_SEM + 2];
			x[2] = instruction[pos_SEM + 3];
			x[3] = '\0';

			if (strcmp(x, "JGT") == 0)
			{
				Setjump("001");
			}
			if (strcmp(x, "JEQ") == 0)
			{
				Setjump("010");
			}
			if (strcmp(x, "JGE") == 0)
			{
				Setjump("011");
			}
			if (strcmp(x, "JLT") == 0)
			{
				Setjump("100");
			}
			if (strcmp(x, "JNE") == 0)
			{
				Setjump("101");
			}
			if (strcmp(x, "JLE") == 0)
			{
				Setjump("110");
			}
			if (strcmp(x, "JMP") == 0)
			{
				Setjump("111");
			}


		}


	}
	
	




	Output();
}

void Assembler::Output()
{
	std::ofstream fout("out.hack", ios_base::app);
	for (int i = 15; i >= 0; i--)
	{
		fout << bin[i];
		std::cout << bin[i];
	}
	std::cout << std::endl;
	fout << std::endl;

}

void Assembler::SetC(char x[6])
{
	for (int i = 11; i >= 6; i--)
	{
		bin[i] = x[11 - i] - '0';
	}
}

void Assembler::Setjump(char x[3])
{
	for (int i = 2; i >= 0; i--)
	{ 
		bin[i] = x[2 - i]-'0';
	}
}

bool Assembler::NewSymbol(char * c)
{
	for (int i = 1; i <= symbol_number; i++)
	{
		if (strcmp(c, symbol[i].name)==0)
		{
			return false;
		}
	}
	return true;
}

void Assembler::AddSymbol(char* c)
{
	symbol_number++;
	strcpy(symbol[symbol_number].name, c);
	symbol[symbol_number].value = 15 + symbol_number;
}

int Assembler::Get_SymbolValue(char * c)
{
	for (int i = 1; i <= symbol_number; i++)
	{
		if (strcmp(symbol[i].name, c) == 0)
		{
			return symbol[i].value;
		}
	}
	return -1;
}

void Assembler::First_SCAN()
{
	ifstream fin("in.asm");

	if (!fin.is_open())
	{
		cout << "无法打开文件！";
		system("pause");
		exit(0);
	}
	line = 0;
	
	char buf[100];

	while (fin.getline(buf, sizeof(buf)))
	{
		int len = strlen(buf);
		//格式化指令 去除空格
		if ((buf[0] == '/' && buf[1] == '/') || len == 0)
		{
			continue;//过滤注释
		}
		for (int i = 0; i < len; i++)
		{
			if (buf[i] == ' ')
			{
				for (int j = i; j < len - 1; j++)
				{
					buf[j] = buf[j + 1];
				}
				buf[len - 1] = '\0';
				len--;
				i--;
			}
		}
		for (int i = 0; i < len-1; i++)
		{
			if (buf[i] == '/' && buf[i+1]== '/')
			{
				buf[i] = '\0';
				break;
			}
		}
		char instruction_[100];
		strcpy(instruction_, buf);
		
		if (instruction_[0] == '(')
		{
			char temp_symbol[30];
			for (int i = 1; i < len - 1; i++)
			{
				temp_symbol[i - 1] = instruction_[i];
			}
			temp_symbol[len - 2] = '\0';
			if (NewLabelSymbol(temp_symbol))
			{
				
				AddLabelSymbol(temp_symbol);
			}
		}
		else
		{
			line++;
		}

	}
	fin.close();
}

bool Assembler::NewLabelSymbol(char *c)
{
	for (int i = 1; i <= labelsymbol_number; i++)
	{
		if (strcmp(c, label[i].name) == 0)
		{
			return false;
		}
	}
	return true;
}

void Assembler::AddLabelSymbol(char * c)
{
	labelsymbol_number++;
	strcpy(label[labelsymbol_number].name, c);
	label[labelsymbol_number].value = line;
}

int Assembler::Get_LabelSymbolValue(char *c)
{
	for (int i = 1; i <= labelsymbol_number; i++)
	{
		if (strcmp(label[i].name, c) == 0)
		{
			return label[i].value;
		}
	}
	return -1;
}

void Assembler::Debug()
{
	cout << "符号表：" << endl;
	for (int i = 1; i <= labelsymbol_number; i++)
	{
		cout << label[i].name << "   " << Get_LabelSymbolValue(label[i].name) << endl;
	}
	cout << "符号表：" << endl;
	for (int i = 1; i <= symbol_number; i++)
	{
		cout << symbol[i].name << "   " << Get_SymbolValue(symbol[i].name) << endl;
	}
}

bool Assembler::InSymbol(char *c)
{
	for (int i = 1; i <= symbol_number; i++)
	{
		if (strcmp(c, symbol[i].name)==0)
		{
			return true;
		}
	}
	return false;
}

bool Assembler::InLabelSymbol(char *c)
{
	for (int i = 1; i <= labelsymbol_number; i++)
	{
		if (strcmp(c, label[i].name) == 0)
		{
			return true;
		}
	}
	return false;

}
