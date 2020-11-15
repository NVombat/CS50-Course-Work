#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<string.h>

int main()
{
    unsigned long long int num; //ULL int since Credit Card/Debit Card Number has 13-16 digits
    char name[15];
    int i, temp, temp1, numdig=0, check1, sum1=0, check2, sum2=0, checksum=0, dig[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    printf("Number: "); //Asks for user input of CC/DC number
    scanf("%llu", &num);

    //printf("\n%llu\n", num);

    i=16; //Set i to 16 so that we can get digits from the end of the number instead of the start (Algorithm needs checking from end)

    while(num>0)
    {
        dig[i]=num%10; //Break the number down digit by digit from the end
        //printf("Digit %d is %d\n", i, dig[i]);
        num=num/10; //Since its an integer it will only store the integer part and discard the decimal part thus making it possible to calculate the digits from right to left
        //printf("Numleft %d\n", num);
        i--; //Decrement i till it reaches 0
    }
    /*
    numdig=16-i; //Calculates number of digits
    printf("Number is \n");
    for(i=0; i<=16; i++)
    {
       printf("%d\n", dig[i]);
    }
    */

    //printf("\nNumber of Digits = %d", numdig);
    //printf("\n");

    for(i=15; i>0; i=i-2)
    {
        //printf("%d\n", dig[i]); //FIRST CHECK
        check1=((dig[i])*2); //Multiplies every alternate digit by 2, starting with the number's second-to-last digit
        if(check1<10) //If, after multiplying by 2, number is single digit then add to Sum as is (eg - 4*2 = 8)
        {
            sum1=sum1+check1; //Adds to sum
            //printf("%d is sum1", sum1);
            //printf("\n");
        }
        else //If, after multiplying by 2, number is not single digit then first add digits of number then add to Sum (eg - 9*2 = 18 => 1+8 = 9)
        {
            while(check1>0)
            {
                temp1=(check1%10); //Breaks down number into digits
                //printf("%d is temp1", temp1);
                //printf("\n");
                sum1=sum1+temp1; //Adds digits to sum
                //printf("%d is sum1", sum1);
                //printf("\n");
                check1=check1/10; //Moves from right to left one digit at a time
                //printf("%d is check1", check1);
                //printf("\n");
            }

        }
    }
    //printf("\n");
    //printf("Sum1=%d", sum1);
    //printf("\n");

    for(i=16; i>0; i=i-2) //SECOND CHECK
    {
        //printf("%d\n", dig[i]);
        sum2=sum2+dig[i]; //Adds all the digits that weren't multiplied by 2 to the sum
    }

    //printf("\n");
    //printf("Sum2=%d", sum2);
    //printf("\n");

    checksum=sum1+sum2; //VALUE OF CHECKSUM IS SUM1 + SUM2
    //printf("SumTOTAL=%d", checksum);
    //printf("\n");

    //printf("%d", dig[0]);
    //printf("\n");
    //printf("%d", dig[1]);
    //printf("\n");
    //printf("%d", dig[2]);
    //printf("\n");
    //printf("%d", dig[3]);
    //printf("\n");

    if(checksum%10==0) //If checksum is divisible by 10 number is valid
    {
        //Checks to see first and second digits of CC/DC number to tell us which company it is from
        if(dig[1]==4)
        {
            printf("VISA");
        }
        else if(dig[2]==3 && dig[3]==4)
        {
            printf("AMEX");
        }
        else if(dig[2]==3 && dig[3]==7)
        {
            printf("AMEX");
        }
        else if(dig[1]==5 && dig[2]==1)
        {
            printf("MASTERCARD");
        }
        else if(dig[1]==5 && dig[2]==2)
        {
            printf("MASTERCARD");
        }
        else if(dig[1]==5 && dig[2]==3)
        {
            printf("MASTERCARD");
        }
        else if(dig[1]==5 && dig[2]==4)
        {
            printf("MASTERCARD");
        }
        else if(dig[1]==5 && dig[2]==5)
        {
            printf("MASTERCARD");
        }
    }

    else //ERROR
    {
        printf("INVALID");
    }
    return 0;
}
