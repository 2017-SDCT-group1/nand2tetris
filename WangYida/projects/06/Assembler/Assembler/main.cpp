#include <iostream>
#include "assembler.h"

using namespace std;

int main(){
	scan_time = 0;
	datasymbols_number = 0;
	instructionsymbols_number = 0;

	strcpy_s(datasymbols[900].name,"SP\0");
	datasymbols[900].number = 0;
	datasymbols[900].validity = true;
	strcpy_s(datasymbols[901].name,"LCL\0");
	datasymbols[901].number = 1;
	datasymbols[901].validity = true;
	strcpy_s(datasymbols[902].name,"ARG\0");
	datasymbols[902].number = 2;
	datasymbols[902].validity = true;
	strcpy_s(datasymbols[903].name,"THIS\0");
	datasymbols[903].number = 3;
	datasymbols[903].validity = true;
	strcpy_s(datasymbols[904].name,"THAT\0");
	datasymbols[904].number = 4;
	datasymbols[904].validity = true;
	strcpy_s(datasymbols[905].name,"SCREEN\0");
	datasymbols[905].number = 16384;
	datasymbols[905].validity = true;
	strcpy_s(datasymbols[906].name,"KBD\0");
	datasymbols[906].number = 24576;
	datasymbols[906].validity = true;


	strcpy_s(datasymbols[907].name,"R0\0");
	strcpy_s(datasymbols[908].name,"R1\0");
	strcpy_s(datasymbols[909].name,"R2\0");
	strcpy_s(datasymbols[910].name,"R3\0");
	strcpy_s(datasymbols[911].name,"R4\0");
	strcpy_s(datasymbols[912].name,"R5\0");
	strcpy_s(datasymbols[913].name,"R6\0");
	strcpy_s(datasymbols[914].name,"R7\0");
	strcpy_s(datasymbols[915].name,"R8\0");
	strcpy_s(datasymbols[916].name,"R9\0");
	strcpy_s(datasymbols[917].name,"R10\0");
	strcpy_s(datasymbols[918].name,"R11\0");
	strcpy_s(datasymbols[919].name,"R12\0");
	strcpy_s(datasymbols[920].name,"R13\0");
	strcpy_s(datasymbols[921].name,"R14\0");
	strcpy_s(datasymbols[922].name,"R15\0");

	for(int i = 0; i <= 15; i++){
		datasymbols[907 + i].number = i;
		datasymbols[907 + i].validity = true;
	}
	
	DealAsLine();
	datasymbols_number = 0;
	DealAsLine();

	return 0;
}