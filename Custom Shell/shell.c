#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <signal.h>
#include <time.h>

#define BUFFER_SIZE 80
#define RUNNING 0

int gamesPlayed = 0;
int playLog[5] = {};

/**
 * Signal handler function for when ctrl+c is called.
 * @param sig the signal to be passed into the shell.
 */
void controlCHandler(int sig) {
    printf("\nmini-shell terminated.\n");
    exit(0);
}

/**
 * Function to get a random integer for the game function.
 * @return the random number to be used for the game.
 */
int getRandomInt() {
    /* Uses current time as a seed for random generator */
    srand(time(0));
    /* Generates and prints 'r' random number in range 1-10*/
    int r = (rand() % 10) + 1;
    return r;
}

/**
 * Function to run the guessing game from the shell.
 */
void game() {
    int r = getRandomInt();
    int guess;

    printf("Please guess a number from 1 - 10.\n");
    int guess_counter = 0;
    while (gamesPlayed < 5) {
        scanf("%d", &guess);
        printf("You guessed %d\n", guess);
        if (guess >= 1 && guess < 11) {
            if (guess == r) {
                guess_counter++;
                gamesPlayed++;
                // adds the number of guesses for respective game to playLog
                playLog[gamesPlayed] = guess_counter;
                printf("Congratulations! You guessed the number %d!\n", r);
                game();
            } else if (guess > r) {
                guess_counter++;
                printf("Guess lower!\n");
                continue;
            } else {
                guess_counter++;
                printf("Guess higher!\n");
                continue;
            }

        } else {
            printf("Please enter a number between 1 and 10.\n");
            continue;

        }
        return;

    }
    int i = 1;
    gamesPlayed = 0;
    while (i < 6) {
        printf("Game %d took you %d guess(es)\n", gamesPlayed + i, playLog[i]);
        i++;
    }
}

/**
 * Function to perform the given commands in the args parameter.
 * @param argc number of arguments
 * @param args char pointer to the individual arguments.
 * @param flag specifies whether or not to perform in a background process.
 */
void perform(int argc, char **args, int flag) {
    // If no arguments passed in.
    if (argc < 1) {
        return;
    }

    // Create a char pointer for the arguments
    char *cmd = args[0];

    // if the command is EXIT, exit.
    if (strcmp(cmd, "exit") == 0) {
        exit(0);
    }

    // if the command is CD, change directories.
    if (strcmp(cmd, "cd") == 0) {

        // Gets current directory name.
        char *directory = args[1];

        // Changes directory.
        chdir(directory);
        return;
    }

    // if the command is GAME, plays the number guessing game.
    if (strcmp(cmd, "game") == 0) {
        game();
        return;
    }

    // if the command is HELP, prints out all possible options for shell.
    if (strcmp(cmd, "help") == 0) {
        printf("ls   - list files in current directory.\n"
               "cd   - Changes directory.\n"
               "game - Plays number guessing game.\n"
               "exit - Exits shell.\n");
        return;
    }


    int cpid;

    // Assigns the CPID to the fork process of the parent.
    if ((cpid = fork())) {

        // If process should be executed in background.
        if (flag == 1) {
            return;
        }

        int status;

        // Reports the status of child process specified by pid.
        waitpid(cpid, &status, 0);

        // Will return a nonzero value if the child process terminated normally with exit or _exit.
        if (WIFEXITED(status) > 0) {
        }
    }

        // Else if creation of a child process was unsuccessful.
    else {

        // The created child process does not have to run the same program as the parent process.
        execvp(cmd, args);

        // If no command identified or valid.
        printf("mini-shell> Command not found--Did you mean something else?\n");
        exit(1);
    }
}

/**
 * Function to copy the arguments from array into another array.
 * @param dest holder for the end of the array.
 * @param src the start of the array of arguments.
 * @param start starting index.
 * @param end ending index.
 */
void copyArgs(char **dest, char **src, int start, int end) {
    if (start >= end) {
        return;
    }

    int finalArgumentIndex = end - start;
    for (int indexCounter = 0; indexCounter < finalArgumentIndex; ++indexCounter) {
        dest[indexCounter] = src[start + indexCounter];
    }

    dest[finalArgumentIndex] = NULL;
}

