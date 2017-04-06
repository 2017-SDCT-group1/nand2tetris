#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char predefined[23][7]={"SP","LCL","ARG","THIS","THAT","R0","R1","R2","R3","R4',""5","R6","R7","R8","R9","R10","R11","R12","R13","R14","R15","SCREEN","KBD"};
int predefined_value[23]={0,1,2,3,4,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16384,24576};
char* bu = NULL; //动态分配
char buf[10000];
char a_0[18][4]={"0","1","-1","D","A","!D","!A","-D","-A","D+1","A+1","D-1","A-1","D+A","D-A","A-D","D&A","D|A"};
int c_0[18][6]={{1,0,1,0,1,0},{1,1,1,1,1,1},{1,1,1,0,1,0},{0,0,1,1,0,0},{1,1,0,0,0,0},{0,0,1,1,0,1},{1,1,0,0,0,1},{0,0,1,1,1,1},{1,1,0,0,1,1},{0,1,1,1,1,1},{1,1,0,1,1,1},{0,0,1,1,1,0},{1,1,0,0,1,0},{0,0,0,0,1,0},{0,1,0,0,1,1},{0,0,0,1,1,1},{0,0,0,0,0,0},{0,1,0,1,0,1}};
char a_1[10][4]={"M","!M","-M","M+1","M-1","D+M","D-M","M-D","D&M","D|M"};
int c_1[10]={4,6,8,10,12,13,14,15,16,17};
char jump[7][4] = {"JGT","JEQ","JGE","JLT","JNE","JLE","JMP"};
int len = 0,label_num = 0,loop_num = 0;
char labels[30][30];
int label_value[30] = {0};

int comp_pre_defined(int a,int b)
{
	int i,j;
	for (i = 0;i < 23;i++)
	{
		if ((b - a + 1) != strlen(predefined[i]))
			continue;
		for (j = 0;j < b - a + 1;j++)
		{
			if (predefined[i][j] != buf[a + j])
				break;
		}
		if (j == b - a + 1)
			return i;
		else
			continue;
	}
	return -1;
}

int add_labels(int a,int b)
{
	int i,j;
	for (i = 0;i < label_num;i++)
	{
		if (strlen(labels[i]) == b - a + 1)
		{
			for (j = 0;j < b - a + 1;j ++)
			{
				if (labels[i][j] != buf[a + j])
					break;
			}
			if (j == b - a + 1)
				return i;
		}
	}
	for (i = 0;i <= b - a;i++)
	{
		labels[label_num][i] = buf[a + i];
	}
	labels[label_num][i] = '\0';
	label_num ++;
	return -1;
}

int comp_c_ins(int a,int b)
{
	int i,j;
	for (i = 0;i < 28;i++)
	{
		if (i < 18)
		{
			if (b - a + 1 == strlen(a_0[i]))
			{
				for (j = 0;j < b - a + 1;j++)
				{
					if (a_0[i][j] != buf[a + j])
						break;
				}
				if (j == b - a + 1)
					return i;
			}
		}
		else
		{
			if (b - a + 1 == strlen(a_1[i - 18]))
			{
				for (j = 0;j < b - a + 1;j++)
				{
					if (a_1[i - 18][j] != buf[a + j])
						break;
				}
				if (j == b - a + 1)
					return i;
			}
		}
	}
}

int comp_jump(int a)
{
	int i,j;
	for (i = 0;i < 7;i++)
	{
		for (j = a;j < a + 3;j++)
		{
			if (jump[i][j - a] != buf[j])
				break;
		}
		if (j == a + 3)
			return i;
	}
	return -1;
}

