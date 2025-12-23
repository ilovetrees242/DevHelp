#include <stdio.h>
#include <string.h>

int main(){
	int DecNum = 0;
	char Octal[256];
	printf("Enter a decimal number: ");
	scanf("%d", &DecNum);
	while(DecNum != 0){
		sprintf(Octal + strlen(Octal), "%d", DecNum % 8);
		DecNum /= 8;
	}
	for(int i = strlen(Octal); i > 0; i--){
		printf("%c", Octal[i - 1]);
	}
	printf("\n");
}
