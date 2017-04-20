#include <iostream>
#include <string>
#include "VMtranslator.h"
#include "Parser.h"
#include "Codewriter.h"
#include "Symboltable.h"

using namespace std; 

int main(){
	cout << "Please tell me the initial value of SP:";
	cin >> spinit;
	extern char OutputName[30];
	cout << "Please tell me how many files are being translated:";
	int filenumbers;
	cin >> filenumbers;
	cout << "Please tell me the output file's name you want:";
	cin >> OutputName;
	getchar();
	Init();
	for(int i = 0; i < filenumbers; i++){
		cout << "Please tell me the No." << i + 1 << " file's name:"; 
		Translate();
		
	}
	system("pause");
	return 0;
}

/*	
	2017.4.13	完成了Arithmetic and Logical Commands部分;

	2017.4.14	完成了Program Flow Commands部分;

				改进了文件的处理方式:	可以通过输入需要处理的文件个数及名称打开文件;
									可以输入新建的文件名;

	2017.4.15	改进了对Command Type及命令参数的判断方法；

				将Parser, Codewriter, Symboltable分开;（鉴于C++的字符串处理方式，Codewriter部分实在是很繁琐）

	2017.4.16	开始进行Function Calling Commands部分的编写;
				错得很离谱，准备期中考试完再修正；
				
	2017.4.19	继续进行Function Calling Commands部分的编写;
				编写完成，Debug中；

	2017.4.20	Debug完成，测试通过；


*/