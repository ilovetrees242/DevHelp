#include <stdio.h>
#include <string.h>
#include <math.h>
// Convert a string to int
int toInt(const char *Num){
    int result = 0;
    const int length = strlen(Num);
    /*
     * Since we are starting from LSB, which is actually MSB, we have to use another variable as the second argument
     * Then we can just keep decrementing it as we move towards the LSB, instead of MSB
     * Example:
     * toInt("52")
     *
     * 5                    2
     * \-> Place value 10^1 \-> Place value 10^0
     *
     * Total value = Summation of Place value of every number multiplied by that number
     */
    int index = strlen(Num) - 1;
    for(int i = 0; i < length; i++){
        result += (Num[i] - '0') * pow(10, index);
        index--;
    }
    return result;
}
int main(){
    printf("Enter the numbers(seperated by space): ");
    char Numbers[256];
    char Buffer[256];
    int Numbers2[256] = {0};
    int NumCount = 0;
    int ArrangedNum[256] = {0};
    int j = 0;
    
    fgets(Numbers, sizeof(Numbers), stdin);
    // Tokenization ( parsing space )
    Numbers[strlen(Numbers) - 1] = '\0';
    for(int i = 0; i < strlen(Numbers); i++){
        if(Numbers[i] != ' '){
            Buffer[j] = Numbers[i];
            j++;
        }
        else{
            Numbers2[NumCount]=toInt(Buffer);
            j=0;
            for(int k = 0; k < strlen(Buffer); k++){
                Buffer[k]='\0';
            }
            NumCount++;
        }
        if(Numbers[i+1] == '\0'){
            Numbers2[NumCount]=toInt(Buffer);
            NumCount++;
        }
    }
    // Bubble Sort algorithm
    // 46 13 39
    // 13 46 39
    // 13 39 46
    int Bubble;
    int NBuffer;
    for(int i = 0; i < NumCount; i++){
        Bubble = Numbers2[0];
        for(int n = 0; n < NumCount - 1; n++){
            if(Bubble > Numbers2[n+1]){
                NBuffer = Bubble;
                Numbers2[n] = Numbers2[n+1];
                Numbers2[n+1] = Bubble;
            }
            else if(Bubble < Numbers2[n+1]){
                Bubble=Numbers2[n+1];
            }
        }
    }
    printf("Arranged : ");
    for(int i = 0; i < NumCount; i++){
        printf("%d ", Numbers2[i]);
    }
    printf("\n");
}
