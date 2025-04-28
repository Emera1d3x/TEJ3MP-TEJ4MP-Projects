/*
    Sehan Munir
    TEJ3MP - Mr. Wong
    2024-04-39
    This program simulates a guess gaming
*/

// Imports
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//  Declaration Section
int num;
int guess;
int amountGuesses = 3;
bool win = false;

// Function That Pauses Program
void pauseProgram()
{
    printf("\nPress any key to continue...");
    getchar();
}

//  Function Title
void title(const char * programTitle)
{
    int len = strlen(programTitle);
    printf("\e[1;1H\e[2J");
    printf("\n");
    for(int i=1;i< 40 - len/2; i++)  printf(" ");
    printf("%s\n", programTitle);
}

//  Function For User Input
void userInput()
{
    title("Random Number");
    printf("\nGuess the Number!");
    printf("\nYou have (%d) number of guesses. Enter a number between 1 and 100 : ", amountGuesses);
    scanf("%d", &guess);
    getchar();
}
// Function For Creating A Random Number
void createRandomNum(){
    unsigned int iseed = (unsigned int)time(NULL);
    srand (iseed);
    num = rand() % 100 + 1;
}
//  Function For Display
void display()
{
    title("Random Number");
    if ( guess > num)
        printf("\nCome down!\n");
    else if (guess < num)
        printf("\nWay down there?\n");
    else {
        printf("\nRight on!\n");
        win = true;
    }
    amountGuesses = amountGuesses-1;
    pauseProgram();
}
// Function For Goodbye Message
void goodbye(){
    if (win)
        printf("\nGood job!\n");
    else {
        printf("\nTry next time... Answer was: %d\n",num);
    }
}
//  Main Program
int main()
{
    createRandomNum();
    do
    {
        userInput();
        display();
    }  while (amountGuesses!=0&&guess!=num);   // Loop while game may still play
    goodbye();
}