/**
 * Function to read and perform the given command incorporating the "|".
 * @param smallCommand the char pointer that represents the command.
 */
void readAndPerform(char *smallCommand) {

    // Commands passed in are separated by spaces.
    const char *separator = " ";

    // Token variable declaration
    char *token;

    // Get the first token
    token = strtok(smallCommand, separator);

    // Char array of Buffer Size
    char *arrayOfArguments[BUFFER_SIZE];
    arrayOfArguments[0] = token;

    // Collect the remaining tokens into an array
    int tokensAsArrayInt = 0;

    // While there is an argument / char in the form of token, read and perform per separator.
    while (token != NULL) {
        token = strtok(NULL, separator);
        arrayOfArguments[++tokensAsArrayInt] = token;
    }


    bool performAdditionalCommand = false;

    // Looping through arguments starting at 1 instead of 0 because 0 is initial command.
    for (int loopHolder = 1; loopHolder < tokensAsArrayInt; ++loopHolder) {

        // Declare the command after the holder.
        int commandAfterHolder = loopHolder + 1;

        // If delineator present, perform and then do command after.
        if (strcmp(arrayOfArguments[loopHolder], "|") == 0) {
            performAdditionalCommand = true;

            // Does the command before '|'
            char *cmdBeforeOp[loopHolder + 1];
            copyArgs(cmdBeforeOp, arrayOfArguments, 0, loopHolder);
            perform(loopHolder, cmdBeforeOp, RUNNING);
            break;
        }
    }

    // If there is no additional command designated by the "|", perform as normal.
    if (!performAdditionalCommand) {
        perform(tokensAsArrayInt, arrayOfArguments, RUNNING);
    }
}

/**
 * Function to read and perform the copy of arrays from main.
 * @param bigCommand the char pointer representing the bigCommand.
 */
void readAndPerformMain(char *bigCommand) {
    // Declare variables
    const char *newLine = "\n";
    char *individualArguments;
    char *args[BUFFER_SIZE];

    // Get the first individualArgument(s)
    int readAndPerformMainCounter = 0;

    // Breaks string 'bigCommand' into a series of tokens using char* newLine.
    individualArguments = strtok(bigCommand, newLine);

    // Increment the readAndPerformMainCounter
    args[readAndPerformMainCounter++] = individualArguments;

    // Collect the remaining tokens into an array
    while (individualArguments != NULL) {

        // Breaks string NULL into a series of tokens using char* newLine.
        individualArguments = strtok(NULL, newLine);

        // Increment the readAndPerformMainCounter
        args[readAndPerformMainCounter++] = individualArguments;
    }

    // Parse for operators and perform
    for (int paeCounterJ = 0; paeCounterJ < readAndPerformMainCounter; ++paeCounterJ) {

        readAndPerform(args[paeCounterJ]);
    }
}

/**
 * Main function to read command line arguments and create loop running the shell from the command line.
 * @param argc the int arg value.
 * @param argv the arguments passed into the shell.
 * @return dummy return value.
 */
int main(int argc, char *argv[]) {
    // Checks for signal handler before loop.
    signal(SIGINT, controlCHandler);

    // Treating and opening devices as files to provide access to the keyboard and screen.
    // Assigning standard input	stdin to be the Keyboard.
    FILE *commandLineArguments = stdin;

    // If "one" argument passed in then have the shell print the "mini-shell>" identifier.
    if (argc == 1) {
        // Reading from stdin
        printf("mini-shell> ");

        // Clears/flushes the output buffer and moves the data to console.
        fflush(stdout);

    } else if (argc > 1) {
        // Reads the first argument from command line and assigns it.
        commandLineArguments = fopen(argv[1], "r");
    }

    // Declares the char array
    char commandArray[BUFFER_SIZE];

    // Reads each line and executes
    while (fgets(commandArray, BUFFER_SIZE, commandLineArguments) != NULL) {
        // Checks for signal handler at every loop.
        signal(SIGINT, controlCHandler);
        readAndPerformMain(commandArray);

        if (argc == 1) {
            printf("mini-shell> ");
        }
    }

    return 0;
}
