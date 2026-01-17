#include <stdio.h>
#include <string.h>
#include <math.h>

int main(){
	int  Result = 0;
	char Input[256];
	printf("Enter any octal number: ");
	fgets(Input, sizeof(Input), stdin);
	Input[strlen(Input) - 1] = '\0';
	const int length = strlen(Input);
	for(int i = length; i > 0; i--){
		switch(Input[i - 1]){
			case '0': Result += pow(8, length - i) * 0; break;
			case '1': Result += pow(8, length - i) * 1; break;
			case '2': Result += pow(8, length - i) * 2; break;
			case '3': Result += pow(8, length - i) * 3; break;
			case '4': Result += pow(8, length - i) * 4; break;
			case '5': Result += pow(8, length - i) * 5; break;
			case '6': Result += pow(8, length - i) * 6; break;
			case '7': Result += pow(8, length - i) * 7; break;
			default: 
				  printf("Invalid octal number!\n");
				  return 1;
		}
	}
	printf("%d\n", Result);
	return 0;
}
