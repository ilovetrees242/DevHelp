#include <stdio.h>
#include <string.h>
#include <math.h>
int toOct(char *Bin){
	unsigned int length = strlen(Bin);
	int Num = 0;
	for(int i = length; i > 0; i--){
		if(*(Bin + (i - 1)) == '1'){
			Num += pow(2, length - i) * 1;	
		}
		else if(*(Bin + (i - 1)) == '0'){
			Num += pow(2, length - i) * 0;	
		}
	}
	return Num;
}
int main(){
	char Binary[260];
	char BinaryNums[256][256] = {0};
	int  NumBuffer = 0;
	char Buffer[4];
	char Result[256];
	int  Counter = 0;
	int  CounterChar = 0;
	printf("Enter a binary number(max characters 256): ");
	fgets(Binary, sizeof(Binary), stdin);
	Binary[strlen(Binary) - 1] = '\0';	
	for(int i = strlen(Binary); i > 0; i--){
		BinaryNums[Counter][CounterChar] = Binary[i - 1];
		CounterChar++;
		if(strlen(BinaryNums[Counter]) == 3){
			strcpy(Buffer, BinaryNums[Counter]);
			for(int i = CounterChar; i > 0; i--){
				BinaryNums[Counter][CounterChar - i] = Buffer[i - 1];	
			}
			CounterChar = 0;
			Counter++;
		}
	}
	printf("%s\n", BinaryNums[0]);
	const int length = sizeof(BinaryNums[0]) / sizeof(BinaryNums[0][0]);
	for(int i = 0; length > i; i++){
		if(BinaryNums[i][0] == '\0')
			break;
		sprintf(Result + strlen(Result), "%d", toOct(BinaryNums[i]));
	}
	for(int i = strlen(Result); i > 0; i--){
		printf("%c", Result[i - 1]);
	}
	printf("\n");
	return 0;

}
