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
	2017.4.13	�����Arithmetic and Logical Commands����;

	2017.4.14	�����Program Flow Commands����;

				�Ľ����ļ��Ĵ���ʽ:	����ͨ��������Ҫ������ļ����������ƴ��ļ�;
									���������½����ļ���;

	2017.4.15	�Ľ��˶�Command Type������������жϷ�����

				��Parser, Codewriter, Symboltable�ֿ�;������C++���ַ�������ʽ��Codewriter����ʵ���Ǻܷ�����

	2017.4.16	��ʼ����Function Calling Commands���ֵı�д;
				��ú����ף�׼�����п�������������
				
	2017.4.19	��������Function Calling Commands���ֵı�д;
				��д��ɣ�Debug�У�

	2017.4.20	Debug��ɣ�����ͨ����


*/