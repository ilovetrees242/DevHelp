#include <stdio.h>
#include <string.h>
int main(){

	int DecNum;
	char BinaryNum[128] = "";

	printf("Enter a decimal number: ");
	scanf("%d", &DecNum);
	
	while(DecNum != 0){
		if(DecNum % 2 == 1){
			sprintf(BinaryNum + strlen(BinaryNum), "%d", 1);
			DecNum /= 2;
		}
		else if(DecNum % 2 == 0){
			sprintf(BinaryNum + strlen(BinaryNum), "%d", 0);
			DecNum /= 2;
		}
	}
	printf("%s\n", BinaryNum);
}
