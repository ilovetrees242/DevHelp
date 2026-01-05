#include <stdio.h>
#include <string.h>
#include <math.h>
int toDec(char *Binary){
	const int length = strlen(Binary);
	int       Result = 0;
	for(int i = length; i > 0; i--){
		if(Binary[i - 1] == '1'){
			Result += pow(2, length - i) * 1;
		}
		else if(Binary[i - 1] == '0'){
			Result += pow(2, length - i) * 0;
		}
	}
	return Result;
}
int main(){
	char Binary[256];
	int  Decimal;
	char Result[64] = "";
	printf("Enter a binary number(max characters 256): ");
	fgets(Binary, sizeof(Binary), stdin);
	Binary[strlen(Binary) - 1] = '\0';
	Decimal = toDec(Binary);

	while(Decimal != 0){
		switch(Decimal % 16){
			case 0 : sprintf(Result + strlen(Result), "%d", 0); Decimal /= 16; break;
			case 1 : sprintf(Result + strlen(Result), "%d", 1); Decimal /= 16; break;
			case 2 : sprintf(Result + strlen(Result), "%d", 2); Decimal /= 16; break;
			case 3 : sprintf(Result + strlen(Result), "%d", 3); Decimal /= 16; break;
			case 4 : sprintf(Result + strlen(Result), "%d", 4); Decimal /= 16; break;
			case 5 : sprintf(Result + strlen(Result), "%d", 5); Decimal /= 16; break;
			case 6 : sprintf(Result + strlen(Result), "%d", 6); Decimal /= 16; break;
			case 7 : sprintf(Result + strlen(Result), "%d", 7); Decimal /= 16; break;
			case 8 : sprintf(Result + strlen(Result), "%d", 8); Decimal /= 16; break;
			case 9 : sprintf(Result + strlen(Result), "%d", 9); Decimal /= 16; break;
			case 10: Result[strlen(Result)] = 'A'; Decimal /= 16; break;
			case 11: Result[strlen(Result)] = 'B'; Decimal /= 16; break;
			case 12: Result[strlen(Result)] = 'C'; Decimal /= 16; break;
			case 13: Result[strlen(Result)] = 'D'; Decimal /= 16; break;
			case 14: Result[strlen(Result)] = 'E'; Decimal /= 16; break;
			case 15: Result[strlen(Result)] = 'F'; Decimal /= 16; break;
		}
	} 
	for(int i = strlen(Result); i > 0; i--){
		printf("%c", Result[i - 1]);
	}
	printf("\n");
}
