#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

//FUNCTION DECLARATION
int letters(int, char[]);
int words(int, char[]);
int sentences(int, char[]);

int main()
{
    char str[500];
    int length, let, wor, sent, rind;
    float L, S, ind;

    printf("Enter String: "); //Inputs string to be assessed by the test
    gets(str);
    //puts(str);
    //printf("\n");

    //LENGTH OF STRING
    length=strlen(str);
    //printf("Length = %d", length);
    //printf("\n");

    //LETTERS, WORDS, SENTENCES
    let=letters(length, str); //calculates number of letters
    wor=words(length, str); //calculates number of words
    sent=sentences(length, str); //calculates number of sentences

    //printf("Letters = %d", let);
    //printf("\n");
    //printf("Words = %d", wor);
    //printf("\n");
    //printf("Sentences = %d", sent);
    //printf("\n");

//CALCULATE COLEMAN-LIAU INDEX
//index = 0.0588 * L - 0.296 * S - 15.8
//L is the average number of letters per 100 words
//S is the average number of sentences per 100 words

    L=((float)let/(float)wor)*100;
    S=((float)sent/(float)wor)*100;

    ind=(0.0588*L) - (0.296*S) - 15.8; //Index
    rind=round(ind); //Rounding number of to a whole number

    //printf("Index = %.2f", ind);
    //printf("\n");
    //printf("Index Grade = %d", rind);
    //printf("\n");

    if(rind>=1 && rind<16) //If Index is between 1 and 16 print grade level of text
    {
        switch(rind) //Checks index value
        {
            case 1: printf("Grade 1\n");
            break;
            case 2: printf("Grade 2\n");
            break;
            case 3: printf("Grade 3\n");
            break;
            case 4: printf("Grade 4\n");
            break;
            case 5: printf("Grade 5\n");
            break;
            case 6: printf("Grade 6\n");
            break;
            case 7: printf("Grade 7\n");
            break;
            case 8: printf("Grade 8\n");
            break;
            case 9: printf("Grade 9\n");
            break;
            case 10: printf("Grade 10\n");
            break;
            case 11: printf("Grade 11\n");
            break;
            case 12: printf("Grade 12\n");
            break;
            case 13: printf("Grade 13\n");
            break;
            case 14: printf("Grade 14\n");
            break;
            case 15: printf("Grade 15\n");
            break;
        }
    }
    else if(rind>=16) //Index greater than 16
    {
        printf("Grade 16+");
    }
    else if(rind<1) //Index less than 1
    {
        printf("Before Grade 1");
    }

    return 0;
}

//FUNCTION TO CALCULATE NUMBER OF LETTERS
int letters(int l, char arr[])
{
    int i, let=0;

    for(i=0; i<l; i++) //Goes through entire string - If letter is present it updates count of letters
        {
            if(arr[i]>='a' && arr[i]<='z')
            {
                let++; //Update letter count
            }
            else if(arr[i]>='A' && arr[i]<='Z')
            {
                let++;
            }
        }
        return let;
}

//FUNCTION TO CALCULATE NUMBER OF WORDS
int words(int l, char arr[])
{
    int i, w=0;

    for(i=0; i<l; i++) //Goes through entire string
        {
            if(arr[i]==' ') //Every time a space is detected it conveys that one word has terminated and another one will begin
            {
                w++; //Updates word count
            }
        }
        return w+1; //+1 for the last word since after last word there is no space
}

//FUNCTION TO CALCULATE NUMBER OF SENTENCES
int sentences(int l, char arr[])
{
    int i, s=0;

    for(i=0; i<l; i++) //Goes through entire string
        {
            if(arr[i]=='.' || arr[i]=='!' || arr[i]=='?') //'.', '!' and '?' signify the end of a sentence
            {
                s++; //Every time these symbols occur the sentence count is updated
            }
        }
        return s;
}
