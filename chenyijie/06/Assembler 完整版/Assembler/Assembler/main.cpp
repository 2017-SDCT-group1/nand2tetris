//本编译器处理无符号版本
//不支持报错
//不支持错误情况处理
//默认输入汇编语言正确
//忽略预定义符号

#include <iostream>

#include "assembler.h"
using namespace std;

int main()
{
	Assembler assembler;
	assembler.First_SCAN();
	assembler.Debug();
	assembler.Getline();
	assembler.Debug();
	system("pause");
}