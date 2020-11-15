#include<stdio.h>

//Prints Mario Pyramids
int main()
{
    int i, j, h;

    printf("Height: "); //Asks User for height input for height of pyramid
    scanf("%d", &h);

    for(i=0; i<=h; ++i)
    {
        j=0;
        while(j<h-i)
        {
            printf(" "); //Since it starts at the midpoint and moves outward - decreasing number of spaces will be printed
            j++;
        }
        j=0;
        while(j<i)
        {
            printf("#"); //Increasing number of # will be printed
            j++;
        }
        printf("  ");

        j=0;
        while (j<i)
        {
            printf("#"); //For opposite side just print # starting with 1 and incrementing number of # by 1 as we go to each new line
            j++;
        }
        printf("\n"); //New line
    }
        return 0;
}
