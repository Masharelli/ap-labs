 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int mystrlen(char *str);
char *mystradd(char *origin, char *addition);
int mystrfind(char *origin, char *substr);

int main(int argc, char *argv[])
{

    if (argc < 3)
    {
        printf("Not enought arguments, please provide the main string then the string to add and finally the substring to search.\n");
    }
    else
    {
        if (mystrlen(argv[1]) < mystrlen(argv[3]))
        {
            printf("The substring to search can not be bigger than the main string");
        }
        else
        {
            int initialLength = mystrlen(argv[1]);
            char *newString = mystradd(argv[1], argv[2]);
            int found = mystrfind(newString, argv[3]);

            printf("Initial Lenght      : %d\n", initialLength);
            printf("New String          : %s\n", newString);
            if (found == 1)
            {
                printf("SubString was found : yes\n");
            }
            else
            {
                printf("SubString was found : no\n");
            }
        }
    }

    return 0;
}