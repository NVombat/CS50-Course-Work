#include<stdio.h>
#include<math.h>

//For a given amount of change - Least number of coins required
int main()
{
    float cng; //cng = Change
    int coin[4]={25,10,5,1}; //Array of different value coins (25c, 10c, 5c, 1c)
    int change[4]={0,0,0,0}; //Array with number of each type of coins needed
    int i, rcng, sum;

    printf("Change owed (in dollars): "); //Accepts Input in dollars
    scanf("%f", &cng);

    rcng=round(cng*100); //rounds change in cents

    sum=0;

    for(i=0; i<=3; i++)
    {
        if(rcng>=coin[i]) //Goes from largest value to smallest value checking if change owed is more than current denomination of coin
        {
            change[i]=(rcng/coin[i]); //Adds number of coins of that denomination to change array
            rcng=rcng-(coin[i]*change[i]); //Subtracts amount from change owed - Updates change owed
            sum=sum+change[i]; //Updates total number of coins
        }
    }
    printf("%d\n", sum);

    return 0;
}
