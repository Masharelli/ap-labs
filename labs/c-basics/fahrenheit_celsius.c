#include <stdio.h>
#include <stdlib.h>


#define   LOWER  0       /* lower limit of table */
#define   UPPER  300     /* upper limit */
#define   STEP   10      /* step size */

int main(int argc, char** argv)
{
    /* code */
    if (argc == 2)
    {
        int farenheit = atoi(argv[1]);
        printf("Farenheit: %3i,  Celsius: %3.1f\n",farenheit,(5.0/9.0)*(farenheit-32.0));
        return 0;
    }else{
        for (int i = atoi(argv[1]); i < atoi(argv[2]); i+= atoi(argv[3])+ STEP)
        {
            printf("Farenheit: %3i  Celsius: %3.1f\n",i,(5.0/9.0)*(i-32.0));
        }
        
    }
}