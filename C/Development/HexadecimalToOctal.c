#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
char ToOctal(const char *Binary ){
    int Octal = 0;
    for(int i = 0; i < strlen(Binary); i++){
        Octal += pow(2, (strlen(Binary) - 1) - i)  * (Binary[i] - '0');
    }
    return Octal + '0';
}
const char* ToBin(char Hex){
    switch(Hex){
        case '0': return "0000"; break;
        case '1': return "0001"; break;
        case '2': return "0010"; break;
        case '3': return "0011"; break;
        case '4': return "0100"; break;
        case '5': return "0101"; break;
        case '6': return "0110"; break;
        case '7': return "0111"; break;
        case '8': return "1000"; break;
        case '9': return "1001"; break;
        case 'A': return "1010"; break;
        case 'B': return "1011"; break;
        case 'C': return "1100"; break;
        case 'D': return "1101"; break;
        case 'E': return "1110"; break;
        case 'F': return "1111"; break;
    }
}
int main(){
    char Hex[256];
    char Binary[1028] = "";
    char BinaryExtended[1028] = "";
    char Octal[256][16] = {0};
    char Buffer[4];
    int Counter1 = 0;
    int Counter2 = 0;
    char Result[64] = {0};
    printf("Enter any hex number: ");
    fgets(Hex, sizeof(Hex), stdin);
    Hex[strlen(Hex) - 1] = '\0';

    for(int i = 0; i < strlen(Hex); i++){
        strcat(Binary, ToBin(Hex[i]));
    }

    switch(strlen(Binary) % 3){
        case 0: strcat(BinaryExtended, "000"); strcat(BinaryExtended, Binary); break;
        case 1: strcat(BinaryExtended, "00"); strcat(BinaryExtended, Binary);  break;
        case 2: strcat(BinaryExtended, "0"); strcat(BinaryExtended, Binary);   break;
    }
    for(int i = 0; i < strlen(BinaryExtended); i++){
        Octal[Counter2][Counter1] = BinaryExtended[i];
        Counter1++;
        if(Counter1 == 3){
            Counter1 = 0;
            Counter2++;
        }
    }
    for(int i = 0; i < sizeof(Octal) / sizeof(Octal[0]); i++){
        if(Octal[i][0] == '\0'){
            break;
        }
        Result[i] = ToOctal(Octal[i]);
    }
    printf("Result: %s\n", Result);
}
