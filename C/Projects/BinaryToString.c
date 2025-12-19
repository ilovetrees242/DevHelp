#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


int BinToDec(char *Bin){
	const int length = strlen(Bin);
	int DecNum = 0;
	int Status = 0;
	for(int i = 0; i < length; i++){
		if(Bin[i] != '0' && Bin[i] != '1'){
			printf("ERROR: Number is not binary. Program will not run.\n");
			Status = 1;
			break;
		}
	}
	if(Status == 0){
		for(int i = length; i > 0; i--){
			if(Bin[i - 1] == '1'){
				DecNum += pow(2, length - i) * 1;
			}
			else if(Bin[i - 1] == '0'){
				DecNum += pow(2, length - i) * 0;
			}
		}
	}
	return DecNum;
}
int main(){
	char BinData[2056];
	char BinArray[512][128] = {0};
	int  Counter1 = 0;
	int  Counter2 = 0;
	char Character;

	printf("Enter some binary data seperated with spaces: ");
	fgets(BinData, sizeof(BinData), stdin);
	BinData[strlen(BinData) - 1] = '\0';
	for(int i = 0; i < strlen(BinData); i++){
		if(BinData[i] == ' '){
			Counter1++;
			Counter2 = 0;
		}
		else{
			BinArray[Counter1][Counter2] = BinData[i];
			Counter2++;
		}
	}
	printf("Heres the result, but wait, I will check your input first\n");
	for(int i = 0; i < sizeof(BinArray) / sizeof(BinArray[0]); i++){
		for(int j = 0; j < strlen(BinArray[i]); j++){
			if( BinArray[i][j] != '0' && BinArray[i][j] != '1'){
				printf("Your number is not binary!\n");
				return 1;
				break;
			}
		}
		if(BinArray[i][0] == '\0')
			break;
	}
	printf("Okay, you're good to go: ");	
	for(int i = 0; i < sizeof(BinArray) / sizeof(BinArray[0]); i++){
		if(BinArray[i][0] == '\0')
			break;
		else{
			Character = BinToDec(BinArray[i]);
			printf("%c", Character);
		}
	}
	printf("\n");
}
