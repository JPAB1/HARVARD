#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //  Pega o valor de n com o usuário
    int n;
    do
    {
        n = get_int("Digite de 1 a 8: ");
    }
    while (n > 8 || n < 1);

    for (int i = 0; i < n; i++)
    {
        for (int e = 0; e < (n - i); e++)
        {
            printf(" ");
        }
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}