#include <cs50.h>
#include <math.h>
#include <stdio.h>

int main(void)
{
    float n;
    do
    {
        n = get_float("digite o troco:  ");
    }
    while (n <= 0);

    int centavos = round(n * 100);
    int qd_moedas = 0;

    for (qd_moedas = 0; centavos > 0;)
        if (centavos >= 25)
        {
            centavos = centavos - 25;
            qd_moedas++;
            printf(" 25 ");
        }
        else if (centavos >= 10 && centavos < 25)
        {
            centavos = centavos - 10;
            qd_moedas++;
            printf(" 10 ");
        }
        else if (centavos >= 5 && centavos < 10)
        {
            centavos = centavos - 5;
            qd_moedas++;
            printf(" 5 ");
        }
        else if (centavos >= 1 && centavos < 5)
        {
            centavos = centavos - 1;
            qd_moedas++;
            printf(" 1 ");
        }

    printf("%d, \n", qd_moedas);
}
