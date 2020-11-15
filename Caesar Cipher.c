#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

int main()
{
    char str[500];
    int i, k, l;


    printf("plaintext: "); //Takes user input for string that needs to be run through cipher
    scanf("%[^\t\n]s", str);
    //puts(str);
    //printf("\n");

    l=strlen(str); //Calculates string length
    //printf("%d", l);
    //printf("\n");

    printf("Command Line Argument k: "); // Takes user input for key of cipher
    scanf("%d", &k);
    //printf("%d", k);
    //printf("\n");

    if(k>26) //Checks if key is greater than the number of letters in the alphabet(26)
    {
        while(k>26) //If yes then keeps subtracting 26 while it is greater than 26 till it becomes less than 26
        {
            k=k-26;
        }
        printf("%d", k); //Outputs Key
    }
    printf("\n");

    for(i=0; i<l; i++) //Runs through length of string
    {
        if(str[i]>=97 && str[i]<=122) //Checks to see if the character under observation is a lower case letter
        {
            str[i]=str[i]-32; //Converts the character to upper case first
            str[i]=str[i]+k; //Adds value of key to the character
            if(str[i]>'Z') //After adding value of key to the character, does it cross A-Z (65-90)(since ASCII doesn't only deal with characters)
            {
                str[i]=(str[i]%90)+65-1; //Modulus checks by how much it over shot the range(90 for UPPER) then adds lower limit(65) and subtracts 1 to get to the current character
            }
            str[i]=str[i]+32; //Converts the character back to lower case
        }
        else if(str[i]>='A' && str[i]<='Z')
        {
            str[i]=str[i]+k; //Adds value of key to the character
            if(str[i]>'Z') //After adding value of key to the character, does it cross A-Z (65-90)(since ASCII doesn't only deal with characters)
            {
                str[i]=(str[i]%90)+65-1; //Modulus checks by how much it over shot the range(90 for UPPER) then adds lower limit(65) and subtracts 1 to get to the current character
            }
        }
    }

    puts(str);
    printf("\n");

    return 0;
}

/* COMMAND LINE ARGUMENT (CLA) CAESAR CIPHER:
#include<cs50.h> //HARVARD HELPER LIBRARY
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

int main(int argc, char *argv[]) //Accepts Command Line arguments(CLA). ARGC stores number of CLA and ARGV stores CLA in the form of strings
{
    if(argc==2) //TWO CLA
    {
        char str[500];
        int i, k, l;

        k=atoi(argv[1]); //Converts string type CLA to an integer
        //printf("%d", k);
        //printf("\n");

        printf("plaintext: ");
        scanf("%[^\t\n]s", str);
        //puts(str);
        //printf("\n");

        l=strlen(str);
        //printf("%d", l);
        //printf("\n");

        //printf("Command Line Argument k: ");
        //scanf("%d", &k);
        //printf("%d", k);
        //printf("\n");

        if(k>26)
        {
            while(k>26)
            {
                k=k-26;
            }
            printf("%d", k);
        }
        //printf("\n");

        for(i=0; i<l; i++)
        {
            if(str[i]>=97 && str[i]<=122)
            {
                str[i]=str[i]-32;
                str[i]=str[i]+k;
                if(str[i]>'Z')
                {
                    str[i]=(str[i]%90)+65-1;
                }
                str[i]=str[i]+32;
            }
            else if(str[i]>='A' && str[i]<='Z')
            {
                str[i]=str[i]+k;
                if(str[i]>'Z')
                {
                    str[i]=(str[i]%90)+65-1;
                }
            }
        }

    printf("ciphertext: %s", str); //Prints final ciphertext
    printf("\n");

    return 0;
    }
    else if(argc>2 || argc<2) //Excess or Lack of CLA
    {
        printf("Error In Command Line Argument");
        return 1;
    }
    else //Error
    {
        printf("Usage: ./caesar key");
    }
}
*/
