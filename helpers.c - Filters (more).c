#include "helpers.h"
#include <stdlib.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float rgbGray; //Create variable to store average value for gray

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            rgbGray = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed)/3.000); //Calculates average value of RGB per pixel

            image[i][j].rgbtBlue = rgbGray; //Sets each pixel's colour byte to the average calculated
            image[i][j].rgbtGreen = rgbGray;
            image[i][j].rgbtRed = rgbGray;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int temp[3];

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width/2; j++) //width/2 because left and right side pixels are being swapped
        {
            //Swapping/Mirroring pixels using temporary variable
            temp[0] = image[i][j].rgbtBlue;
            temp[1] = image[i][j].rgbtGreen;
            temp[2] = image[i][j].rgbtRed;

            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue; //Calculates horizontal mirror coordinate
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;

            image[i][width - j - 1].rgbtBlue=temp[0];
            image[i][width - j - 1].rgbtGreen=temp[1];
            image[i][width - j - 1].rgbtRed=temp[2];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int sumBlue, sumGreen, sumRed;
    float count;

    RGBTRIPLE temp[height][width]; //Temporary blank image grid to store new values for color

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            sumBlue = 0; //Sum of Blue color in pixels
            sumGreen = 0; //Sum of Green color in pixels
            sumRed = 0; //Sum of Red color in pixels
            count = 0.00; //Counter to see how many pixels we have looked at - for average

            //For current pixel
            sumBlue += image[i][j].rgbtBlue;
            sumGreen += image[i][j].rgbtGreen;
            sumRed += image[i][j].rgbtRed;
            count++;

            if((i+1)<height) //Checks Pixel directly below
            {
                sumBlue += image[i+1][j].rgbtBlue;
                sumGreen += image[i+1][j].rgbtGreen;
                sumRed += image[i+1][j].rgbtRed;
                count++;
            }

            if((i-1)>=0) //Checks Pixel directly above
            {
                sumBlue += image[i-1][j].rgbtBlue;
                sumGreen += image[i-1][j].rgbtGreen;
                sumRed += image[i-1][j].rgbtRed;
                count++;
            }

            if((j+1)<width) //Checks Pixel to the right
            {
                sumBlue += image[i][j+1].rgbtBlue;
                sumGreen += image[i][j+1].rgbtGreen;
                sumRed += image[i][j+1].rgbtRed;
                count++;
            }

            if((j-1)>=0) //Checks Pixel to the left
            {
                sumBlue += image[i][j-1].rgbtBlue;
                sumGreen += image[i][j-1].rgbtGreen;
                sumRed += image[i][j-1].rgbtRed;
                count++;
            }

            if(((i-1)>=0) && ((j-1)>=0)) //Checks top left pixel
            {
                sumBlue += image[i-1][j-1].rgbtBlue;
                sumGreen += image[i-1][j-1].rgbtGreen;
                sumRed += image[i-1][j-1].rgbtRed;
                count++;
            }

            if(((i-1)>=0) && ((j+1)<width)) //Checks top right pixel
            {
                sumBlue += image[i-1][j+1].rgbtBlue;
                sumGreen += image[i-1][j+1].rgbtGreen;
                sumRed += image[i-1][j+1].rgbtRed;
                count++;
            }

            if(((i+1)<height) && ((j-1)>=0)) //Checks bottom left pixel
            {
                sumBlue += image[i+1][j-1].rgbtBlue;
                sumGreen += image[i+1][j-1].rgbtGreen;
                sumRed += image[i+1][j-1].rgbtRed;
                count++;
            }

            if(((i+1)<height) && ((j+1)<width)) //Checks bottom right pixel
            {
                sumBlue += image[i+1][j+1].rgbtBlue;
                sumGreen += image[i+1][j+1].rgbtGreen;
                sumRed += image[i+1][j+1].rgbtRed;
                count++;
            }

            temp[i][j].rgbtBlue = round(sumBlue / count); //find average
            temp[i][j].rgbtGreen = round(sumGreen / count);
            temp[i][j].rgbtRed = round(sumRed / count);
        }
    }

    for (int i = 0; i < height; i++) //Switch temp and image
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
        }
    }
    return;
}

// stops max value at 255 preventing overflow
int limit(int RGB)
{
    if (RGB > 255)
    {
        RGB = 255;
    }
    return RGB;
}

