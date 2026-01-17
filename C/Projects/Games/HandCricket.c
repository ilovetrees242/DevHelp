#include <stdio.h>
#include <time.h>
#include <stdlib.h>
int main(){
    int runs;
    int playerRuns;
    int CompRuns;
    srand(time(NULL));
    while(true){
        printf("Enter your runs(1 - 6): ");
        scanf("%d", &runs);
        printf("runs: %d\n", runs);
        if(runs > 6){
            printf("Runs cant be greater than 6!\n");
            return 1;
        }
        if(runs == 0){
            printf("Runs cant be 0!\n");
            return 1;
        }
        CompRuns = (rand() % 6) + 1;
        if(CompRuns == runs){
            printf("You're out! Computer chose %d runs.\n", CompRuns);
            printf("Your runs were: %d\n", playerRuns);
            return 0;
        }
        else{
            playerRuns += runs;
            printf("Your runs: %d\n", playerRuns);
            printf("Computer runs: %d\n", CompRuns);
        }
    }
    return 0;
}
