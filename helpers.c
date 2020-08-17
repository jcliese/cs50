#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //iterate over every pixel
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
    //initialize a copy of the picture
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //safe every pixel vertically reflected
            copy[i][width - (j + 1)] = image[i][j];
        }
    }
    //overwrite the image with the new reflected copy
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
    //initialize a copy
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    //iterate over every pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //initialize a sum for every color
            float blue = 0, green = 0, red = 0;
            //init count
            int count = 0;
            //iterate over all pixels surrounding the one which is checked
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    int h = i + k;
                    int w = j + l;
                    //check if outside of image
                    if ((h < 0 || h >= height) || (w < 0 || w >= width))
                    {
                        continue;
                    }
                    else
                    {
                        //use copy of picture because initial picture gets overwriten in process
                        blue += copy[h][w].rgbtBlue;
                        green += copy[h][w].rgbtGreen;
                        red += copy[h][w].rgbtRed;
                        count++;
                    }
                }
            }
            //overwrite picture
            image[i][j].rgbtBlue = round(blue / count);
            image[i][j].rgbtGreen = round(green / count);
            image[i][j].rgbtRed = round(red / count);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //init copy
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    //iterate over every pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //init variables
            int sobel_blue = 0, sobel_green = 0, sobel_red = 0;
            float blue = 0, green = 0, red = 0;
            int Gx_blue = 0, Gx_green = 0, Gx_red = 0;
            int Gy_blue = 0, Gy_green = 0, Gy_red = 0;
            //iterate over the pixels next to the one checked: get Gx values
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    int multi;
                    int h = i + k;
                    int w = j + l;
                    //check if outside of image
                    if ((h < 0 || h >= height) || (w < 0 || w >= width))
                    {
                        continue;
                    }
                    //define the multiplier
                    else
                    {
                        if (l == -1 || l == 1)
                        {
                            switch (k)
                            {
                                case -1:
                                case 1:
                                    multi = l;
                                    break;
                                case 0:
                                    multi = l * 2;
                                    break;
                                default:
                                    multi = 0;
                            }
                        }
                        else
                        {
                            multi = 0;
                        }
                        Gx_blue += (copy[h][w].rgbtBlue * multi);
                        Gx_green += (copy[h][w].rgbtGreen * multi);
                        Gx_red += (copy[h][w].rgbtRed * multi);
                    }
                }
                //iterate over nearby pixels: get Gy values
                for (int l = -1; l < 2; l++)
                {
                    int multi;
                    int h = i + k;
                    int w = j + l;
                    if ((h < 0 || h >= height) || (w < 0 || w >= width))
                    {
                        continue;
                    }
                    else
                    {
                        if (k == -1 || k == 1)
                        {
                            switch (l)
                            {
                                case -1:
                                case 1:
                                    multi = k;
                                    break;
                                case 0:
                                    multi = k * 2;
                                    break;
                                default:
                                    multi = 0;
                            }
                        }
                        else
                        {
                            multi = 0;
                        }
                        Gy_blue += (copy[h][w].rgbtBlue * multi);
                        Gy_green += (copy[h][w].rgbtGreen * multi);
                        Gy_red += (copy[h][w].rgbtRed * multi);
                    }
                }
            }
            //calculate sobel value for every color
            sobel_blue = round(sqrt(pow(Gx_blue, 2) + pow(Gy_blue, 2)));
            sobel_green = round(sqrt(pow(Gx_green, 2) + pow(Gy_green, 2)));
            sobel_red = round(sqrt(pow(Gx_red, 2) + pow(Gy_red, 2)));
            //check if sobel value is too hight
            if (sobel_blue > 255)
            {
                sobel_blue = 255;
            }
            if (sobel_green > 255)
            {
                sobel_green = 255;
            }
            if (sobel_red > 255)
            {
                sobel_red = 255;
            }
            //manipulate picture
            image[i][j].rgbtBlue = sobel_blue;
            image[i][j].rgbtGreen = sobel_green;
            image[i][j].rgbtRed = sobel_red;
        }
    }
    return;
}