//Finds Edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    float sumBlueY;
    float sumGreenY;
    float sumRedY;
    float sumBlueX;
    float sumGreenX;
    float sumRedX;

    RGBTRIPLE temp[height][width]; //Temporary blank image grid to store new values for color

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            //All initialised to 0
            sumBlueY = 0.0; //Sum of Blue color in pixels
            sumGreenY = 0.0; //Sum of Green color in pixels
            sumRedY = 0.0; //Sum of Red color in pixels
            sumBlueX = 0.0; //Sum of Blue color in pixels
            sumGreenX = 0.0; //Sum of Green color in pixels
            sumRedX = 0.0; //Sum of Red color in pixels

            //For current pixel
            sumBlueY += image[i][j].rgbtBlue * 0;
            sumGreenY += image[i][j].rgbtGreen * 0;
            sumRedY += image[i][j].rgbtRed * 0;

            sumBlueX += image[i][j].rgbtBlue * 0;
            sumGreenX += image[i][j].rgbtGreen * 0;
            sumRedX += image[i][j].rgbtRed * 0;


            if((i+1)<height) //Checks Pixel directly below
            {
                sumBlueY += image[i+1][j].rgbtBlue * 2;
                sumGreenY += image[i+1][j].rgbtGreen * 2;
                sumRedY += image[i+1][j].rgbtRed * 2;

                sumBlueX += image[i+1][j].rgbtBlue * 0;
                sumGreenX += image[i+1][j].rgbtGreen * 0;
                sumRedX += image[i+1][j].rgbtRed * 0;
            }

            if((i-1)>=0) //Checks Pixel directly above
            {
                sumBlueY += image[i-1][j].rgbtBlue * (-2);
                sumGreenY += image[i-1][j].rgbtGreen * (-2);
                sumRedY += image[i-1][j].rgbtRed * (-2);

                sumBlueX += image[i-1][j].rgbtBlue * 0;
                sumGreenX += image[i-1][j].rgbtGreen * 0;
                sumRedX += image[i-1][j].rgbtRed * 0;
            }

            if((j+1)<width) //Checks Pixel to the right
            {
                sumBlueY += image[i][j+1].rgbtBlue * 0;
                sumGreenY += image[i][j+1].rgbtGreen * 0;
                sumRedY += image[i][j+1].rgbtRed * 0;

                sumBlueX += image[i][j+1].rgbtBlue * 2;
                sumGreenX += image[i][j+1].rgbtGreen * 2;
                sumRedX += image[i][j+1].rgbtRed * 2;
            }

            if((j-1)>=0) //Checks Pixel to the left
            {
                sumBlueY += image[i][j-1].rgbtBlue * 0;
                sumGreenY += image[i][j-1].rgbtGreen * 0;
                sumRedY += image[i][j-1].rgbtRed * 0;

                sumBlueX += image[i][j-1].rgbtBlue * (-2);
                sumGreenX += image[i][j-1].rgbtGreen * (-2);
                sumRedX += image[i][j-1].rgbtRed * (-2);
            }

            if(((i-1)>=0) && ((j-1)>=0)) //Checks top left pixel
            {
                sumBlueY += image[i-1][j-1].rgbtBlue * (-1);
                sumGreenY += image[i-1][j-1].rgbtGreen * (-1);
                sumRedY += image[i-1][j-1].rgbtRed * (-1);

                sumBlueX += image[i-1][j-1].rgbtBlue * (-1);
                sumGreenX += image[i-1][j-1].rgbtGreen * (-1);
                sumRedX += image[i-1][j-1].rgbtRed * (-1);
            }

            if(((i-1)>=0) && ((j+1)<width)) //Checks top right pixel
            {
                sumBlueY += image[i-1][j+1].rgbtBlue * (-1);
                sumGreenY += image[i-1][j+1].rgbtGreen * (-1);
                sumRedY += image[i-1][j+1].rgbtRed * (-1);

                sumBlueX += image[i-1][j+1].rgbtBlue * 1;
                sumGreenX += image[i-1][j+1].rgbtGreen * 1;
                sumRedX += image[i-1][j+1].rgbtRed * 1;
            }

            if(((i+1)<height) && ((j-1)>=0)) //Checks bottom left pixel
            {
                sumBlueY += image[i+1][j-1].rgbtBlue * 1;
                sumGreenY += image[i+1][j-1].rgbtGreen * 1;
                sumRedY += image[i+1][j-1].rgbtRed * 1;

                sumBlueX += image[i+1][j-1].rgbtBlue * (-1);
                sumGreenX += image[i+1][j-1].rgbtGreen * (-1);
                sumRedX += image[i+1][j-1].rgbtRed * (-1);
            }

            if(((i+1)<height) && ((j+1)<width)) //Checks bottom right pixel
            {
                sumBlueY += image[i+1][j+1].rgbtBlue * 1;
                sumGreenY += image[i+1][j+1].rgbtGreen * 1;
                sumRedY += image[i+1][j+1].rgbtRed * 1;

                sumBlueX += image[i+1][j+1].rgbtBlue * 1;
                sumGreenX += image[i+1][j+1].rgbtGreen * 1;
                sumRedX += image[i+1][j+1].rgbtRed * 1;
            }

            temp[i][j].rgbtBlue = limit(round(sqrt(sumBlueX * sumBlueX + sumBlueY * sumBlueY)));
            temp[i][j].rgbtGreen = limit(round(sqrt(sumGreenX * sumGreenX + sumGreenY * sumGreenY)));
            temp[i][j].rgbtRed = limit(round(sqrt(sumRedX * sumRedX + sumRedY * sumRedY)));
        }
    }

    for (int i = 0; i < height; i++) //Switch temp and image
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
        }
    }
    return;
}
