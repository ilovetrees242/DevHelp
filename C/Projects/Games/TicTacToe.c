#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
char Grid[3][13] = {
    "   |   |   \n",
    "- -+- -+- -\n",
    "   |   |   \n"
};
int compscore = 0;
int userscore = 0;
void clearGrid(){
    for(int i = 0; i <= 2; i++){
        for(int j = 1; j <= 9; j += 4){
            Grid[i][j] = ' ';
        }
    }
}
void printGrid(){
    printf("%s", Grid[0]);
    printf("%s", Grid[1]);
    printf("%s", Grid[2]);
}
void clearlog(){
    for(int i = 8; i < 28; i++){
        printf("\e[%d;0H", i);
        printf("                                     \n");
    }
    printf("\e[u");
}
void askagain(){
    char choice;
    printf("Your score: %d\n", userscore);
    printf("Computer's score: %d\n", compscore);
    printf("Play again?[y/n]: ");
    scanf(" %c", &choice);
    if(choice == 'y'){
        clearGrid();
        return;
    }
    else if(choice == 'n'){
        printf("Goodbye!\n");
        exit(0);
    }
    else{
        printf("Not a valid choice!\n"); exit(1);
    }
}
bool checkiftie(){
    for(int i = 0; i <= 2; i++){
        for(int j = 1; j <= 9; j += 4){
            if(Grid[i][j] == ' '){
                return false;
            }
        }
    }
    printf("\e[4;0H");
    printGrid();
    printf("\e[8;0H");
    printf("Tie!\n");
    return true;
}
// O O O
// O O O
// O O O
void checkifcompwon(){
    printf("\e[4;0H");
    printGrid();
    printf("\e[8;0H");
    if(Grid[0][1] == 'X' && Grid[0][5] == 'X' && Grid[0][9] == 'X'){ printf("\nComputer wins!\n"); compscore++; askagain(); }
    else if(Grid[1][1] == 'X' && Grid[1][5] == 'X' && Grid[1][9] == 'X'){ printf("\nComputer wins!\n"); compscore++; askagain(); }
    else if(Grid[2][1] == 'X' && Grid[2][5] == 'X' && Grid[2][9] == 'X'){ printf("\nComputer wins!\n"); compscore++; askagain(); }
    else if(Grid[0][1] == 'X' && Grid[1][5] == 'X' && Grid[2][9] == 'X'){ printf("\nComputer wins!\n"); compscore++; askagain(); }
    else if(Grid[0][9] == 'X' && Grid[1][5] == 'X' && Grid[2][1] == 'X'){ printf("\nComputer wins!\n"); compscore++; askagain(); }
    else if(Grid[0][1] == 'X' && Grid[0][5] == 'X' && Grid[0][9] == 'X'){ printf("\nComputer wins!\n"); compscore++; askagain(); }
    else if(Grid[0][5] == 'X' && Grid[1][5] == 'X' && Grid[2][5] == 'X'){ printf("\nComputer wins!\n"); compscore++; askagain(); }
    else if(Grid[1][1] == 'X' && Grid[1][5] == 'X' && Grid[1][9] == 'X'){ printf("\nComputer wins!\n"); compscore++; askagain(); }
}
void checkifplayerwon(){
    printf("\e[4;0H");
    printGrid();
    printf("\e[8;0H");
    if(Grid[0][1] == 'O' && Grid[0][5] == 'O' && Grid[0][9] == 'O'){ printf("You win!\n"); userscore++; askagain(); }
    else if(Grid[1][1] == 'O' && Grid[1][5] == 'O' && Grid[1][9] == 'O'){ printf("\nYou win!\n"); userscore++; askagain(); }
    else if(Grid[2][1] == 'O' && Grid[2][5] == 'O' && Grid[2][9] == 'O'){ printf("\nYou win!\n"); userscore++; askagain(); }
    else if(Grid[0][1] == 'O' && Grid[1][5] == 'O' && Grid[2][9] == 'O'){ printf("\nYou win!\n"); userscore++; askagain(); }
    else if(Grid[0][9] == 'O' && Grid[1][5] == 'O' && Grid[2][1] == 'O'){ printf("\nYou win!\n"); userscore++; askagain(); }
    else if(Grid[0][1] == 'O' && Grid[0][5] == 'O' && Grid[0][9] == 'O'){ printf("\nYou win!\n"); userscore++; askagain(); }
    else if(Grid[0][5] == 'O' && Grid[1][5] == 'O' && Grid[2][5] == 'O'){ printf("\nYou win!\n"); userscore++; askagain(); }
    else if(Grid[0][1] == 'O' && Grid[1][1] == 'O' && Grid[2][1] == 'O'){ printf("\nYou win!\n"); userscore++; askagain(); }
    else if(Grid[0][9] == 'O' && Grid[1][9] == 'O' && Grid[2][9] == 'O'){ printf("\nYou win!\n"); userscore++; askagain(); }
}
bool checkifoccupied(int location){
    if(location > 9){
        printf("You cannot do that!\n");
        exit(1);
    }
    switch(location){
        case 1: if(Grid[0][1] == ' '){ return false; }else{ return true; } break;
        case 2: if(Grid[0][5] == ' '){ return false; }else{ return true; } break;
        case 3: if(Grid[0][9] == ' '){ return false; }else{ return true; } break;
        case 4: if(Grid[1][1] == ' '){ return false; }else{ return true; } break;
        case 5: if(Grid[1][5] == ' '){ return false; }else{ return true; } break;
        case 6: if(Grid[1][9] == ' '){ return false; }else{ return true; } break;
        case 7: if(Grid[2][1] == ' '){ return false; }else{ return true; } break;
        case 8: if(Grid[2][5] == ' '){ return false; }else{ return true; } break;
        case 9: if(Grid[2][9] == ' '){ return false; }else{ return true; } break;
    }
}
void toX(int location){
    if(location > 9){
        printf("You cannot do that!\n");
        exit(1);
    }
    switch(location){
        case 1: Grid[0][1] = 'X'; break;
        case 2: Grid[0][5] = 'X'; break;
        case 3: Grid[0][9] = 'X'; break;
        case 4: Grid[1][1] = 'X'; break;
        case 5: Grid[1][5] = 'X'; break;
        case 6: Grid[1][9] = 'X'; break;
        case 7: Grid[2][1] = 'X'; break;
        case 8: Grid[2][5] = 'X'; break;
        case 9: Grid[2][9] = 'X'; break;
    }
}
void toO(int location){
    if(location > 9){
        printf("You cannot do that!\n");
        exit(1);
    }
    switch(location){
        case 1: Grid[0][1] = 'O'; break;
        case 2: Grid[0][5] = 'O'; break;
        case 3: Grid[0][9] = 'O'; break;
        case 4: Grid[1][1] = 'O'; break;
        case 5: Grid[1][5] = 'O'; break;
        case 6: Grid[1][9] = 'O'; break;
        case 7: Grid[2][1] = 'O'; break;
        case 8: Grid[2][5] = 'O'; break;
        case 9: Grid[2][9] = 'O'; break;
    }

}
int main(){
    srand(time(NULL));
    char choice;
    char  choice2;
    bool USEROCCUPIED;
    bool TIE;
    system("clear");
    printf("Tic Tac Toe!!! Play now!!\n");
    printf("Would you like to go first? [y/n]: ");
    scanf("%c", &choice);

    if(choice == 'y'){
        while(true){
            printf("\e[s");
            printf("The current state: \n");
            printGrid();   
            printf("Enter a location. 0 to exit(1-9): ");
            scanf(" %c", &choice2); 
            choice2 -= '0';
            TIE = checkiftie();
            if(TIE){
                askagain();
            }
            if(choice2 == 0){
                printf("Goodbye!\n");
                exit(0);
            }
            else if(choice2 < 10){
                bool OCCUPIED = checkifoccupied(choice2);
                USEROCCUPIED=OCCUPIED;
                if(OCCUPIED && !TIE){
                    printf("That location is already occupied!");
                    printf("\033[u");
                }
                else{       
                    toO(choice2);
                    checkifplayerwon();
                    printf("\033[u");
                    clearlog();
                }
            }
            else{
                printf("Not a valid choice!\n");
                exit(1);
            }
            if(!USEROCCUPIED){
                while(true){
                    TIE = checkiftie();
                    if(TIE){
                        askagain();
                    }
                    int complocation = (rand() % 9) + 1;
                    bool OCCUPIED = checkifoccupied(complocation);
                    if(!OCCUPIED){
                        toX(complocation);
                        checkifcompwon();
                        printf("\e[u");
                        break;
                    }
                }
            }
        }
    }
    else if(choice == 'n'){
        // this is left but i will do it later.
    }
    else{
        printf("Not a valid choice!\n");
        return 1;
    }
    return 0;
}
