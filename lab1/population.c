#include <cs50.h>
#include <stdio.h>

int main(void)
{
      // TODO: Solicite o valor inicial ao usuário

    int i;
    do
    {
        i = get_int("Start size:  ");
    }
    while (i < 9);

     // TODO: Solicite o valor final ao usuário
    int f;
    do
    {
        f = get_int("End size:  ");
    }
    while (f < i);

     // TODO: Calcule o número de anos até o limite
    int y;
    for (y = 0; i < f; y++)
    {
        i = i + (i/3) - (i/4);
    }

     // TODO: Imprima o número de anos
    printf("Years: %i\n", y);
}
