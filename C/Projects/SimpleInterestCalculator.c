#include <stdio.h>
int main(){
	int Principal;
	int Time;
	int Rate; 
	int SimpleInterest = 1;
	printf("Enter the principal amount: ");
	scanf("%d", &Principal);
	printf("Enter the time in years: ");
	scanf("%d", &Time);
	printf("Enter the rate (no percentage sign): ");
	scanf("%d", &Rate);
	SimpleInterest = (Principal * Rate * Time) / 100;
	printf("Simple Interest = %d\n", SimpleInterest);
	return 0;
}
