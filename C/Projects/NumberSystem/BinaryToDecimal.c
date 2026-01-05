#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(){
	char  Binary[256];
	int   Result;
	printf("Enter the binary number(max characters 256): ");
	fgets(Binary, sizeof(Binary), stdin);
	Binary[strlen(Binary) - 1] = '\0';
	const int length = strlen(Binary);
	for(int i = length; i > 0; i--){
		if(Binary[i - 1] == '1'){
			Result += pow(2, length - i) * 1;
		}
		if(Binary[i - 1] == '0'){
			Result += pow(2, length - i) * 0;
		}
	}
	printf("The result is: %d\n", Result);
	return 0;
}
