#include <cs50.h>
#include <stdio.h>
#include <string.h>

int luhn_algorithm(long  number) {
    char str[20];
    sprintf(str, "%ld", number);
    int soma = 0;
    int len = strlen(str);
    int parity = len % 2;

    for (int i = 0; i < len; i++)
    {
        int digito = str[i] - '0';

        if (i % 2 == parity)
        {
            digito *= 2;
            if (digito > 9)
            {
                digito -= 9;
            }
        }

        soma += digito;
    }
     return soma % 10 == 0;
}

int main() {
    long n;
    do
    {
        n = get_long("Digite o número do cartão de crédito:  ");
    }
    while ( n < 0);

    char st[20];
    sprintf(st,"%ld", n);
    char d[3];
    strncpy(d, st, 2);
    d[2] = '\0';
    char d1[2];
    strncpy(d1, st, 1);
    d1[1] = '\0';


    if (luhn_algorithm(n)) {
        printf("O número do cartão de crédito é válido.\n");
        if (strcmp(d,"34") == 0 || strcmp(d, "37") == 0)
        {
            printf("AMEX\n");
        }
        if (strcmp(d,"51") == 0 || strcmp(d, "52") == 0 || strcmp(d, "53") == 0 || strcmp(d, "54") == 0 || strcmp(d, "55") == 0)
            {
                printf("MasterCard\n");
            }
        if (strcmp(d1,"4") == 0)
            {
                printf("Visa\n");
            }
    } else {
        printf("O número do cartão de crédito é inválido.\n");
    }
    return 0;

}
