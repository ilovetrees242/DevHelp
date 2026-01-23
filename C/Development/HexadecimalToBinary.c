#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
const char* ToBin(char Hex){
    switch(Hex){
        case '0': return "0000";
        case '1': return "0001";
        case '2': return "0010";
        case '3': return "0011";
        case '4': return "0100";
        case '5': return "0101";
        case '6': return "0110";
        case '7': return "0111";
        case '8': return "1000";
        case '9': return "1001";
        case 'A': return "1010";
        case 'B': return "1011";
        case 'C': return "1100";
        case 'D': return "1101";
        case 'E': return "1110";
        case 'F': return "1111";
    }
}
int main(){
    char Hex[256];
    char Binary[1028] = "";
    printf("Enter any hex number: ");
    fgets(Hex, sizeof(Hex), stdin);
    Hex[strlen(Hex) - 1] = '\0';
    for(int i = 0; i < strlen(Hex); i++){
        strcat(Binary, ToBin(Hex[i]));
    }
    printf("Result: %s\n", Binary);
}
