#include <stdio.h>
#include <cs50.h>

//start of the main function
int main(void)
{
    string name = get_string("What is your name?\n");
    printf("hello, %s\n", name);
}