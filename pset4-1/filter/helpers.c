#include "helpers.h"
#include "math.h"
#include "string.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            // Calcula o valor médio dos componentes RGB
            int media = (image[x][y].rgbtBlue + image[x][y].rgbtGreen + image[x][y].rgbtRed)/3;
            // Arredonda para o valor inteiro mais próximo
            media = round(media);

            // Limita o valor entre 0 e 255
            media = fmin(255, fmax(0, media));

            // Atribui o valor médio a todos os componentes RGB
            image[x][y].rgbtBlue = (unsigned char)media;
            image[x][y].rgbtGreen = (unsigned char)media;
            image[x][y].rgbtRed = (unsigned char)media;

        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int x = 0; x < height; x++)
    {
        for ( int y =0; y < width; y++)
        {
            // formula para sepia (envelhecimento)
            float sepiaRed = .393 * image[x][y].rgbtRed + .769 * image[x][y].rgbtGreen + .189 * image[x][y].rgbtBlue;
            float sepiaGreen = .349 * image[x][y].rgbtRed + .686 * image[x][y].rgbtGreen + .168 * image[x][y].rgbtBlue;
            float sepiaBlue = .272 * image[x][y].rgbtRed + .534 * image[x][y].rgbtGreen + .131 * image[x][y].rgbtBlue;

            sepiaRed = round(sepiaRed);
            sepiaGreen = round(sepiaGreen);
            sepiaBlue = round(sepiaBlue);

            sepiaRed = fmin(255, fmax(0, sepiaRed));
            sepiaGreen = fmin(255, fmax(0, sepiaGreen));
            sepiaBlue = fmin(255, fmax(0, sepiaBlue));


            image[x][y].rgbtRed = (unsigned char)sepiaRed;
            image[x][y].rgbtGreen = (unsigned char)sepiaGreen;
            image[x][y].rgbtBlue = (unsigned char)sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // o código do exercicio anterior é mais eficiente pois oculpa menos espaço na memoria

    // faz uma copia da imagem
    RGBTRIPLE nova_image[height][width];
    memcpy(nova_image, image, sizeof(nova_image));

    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            // substituir o primeiro pixels por o ultimo da linha.
            image[x][y] = nova_image[x][width-y-1];
        }
    }
    return;
}

// Blur image
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