int main()
{   
    char ch;
    int i,j,t,x;
    printf("Please input some line(input Ctrl + Z/D to stop):\n");
    while(scanf("%c",&ch)==1 && ch!=EOF && ch!='#')
	{ //定义一个结束符或者ctrl+z/d
        //动态的实现
		bu = (char*)realloc(bu,sizeof(char)*(len+1));
        bu[len++] = ch;
    }//建输入存入buf
	strcpy(buf,bu);
	buf[len] = '\n';
	len += 1;
	buf[len] = '\0';
    for (i = 0;i < len;i++)
	{
		if (buf[i] == '/' && buf[i + 1] == '/')
		{
			for (j = i + 1;j < len;j++)
			{
				if (buf[j] == '\n')
					break;
			}
			for (t = 0;t <= len - j + 1;t++)
			{
				buf[i + t] = buf[j + t];
			}
			len -= (j - i);
			i--;
			buf[len] = '\0';
			continue;
		}
		if (buf[0] == '\n')
		{
			for (j = 0;j < len;j++)
			{
				buf[j] = buf[j + 1];
			}
			len -= 1;
			i--;
			buf[len] = '\0';
			continue;
		}
		if (i != 0 && buf[i] == '\n' && buf[i + 1] == '\n')
		{
			for (j = i;j < len;j++)
			{
				buf[j] = buf[j + 1];
			}
			len -= 1;
			i--;
			buf[len] = '\0';
			continue;
		}
		if (buf[i] == 32)
		{
			for (j = i;j < len;j++)
			{
				buf[j] = buf[j + 1];
			}
			len -= 1;
			i--;
			buf[len] = '\0';
			continue;
		}
	}//去注释//去空行//去空格

	for (i = 0;i < len;i ++)
	{
		if (buf[i] == '(')
		{
			for (j = i;j < len;j++)
			{
				if (buf[j] == ')')
					break;
			}
			add_labels(i + 1,j - 1);
			loop_num += 1;
			for (j = 0;j < i;j++)
			{
				if (buf[j] == '\n' && buf[j - 1] != ')')
					label_value[label_num - 1]++;
			}
		}
	}//循环labels//为label赋值

	for (i = 0;i < len;i ++)
	{
		if (buf[i] == '@' && !isdigit(buf[i + 1]))
		{
			for (j = i + 1;j < len;j++)
			{	
				if (buf[j] == '\n')
				{
					if (comp_pre_defined(i + 1,j - 1) == -1)
					{
						add_labels(i + 1,j - 1);
						label_value[label_num - 1] = label_num - loop_num + 15;
						break;
					}
					else
					{
						break;
					}
				}
			}
		}	
	}//检查labels//为label赋值

	for (i = 0;i < len;i++)
	{
		if (buf[i] == '(')
		{
			for (j = i + 1;j < len;j++)
			{
				if (buf[j] == ')')
				{
					for (t = 0;t < len - j;t++)
					{
						buf[t + i] = buf[t + j + 2];
					}
					len = len - (j - i) - 2;
					buf[len] = '\0';
					i--;
					break;
				}
				
			}
		}
	}
	//去掉loop_label行

	int value;
	for (i = 0;i < len;i++)
	{
		value = 0;
		if (buf[i] == '@')
		{
			for (j = i;j < len;j ++)
			{
				if (buf[j] == '\n')
					break;
			}
			if (isdigit(buf[i + 1]))
			{
				for (t = j - 1;t > i;t--)
				{
					value *= 10;
					value += (buf[t] - '0');
				}
				for (t = len + 16 - (j - i);t > i + 15;t--)
				{
					buf[t] = buf[t - 16 + j - i];
				}
				for (t = i + 15;t > i;t--)
				{
					buf[t] = (value % 2) + '0';
					value /= 2;	
				}			
				buf[i] = '0';
				len = len + 16 - (j - i);
				buf[len] = '\0';
			}//num
			else
			{
				if (comp_pre_defined(i + 1,j - 1) == -1)
				{
					value = label_value[add_labels(i + 1,j - 1)];
				}
				else
				{
					value = predefined_value[comp_pre_defined(i + 1,j - 1)];
				}
				if (j - i < 16)
				{
					for (t = len + 16 - (j - i);t > i + 15;t--)
					{
						buf[t] = buf[t - 16 + j - i];
					}
					for (t = i + 15;t > i;t--)
					{
						buf[t] = (value % 2) + '0';
						value /= 2;	
					}			
					buf[i] = '0';
				}
				if (j - i == 16)
				{
					for (t = i + 15;t > i;t--)
					{
						buf[t] = (value % 2) + '0';
						value /= 2;	
					}			
					buf[i] = '0';
				}
				if (j - i > 16)
				{
					for (t = i + 16;t <= len + 16 - (j - i);t++)
					{
						buf[t] = buf[t - 16 + j - i];
					}
					for (t = i + 15;t > i;t--)
					{
						buf[t] = (value % 2) + '0';
						value /= 2;	
					}			
					buf[i] = '0';
				}
				len = len + 16 - (j - i);
				buf[len] = '\0';
			}//label
		}
	}//替换@行
	
	int instruction[16],a_status;
	instruction[0] = 1;
	instruction[1] = 1;
	instruction[2] = 1;
	
	int equal;
	for (i = 0;i < len;i++)
	{
		for (j = 3;j < 16;j++)
		{
			instruction[j] = 0;
		}//初始化
		equal = 0;
		if(buf[i] == '\n' && buf[i + 1] != '\0')
		{
			for (j = i + 1;j < len;j++)
			{
				a_status = 1;
				if (buf[j] == '\n')
				{
					break;
				}
				if (buf[j] == ';')
				{
					a_status = 0;
					equal = 0;
					break;
				}
				if (buf[j] == '=')
				{
					a_status = 0;
					equal = 1;
					break;
				}
				
			}
			if (a_status == 1)
					continue;
			if (equal == 1)
			{
				if (j - i == 2)
				{
					if (buf[i + 1] == 'A')
					{
						instruction[10] = 1;
						instruction[11] = 0;
						instruction[12] = 0;
					}
					if (buf[i + 1] == 'M')
					{
						instruction[10] = 0;
						instruction[11] = 0;
						instruction[12] = 1;
					}
					if (buf[i + 1] == 'D')
					{
						instruction[10] = 0;
						instruction[11] = 1;
						instruction[12] = 0;
					}
				}
				if (j - i == 3)
				{
					if (buf[i + 1] == 'A' && buf[i + 1] == 'M')
					{
						instruction[10] = 1;
						instruction[11] = 0;
						instruction[12] = 1;
					}
					if (buf[i + 1] == 'A' && buf[i + 1] == 'D')
					{
						instruction[10] = 1;
						instruction[11] = 1;
						instruction[12] = 0;
					}
					if (buf[i + 1] == 'M' && buf[i + 1] == 'D')
					{
						instruction[10] = 0;
						instruction[11] = 1;
						instruction[12] = 1;
					}
				}
				if (j - i == 4)
				{
					instruction[10] = 1;
					instruction[11] = 1;
					instruction[12] = 1;
				}
				for (x = j;x < len;x++)
				{
					if (buf[x] == '\n')
						break;
				}
				instruction[3] = comp_c_ins(j + 1,x - 1) >= 18? 1: 0;
				if (instruction[3] == 0)
				{
					for (t = 4;t < 10;t++)
					{
						instruction[t] = c_0[comp_c_ins(j + 1,x - 1)][t - 4];
					}
				}
				else
				{
					for (t = 4;t < 10;t++)
					{
						instruction[t] = c_0[c_1[comp_c_ins(j + 1,x - 1) - 18]][t - 4];
					}
				}
			}
			else
			{
				instruction[3] = 0;
				for (t = 4;t < 10;t++)
				{
					instruction[t] = c_0[comp_c_ins(i + 1,j - 1)][t - 4];
				}//a
				value = comp_jump(j + 1) + 1;
				if (value != -1)
				{
					instruction[15] = value % 2; 
					value /= 2;
					instruction[14] = value % 2; 
					value /= 2;
					instruction[13] = value; 
				}//jump
			}
			for (j = i + 1;j < len;j++)
			{
				if (buf[j] == '\n')
					break;
			}
			for (t = len + 16 - (j - i - 1);t > i + 16;t--)
			{
				buf[t] = buf[t + (j - i - 1) - 16];
			}
			for (t = i + 1;t <= i + 16;t++)
			{
				buf[t] = instruction[t - i - 1] + '0';
			}
			len = len + 16 - (j - i - 1);
			buf[len] = '\0';
			//替换
		}
	}//替换命令行
	if (buf[len - 1] != '\n')
	{
		buf[len] = '\n';
		len += 1;
		buf[len] = '\0';
	}
	for (i = 0;i < len;i++)
	{
		printf ("%c",buf[i]);
	}
	system("pause");
	free(bu);	
    return 0;
}