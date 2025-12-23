#include <stdio.h>
#include <string.h>

int main(){
	int DecNum;
	char HexNum[256];
	printf("Enter a number to be converted to hexadecimal: ");
	scanf("%d", &DecNum);
	
	while(DecNum != 0){
		switch(DecNum % 16){
			case 0:	sprintf(HexNum + strlen(HexNum), "%d", 0); DecNum /= 16; break;
			case 1: sprintf(HexNum + strlen(HexNum), "%d", 1); DecNum /= 16; break;
			case 2: sprintf(HexNum + strlen(HexNum), "%d", 2); DecNum /= 16; break;
			case 3: sprintf(HexNum + strlen(HexNum), "%d", 3); DecNum /= 16; break;
			case 4: sprintf(HexNum + strlen(HexNum), "%d", 4); DecNum /= 16; break;
			case 5: sprintf(HexNum + strlen(HexNum), "%d", 5); DecNum /= 16; break;
			case 6: sprintf(HexNum + strlen(HexNum), "%d", 6); DecNum /= 16; break;
			case 7: sprintf(HexNum + strlen(HexNum), "%d", 7); DecNum /= 16; break;
			case 8: sprintf(HexNum + strlen(HexNum), "%d", 8); DecNum /= 16; break;
			case 9: sprintf(HexNum + strlen(HexNum), "%d", 9); DecNum /= 16; break;
			case 10: HexNum[strlen(HexNum)] = 'A'; DecNum /= 16; break;
			case 11: HexNum[strlen(HexNum)] = 'B'; DecNum /= 16; break;
			case 12: HexNum[strlen(HexNum)] = 'C'; DecNum /= 16; break;
			case 13: HexNum[strlen(HexNum)] = 'D'; DecNum /= 16; break;
			case 14: HexNum[strlen(HexNum)] = 'E'; DecNum /= 16; break;
			case 15: HexNum[strlen(HexNum)] = 'F'; DecNum /= 16; break;
		}
	}
	printf("%s\n", HexNum);
}
