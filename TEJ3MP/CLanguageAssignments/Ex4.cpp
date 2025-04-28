#include <stdio.h>
#include <math.h> // header files needed for Math functions
double num; // global variable
double num2;
// Function Title
void title()
{
    printf("\n%30sMore Math Functions\n","");
}
// function spacing – create a number of blank lines, and then a number of spaces based on calling arguments
void spacing(int numOfLines, int numOfSpaces)
{
    for (int x=0;x<numOfLines;x++)
        printf("\n");
    for (int x=0;x<numOfSpaces;x++)
        printf(" ");
}
// function intro
void intro()
{
    title();
    spacing(0, 5);
    printf("This program demonstrates two new Math functions that are very useful!");
}
// function userInput
void userInput()
{
    spacing(2, 0);
    printf("Enter a real number: ");
    scanf("%lf", &num);
    spacing(1, 0);
    printf("Enter a real number: ");
    scanf("%lf", &num2);
    getchar(); // to get rid of the Enter character
}
// function display
void display()
{
    double answer;
    spacing(3, 30);
    answer = round(num);
    printf("%lf is rounded as %lf\n", num, answer);
    spacing(1, 30);
    printf("%lf square rooted is %lf\n", num, sqrt(num));
    spacing(1, 30);
    printf("%lf to the power of %lf is %lf\n", num, num2, pow(num,num2)); // don’t need the variable answer if just for display
    spacing(1, 30);
    printf("%lf to the ceiling is %lf\n", num, ceil(num));
}
// main program
int main()
{
    intro();
    userInput();
    display();
}