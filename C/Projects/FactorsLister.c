#include <stdio.h>

int main(){
	int Num;
	printf("Enter a number: ");
	scanf("%d", &Num);
	
	printf("Factors are: ");
	for(int i = 1; i < Num; i++){
		if(Num % i == 0){
			printf("%d ", i);
		}
	}
	printf("\n");
}
