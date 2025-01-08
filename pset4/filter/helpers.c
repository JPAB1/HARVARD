#include <string.h>
#include <math.h>
#include "helpers.h"

// Convert image to grayscale
// Converter imagem em tons de cinza
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            // Calcula o valor médio dos componentes RGB
            float average = 0.299 * image[x][y].rgbtRed + 0.587 * image[x][y].rgbtGreen + 0.114 * image[x][y].rgbtBlue;
            average = round(average); // Arredonda para o valor inteiro mais próximo
            average = fmin(255, fmax(0, average)); // Limita o valor entre 0 e 255

            // Atribui o valor médio a todos os componentes RGB
            image[x][y].rgbtRed = (unsigned char)average;
            image[x][y].rgbtGreen = (unsigned char)average;
            image[x][y].rgbtBlue = (unsigned char)average;
        }
    }
}

// Reflect image horizontally
// Refletir imagem horizontalmente
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width/2; y++)
        {
            RGBTRIPLE img = image[x][y];
            image[x][y] = image[x][width-y-1];
            image[x][width-y-1] = img;


        }
    }
    return;
}

// Blur image
// Desfocar imagem
void blur(int height, int width, RGBTRIPLE image[height][width])
{
        // Crie uma cópia da imagem original
    RGBTRIPLE copy[height][width];
    memcpy(copy, image, sizeof(copy));

    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            double sumRed = 0;
            double sumGreen = 0;
            double sumBlue = 0;
            int count = 0;

            // Percorra a vizinhança 3x3 (ou 2x3) do pixel atual
            for (int xx = x - 3; xx <= x + 3; xx++)
            {
                for (int yy = y - 3; yy <= y + 3; yy++)
                {
                    if (xx >= 0 && xx < height && yy >= 0 && yy < width)
                    {
                        sumRed += copy[xx][yy].rgbtRed;
                        sumGreen += copy[xx][yy].rgbtGreen;
                        sumBlue += copy[xx][yy].rgbtBlue;
                        count++;
                    }
                }
            }

            // Calcule os valores médios e atribua ao pixel original
            if (count != 0)
            {
                image[x][y].rgbtRed = (unsigned char)round(sumRed / count);
                image[x][y].rgbtGreen = (unsigned char)round(sumGreen / count);
                image[x][y].rgbtBlue = (unsigned char)round(sumBlue / count);
            }
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int sobelX[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int sobelY[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    RGBTRIPLE copy[height][width];
    memcpy(copy, image, sizeof(copy));

    for (int x = 1; x < height - 1; x++)
    {
        for (int y = 1; y < width - 1; y++)
        {
            int gxRed = 0, gxGreen = 0, gxBlue = 0;
            int gyRed = 0, gyGreen = 0, gyBlue = 0;

            for (int xx = -1; xx <= 1; xx++)
            {
                for (int yy = -1; yy <= 1; yy++)
                {
                    gxRed += sobelX[xx + 1][yy + 1] * copy[x + xx][y + yy].rgbtRed;
                    gxGreen += sobelX[xx + 1][yy + 1] * copy[x + xx][y + yy].rgbtGreen;
                    gxBlue += sobelX[xx + 1][yy + 1] * copy[x + xx][y + yy].rgbtBlue;

                    gyRed += sobelY[xx + 1][yy + 1] * copy[x + xx][y + yy].rgbtRed;
                    gyGreen += sobelY[xx + 1][yy + 1] * copy[x + xx][y + yy].rgbtGreen;
                    gyBlue += sobelY[xx + 1][yy + 1] * copy[x + xx][y + yy].rgbtBlue;
                }
            }

            int red = round(sqrt(gxRed * gxRed + gyRed * gyRed));
            int green = round(sqrt(gxGreen * gxGreen + gyGreen * gyGreen));
            int blue = round(sqrt(gxBlue * gxBlue + gyBlue * gyBlue));

            image[x][y].rgbtRed = fmin(255, red);
            image[x][y].rgbtGreen = fmin(255, green);
            image[x][y].rgbtBlue = fmin(255, blue);
        }
    }
    return;
}
