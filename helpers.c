 #include "helpers.h"
 #include <stdio.h>
 #include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float sum = 0;
            sum += image[i][j].rgbtBlue;
            sum += image[i][j].rgbtGreen;
            sum += image[i][j].rgbtRed;
            sum /= 3;
            sum = round(sum);
            image[i][j].rgbtBlue = sum;
            image[i][j].rgbtGreen = sum;
            image[i][j].rgbtRed = sum;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][width-(j+1)] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = copy[i][j];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int blue = 0, green = 0, red = 0;
            int count = 0;
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    int h = i + k;
                    int w = j + l;
                    if ((h < 0 || h >= height) || (w < 0 || w >= width))
                    {
                        continue;
                    }
                    else
                    {

                        blue += copy[h][w].rgbtBlue;
                        green += copy[h][w].rgbtGreen;
                        red += copy[h][w].rgbtRed;
                        count++;
                    }
                }
            }
            image[i][j].rgbtBlue = round(blue/count);
            image[i][j].rgbtGreen = round(green/count);
            image[i][j].rgbtRed = round(red/count);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
