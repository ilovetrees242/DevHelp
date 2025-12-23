#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* DecToBin(int DecNum){
	char *BinNum = malloc(33 * sizeof(char));
	char *result = malloc(33 * sizeof(char));
	while(DecNum != 0){
		if(DecNum % 2 == 0){
			sprintf(BinNum + strlen(BinNum), "%d", DecNum % 2);
			DecNum /= 2;
		}
		else if(DecNum % 2 == 1){
			sprintf(BinNum + strlen(BinNum), "%d", DecNum % 2);
			DecNum /= 2;
		}
	}
	const int length = strlen(BinNum);
	for(int i = length; i > 0; i--){
		result[length - i] = BinNum[i - 1]; 
	}
	return result;
	free(BinNum);
	free(result);
}
int main(){
	char Text[512] = "";
	int CharBuffer;
	int Counter = 0;
	printf("Enter any text (max characters 512): ");
	fgets(Text, sizeof(Text), stdin);
	Text[strlen(Text) - 1] = '\0';
	for(int i = 0; i < strlen(Text); i++){
		CharBuffer = Text[i];
		printf("%-8s ", DecToBin(CharBuffer));
		Counter++;
		if(Counter == 5){
			Counter = 0;
			printf("\n");
		}
	}
	printf("\n");
	return 0;
}
