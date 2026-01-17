#include <stdio.h>
#include <math.h>
#include <string.h>
const char* ToBin(char Octal){
	switch(Octal){
		case '0': return "000"; break;
		case '1': return "001"; break;
		case '2': return "010"; break;
		case '3': return "011"; break;
		case '4': return "100"; break;
		case '5': return "101"; break;
		case '6': return "110"; break;
		case '7': return "111"; break;
	}
}
char ToHex(const char* Bin);
int main(){
	char Octal[256];
	char Binary[512] = "";
	char BinaryExtended[512] = "";
    char Buffer[32][64] = {0};
	char Result[64] = "";
    int  Counter = 0;
    int  ElCounter = 0;
    int  HexCounter = 0;
	printf("Enter an octal number: ");
	fgets(Octal, sizeof(Octal), stdin);
	Octal[strlen(Octal) - 1] = '\0';

	for(int i = 0; i < strlen(Octal); i++){
		strcat(Binary, ToBin(Octal[i]));
	}
	switch(strlen(Binary) % 4){
		case 0: strcat(BinaryExtended, "0000"); strcat(BinaryExtended, Binary); break;
		case 1: strcat(BinaryExtended, "000"); strcat(BinaryExtended, Binary); break;
		case 2: strcat(BinaryExtended, "00"); strcat(BinaryExtended, Binary); break;
		case 3: strcat(BinaryExtended, "0"); strcat(BinaryExtended, Binary); break;
	}
    for(int i = 0; i < strlen(BinaryExtended); i++){
        Buffer[ElCounter][Counter] = BinaryExtended[i];
        Counter++;
        if(Counter == 4){
            Counter = 0;
            ElCounter++;
        }
    }
    for(int i = 0; i < sizeof(Buffer) / sizeof(Buffer[0][0]); i++){
        if(Buffer[i][0] == '\0')
            break;
        Result[i] = ToHex(Buffer[i]);
    }
    printf("0x%s\n", Result);
}
char ToHex(const char* Bin){
    int Dec = 0;
    for(int i = 0; i < 4; i++){
        Dec += pow(2, 3 - i) * (Bin[i] - '0');
    }
    switch(Dec){
        case 0: return '0';  
        case 1: return '1';  
        case 2: return '2';  
        case 3: return '3'; 
        case 4: return '4'; 
        case 5: return '5'; 
        case 6: return '6'; 
        case 7: return '7'; 
        case 8: return '8'; 
        case 9: return '9'; 
        case 10: return 'A'; 
        case 11: return 'B'; 
        case 12: return 'C'; 
        case 13: return 'D'; 
        case 14: return 'E'; 
        case 15: return 'F'; 
    }
}
