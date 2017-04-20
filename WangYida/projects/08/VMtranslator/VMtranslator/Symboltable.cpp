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

//没有单独用于处理符号表的函数