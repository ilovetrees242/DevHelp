#include <stdio.h>
#include <string.h>
const char* ToBin(char Octal){
	switch(Octal){
		case '0': return "000";
		case '1': return "001";
		case '2': return "010";
		case '3': return "011";
		case '4': return "100";
		case '5': return "101";
		case '6': return "110";
		case '7': return "111";
	}
}
int main(){
	char Octal[64];
	char Binary[256] = "";
	printf("Enter any octal number: ");
	fgets(Octal, sizeof(Octal), stdin);
	Octal[strlen(Octal) - 1] = '\0';
	for(int i = 0; i < strlen(Octal); i++){
		strcat(Binary, ToBin(Octal[i]));
	}
	printf("%s\n", Binary);
}
