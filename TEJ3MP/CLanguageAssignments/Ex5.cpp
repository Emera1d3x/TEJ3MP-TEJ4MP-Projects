// Sehan Munir
// TEJ3MP with Mr. Wong
// 2024-04-25
// This program will tell you information about inputted string

#include <stdio.h>
#include <string.h>
char word[100];
void pauseProgram()
{
    printf("\nPress Enter key to continue...");
    getchar();
}
void intro()
{
    printf("See if you can understand strings!\n");
}
void userInput()
{
    printf("Type any word : ");
    fgets(word, sizeof(word), stdin);
    if (strlen(word)-1 < 1 || strlen(word) > 21) {
        printf("Error: Please enter a word between 1 and 20 characters!\n");
        pauseProgram();
        userInput();
    }
}
void display()
{
    int len = strlen(word) - 1;
    if (len < 5)
    {
        printf("%s is less than 5 characters long.\n", word);
    }
    else if (len % 2 != 0)
    {
        printf("%s has an odd number of letters.\n", word);
        int pos = len / 2 + 1;
        printf("The middle letter is at position %d\n", pos);
    }
    else
    {
        printf("%s has an even number of letters.\n", word);
    }
}
int main()
{
    intro();
    userInput();
    display();
    pauseProgram();
    return 0;
}
