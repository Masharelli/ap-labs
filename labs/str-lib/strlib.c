#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int mystrlen(char *str)
{
    int i = 0;
    int size = 0;
    while (str[i] != NULL)
    {
        size++;
        i++;
    }
    return size;
}

char *mystradd(char *origin, char *addition)
{
    char *newStr = malloc(mystrlen(origin) + mystrlen(addition));
    int size1 = mystrlen(origin);
    int size2 = mystrlen(addition);
    for (int i = 0; i < size1; i++)
    {
        newStr[i] = origin[i];
    }

    int i = 0;
    for (int j = size1; j < size2 + size1; j++)
    {
        newStr[j] = addition[i];
        i++;
    }
    return newStr;
}

int mystrfind(char *origin, char *substr)
{
    int start = 0;
    int found;
    for (int i = 0; i < mystrlen(origin); i++)
    {
        found = 1;
        int y = i;
        for (int j = 0; j < mystrlen(substr); j++)
        {
            if (origin[y] != substr[j] || origin[y] == NULL)
            {
                found = 0;
                break;
            }
            y++;
        }
        if (found == 1)
        {
            return 1;
        }
    }
    return 0;
}
