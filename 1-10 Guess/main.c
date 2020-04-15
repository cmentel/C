#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// variable containing number of games played.
int games_played = 0;

// array containing number of guesses per game.
int play_log[5] = {};

// function to get random int between 1 and 10.
int numselect(){
    /* Uses current time as a seed for random generator */
    srand(time(0));
    /* Generates and prints 'r' random number in range 1-10*/
    int r = (rand() % 10) + 1;
    return r;
}
// main function to run the game.
int main() {
    int r = numselect();
    int guess;

    printf("Please guess a number from 1 - 10.\n");
    int guess_counter = 0;
    while (games_played < 5){
        scanf("%d",&guess);
        printf("You guessed %d\n",guess);
        if (guess >= 1 && guess < 11){
            if (guess == r){
                guess_counter ++;
                games_played ++;
                // adds the number of guesses for respective game to play_log
                play_log[games_played] = guess_counter;
                printf("Congratulations! You guessed the number %d!\n",r);
                main();
            }

            else if (guess > r){
                guess_counter ++;
                printf("Guess lower!\n");
                continue;
            }

            else{
                guess_counter ++;
                printf("Guess higher!\n");
                continue;
            }

        }
        else{
            printf("Please enter a number between 1 and 10.\n");
            continue;

        }
        return 0;

    }
    int i = 1;
    games_played = 0;
    while (i < 6){
        printf("Game %d took you %d guess(es)\n", games_played + i, play_log[i]);
        i ++;
    }

}
