#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    BYTE average;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            average = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3);
            image[i][j].rgbtBlue = image[i][j].rgbtGreen = image[i][j].rgbtRed = average;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width % 2 ? width - 1 / 2 : width / 2); j++)
        {
            temp = image[i][j];
            image[i][j] = image[i][width - j];
            image[i][width - j] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    BYTE nelements;
    RGBTRIPLE aux[height][width];
    int sumred, sumgreen, sumblue;

    for(int i = 0; i < height; i++) //Makes a copy of image as reference
    {
        for(int j = 0; j < width; j++)
        {
            aux[i][j] = image[i][j];
        }
    }


    for(int i = 0; i < height; i++) //For each row
    {
        for(int j = 0; j < width; j++) //For each column
        {
            sumred = sumgreen = sumblue = 0;

            //For elements on the edge
            if(!i || !j || i == height - 1 || j == width - 1)
            {
                nelements = 0;

                if (i - 1 >= 0 && j - 1 >= 0) //Upper left
                {
                    nelements++;
                    sumred += aux[i - 1][j - 1].rgbtRed;
                    sumgreen += aux[i - 1][j - 1].rgbtGreen;
                    sumblue += aux[i - 1][j - 1].rgbtBlue;
                }

                if (i - 1 >= 0) //Upper
                {
                    nelements++;
                    sumred += aux[i - 1][j].rgbtRed;
                    sumgreen += aux[i - 1][j].rgbtGreen;
                    sumblue += aux[i - 1][j].rgbtBlue;
                }

                if (i - 1 >= 0 && j + 1 >= width - 1) //Upper right
                {
                    nelements++;
                    sumred += aux[i - 1][j + 1].rgbtRed;
                    sumgreen += aux[i - 1][j + 1].rgbtGreen;
                    sumblue += aux[i - 1][j + 1].rgbtBlue;
                }

                if (j - 1 >= 0) //Left
                {
                    nelements++;
                    sumred += aux[i][j - 1].rgbtRed;
                    sumgreen += aux[i][j - 1].rgbtGreen;
                    sumblue += aux[i][j - 1].rgbtBlue;
                }

                //Self
                nelements++;
                sumred += aux[i][j].rgbtRed;
                sumgreen += aux[i][j].rgbtGreen;
                sumblue += aux[i][j].rgbtBlue;

                if (j + 1 <= width - 1) //Right
                {
                    nelements++;
                    sumred += aux[i][j + 1].rgbtRed;
                    sumgreen += aux[i][j + 1].rgbtGreen;
                    sumblue += aux[i][j + 1].rgbtBlue;
                }

                if (i + 1 <= height - 1 && j - 1 >= 0) //Lower left
                {
                    nelements++;
                    sumred += aux[i + 1][j - 1].rgbtRed;
                    sumgreen += aux[i + 1][j - 1].rgbtGreen;
                    sumblue += aux[i + 1][j - 1].rgbtBlue;
                }

                if (i + 1 <= height - 1) //Lower
                {
                    nelements++;
                    sumred += aux[i + 1][j].rgbtRed;
                    sumgreen += aux[i + 1][j].rgbtGreen;
                    sumblue += aux[i + 1][j].rgbtBlue;
                }

                if (i + 1 <= height - 1 && j + 1 <= width - 1) //Lower Right
                {
                    nelements++;
                    sumred += aux[i + 1][j + 1].rgbtRed;
                    sumgreen += aux[i + 1][j + 1].rgbtGreen;
                    sumblue += aux[i + 1][j + 1].rgbtBlue;
                }

                image[i][j].rgbtRed = sumred / nelements;
                image[i][j].rgbtGreen = sumgreen / nelements;
                image[i][j].rgbtBlue = sumblue / nelements;

            }

            else
            {
                for(int k = i - 1; k <= i + 1; k++)
                {
                    for(int l = j - 1; l <= j + 1; l++)
                    {
                        sumred += aux[k][l].rgbtRed;
                        sumgreen += aux[k][l].rgbtGreen;
                        sumblue += aux[k][l].rgbtBlue;
                    }
                }

                image[i][j].rgbtRed = sumred / 9;
                image[i][j].rgbtGreen = sumgreen / 9;
                image[i][j].rgbtBlue = sumblue / 9;
            }
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    char GX[][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    char GY[][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    RGBTRIPLE aux[height + 2][width + 2];

    RGBTRIPLE black = {0, 0, 0};

    long int sumred_gx, sumgreen_gx, sumblue_gx, sumred_gy, sumgreen_gy, sumblue_gy ;
    double gxgy_red, gxgy_green , gxgy_blue;

    //MAKES A COPY OF image[][] AND ADDS A BLACK BORDER
    for(int i = 0; i < height + 2; i++)
    {
        for(int j = 0; j < width + 2; j++)
        {
            if(!i || !j || i == height + 1 || j == width + 1)
                aux[i][j] = black;

            else
                aux[i][j] = image[i - 1][j - 1];
        }
    }

    for(int i = 0; i < height; i++) //FOR EACH ROW
    {
        for(int j = 0; j < width; j++) //FOR EACH ELEMENT
        {
            sumred_gx = sumgreen_gx = sumblue_gx = sumred_gy = sumgreen_gy = sumblue_gy = 0;

            for(int k = i - 1, m = 0; k <= i + 1; k++, m++)
            {
                for(int l = j - 1, n = 0; l <= j + 1; l++, n++)
                {
                     sumred_gx += aux[k][l].rgbtRed * GX[m][n];
                     sumgreen_gx += aux[k][l].rgbtGreen * GX[m][n];
                     sumblue_gx += aux[k][l].rgbtBlue * GX[m][n];

                     sumred_gy += aux[k][l].rgbtRed * GY[m][n];
                     sumgreen_gy += aux[k][l].rgbtGreen * GY[m][n];
                     sumblue_gy += aux[k][l].rgbtBlue * GY[m][n];
                }
            }

            gxgy_red = sqrt(pow(sumred_gx, 2) + pow(sumred_gy, 2));
            gxgy_green = sqrt(pow(sumgreen_gx, 2) + pow(sumgreen_gy, 2));
            gxgy_blue = sqrt(pow(sumblue_gx, 2) + pow(sumblue_gy, 2));

            image[i][j].rgbtRed = gxgy_red >= 255 ? 255 : gxgy_red;
            image[i][j].rgbtGreen = gxgy_green >= 255 ? 255 : gxgy_green;
            image[i][j].rgbtBlue = gxgy_blue >= 255 ? 255 : gxgy_blue;
        }
    }

    return;
}
