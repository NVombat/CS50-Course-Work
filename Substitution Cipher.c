#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

int main()
{
    char str[500], ciph[500], key[26]; //Char - Input String //Ciph - Cipher text //Key - Key
    int i, j, l, ind;

    printf("plaintext: "); //Inputs plain text string
    scanf("%[^\t\n]s", str);
    //puts(str);
    //printf("\n");

    l=strlen(str); //Finds length of string
    //printf("plaintext Length = %d", l);
    //printf("\n");

    /*
    //To find ASCII value of characters in the string
    for(i=0; i<l; i++)
    {
        printf("str[%d] = %c ASCII %d\t", i, str[i], str[i]);
        printf("\n");
    }*/

    printf("Enter Key: "); //Enter key as a string
    scanf("%s", key);
    //puts(key);
    //printf("\n");

    for(j=0; j<26; j++) //Runs through key
    {
        if(key[j]>='a' && key[j]<='z') //Checks if any key characters are in lower case
        {
            key[j]=key[j]-32; //Converts lower case key characters to upper case
        }
        //printf("key[%d] = %c ASCII %d\n", j, key[j], key[j]);
    }
    //puts(key);
    //printf("\n");

    for(i=0; i<l; i++) //Runs through plain text string
    {
        if(str[i]>='a' && str[i]<='z') //If letter is lower case (97-122)
        {
            ind=str[i]-97; //To give letter an index from 0-25 since characters in the key have indexes from 0-25
            //printf("index = %d\t", ind);
            //printf("key[%d] = %c\t", ind, key[ind]);
            ciph[i]=key[ind]; //Cipher text character will be the same index but applied to the key array
            //printf("ciph[%d] = %c\n", i, ciph[i]);
            if(ciph[i]>122) //If it over shoots the range it has to cycle back
            {
                ciph[i]=(ciph[i]%122)+65-1; //Modulus to see how much it over shot the range by and then +65 to get it back in that range from the start again and -1 to get to the particular character
            }
            ciph[i]=ciph[i]+32; //Since key is only in upper case (converted earlier)
        }
        else if(str[i]>='A' && str[i]<='Z')
        {
            ind=str[i]-65; //To give letter an index from 0-25 since characters in the key have indexes from 0-25
            //printf("index = %d\t", ind);
            //printf("key[%d] = %c\t", ind, key[ind]);
            ciph[i]=key[ind]; //Cipher text character will be the same at index but applied to the key array
            //printf("ciph[%d] = %c\n", i, ciph[i]);
            if(ciph[i]>90)
            {
                ciph[i]=(ciph[i]%90)+65-1; //Modulus to see how much it over shot the range by and then +65 to get it back in that range from the start again and -1 to get to the particular character
            }
        }
        else //Any symbols etc other than letters stay the same
        {
            ciph[i]=str[i];
            //printf("%c", ciph[i]);
        }
    }
    printf("ciphertext: ");

    for(i=0; i<l; i++) //Prints cipher text character by character
    {
        printf("%c", ciph[i]);
    }
    printf("\n");

    return 0;
}

//SUBSTITUTION CIPHER WITH COMMAND LINE ARGUMENTS:
/*
#include<cs50.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

int main(int argc, char *argv[]) //Command Line Arguments
{
    int x, y;
    if(argc==2)
    {
        if(strlen(argv[1])!=26) //If key is not 26 characters long
        {
            printf("Key Needs To Be 26 Characters Long\n");
            return 1;
        }
        else
        {
            //INVALID CHAR CHECK //Each character of the key should be a letter only
            for(y=0; y<26; y++)
            {
               if(argv[1][y]<'A' || (argv[1][y]>'Z' && argv[1][y]<'a') || argv[1][y]>'z')
                {
                    printf("Invalid Characters!");
                    return 1;
                }
            }
            //DUPLICATE CHECK
            for(x=0; x<26; x++)
            {
                for(y=x+1; y<26; y++)
                {
                    if(argv[1][x]==argv[1][y])
                    {
                        printf("Duplicate Letters Present");
                        return 1;
                    }
                }
            }

            char str[500], ciph[500];
            int i, j, l, ind;

            printf("plaintext: ");
            scanf("%[^\t\n]s", str);
            //puts(str);
            //printf("\n");

            l=strlen(str);
            //printf("plaintext Length = %d", l);
            //printf("\n");

            //for(i=0; i<l; i++)
            //{
                //printf("str[%d] = %c ASCII %d\t", i, str[i], str[i]);
                //printf("\n");
            //}

            //printf("Enter Key: ");
            //scanf("%s", key);
            //puts(key);
            //printf("\n");

            for(j=0; j<26; j++)
            {
                if(argv[1][j]>='a' && argv[1][j]<='z')
                {
                    argv[1][j]=argv[1][j]-32;
                }
                //printf("key[%d] = %c ASCII %d\n", j, key[j], key[j]);
            }
            //puts(key);
            //printf("\n");

            for(i=0; i<l; i++)
            {
                if(str[i]>='a' && str[i]<='z')
                {
                    ind=str[i]-97;
                    //printf("index = %d\t", ind);
                    //printf("key[%d] = %c\t", ind, key[ind]);
                    ciph[i]=argv[1][ind];
                    //printf("ciph[%d] = %c\n", i, ciph[i]);
                    if(ciph[i]>122)
                    {
                        ciph[i]=(ciph[i]%122)+65-1;
                    }
                    ciph[i]=ciph[i]+32;
                }
                else if(str[i]>='A' && str[i]<='Z')
                {
                    ind=str[i]-65;
                    //printf("index = %d\t", ind);
                    //printf("key[%d] = %c\t", ind, key[ind]);
                    ciph[i]=argv[1][ind];
                    //printf("ciph[%d] = %c\n", i, ciph[i]);
                    if(ciph[i]>90)
                    {
                        ciph[i]=(ciph[i]%90)+65-1;
                    }
                }
                else
                {
                    ciph[i]=str[i];
                    //printf("%c", ciph[i]);
                }
            }
            printf("ciphertext: ");

            for(i=0; i<l; i++)
            {
                printf("%c", ciph[i]);
            }
            printf("\n");

            return 0;
        }
    }
    else if(argc>2 || argc<2)
    {
        printf("Error In Command Line Argument\n");
        return 1;
    }
    else
    {
        printf("Usage: ./substitution key\n");
    }
}
*/
