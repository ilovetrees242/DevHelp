#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]){
    if(argc < 2){
        printf("%s: Missing file operand\n", argv[0]);
    }
    else{
        FILE *fptr;
        fptr = fopen(arv[1], "w");
        printf("%s\n", argv[1]);
    }
    return 0;
}
