#include<iostream>
#include<string>
#include<fstream>
#include"VMtranslator.h"
#include "Parser.h"
#include "Codewriter.h"
#include "Symboltable.h"#pragma once

using namespace std;

VMLabel Label[500];
FunctionSymbol Function[100];

//û�е������ڴ�����ű�ĺ���