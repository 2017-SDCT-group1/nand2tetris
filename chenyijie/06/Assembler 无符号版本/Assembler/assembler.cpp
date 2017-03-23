#include "assembler.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;
void Assembler::Getline()
{
	std::ifstream fin("in.asm");
	char buf[100];

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
		cout << buf << endl;
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
	//翻译A指令
	if (instruction[0] == '@')
	{
		bin[15] = 0;
		for (int j = 1; j <= len-1; j++)
		{
			number = number * 10 + instruction[j] - '0';
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
