#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>

int main(void)
{
    string tex = get_string("Text:");

    int espaco = 1;
    int letra = 0;
    int frase = 0;
    int c = 0;
    while (tex[c] != '\0')//Percorre cada caractere da string
    {
        if (isalpha(tex[c]))// Verifica se é uma letra
        {
            letra += 1;
        }
        if (isspace(tex[c]))// Verifica se é espaço
           {
               espaco += 1;
           }
        if (tex[c] == '.' || tex[c] == '!' || tex[c] == '?')// Verifica se é ponto
            {
                frase += 1;
            }
        c += 1;
    }

    float l = (float) letra / espaco * 100;
    float s = (float) frase / espaco * 100;
    float indice = 0.0588 * l - 0.296 * s - 15.8;

     // Arredonde o índice para o número inteiro mais próximo
    int rounded_index = (int) round(indice);

    if ( rounded_index < 1)
    {
        printf("Before Grade 1\n" );
    }
    else if ( rounded_index < 16)
    {
        printf("GRADE %i\n",  rounded_index );
    }
    else
    {
        printf( "Grade 16+\n");
    }


   return 0;
}
