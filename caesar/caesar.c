#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


int main(int argc, string argv[])
{
     //Verifique se o programa foi executado com um argumento de linha de comando;
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");

        return 1;
    }

    //Repita o argumento fornecido para garantir que todos os caracteres sejam dígitos;
    for (int i = 0; argv[1][i] !='\0'; i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    int k = atoi(argv[1]);//trasformando em inteiro

    string text = get_string("plaintext: ");

    // Repita/Itere para cada caractere do plaintext: (texto simples)
    string c = text;
    for (int i = 0; text[i] != '\0'; i++)
    {
        //Se é uma letra maiuscula, rotacione-a, preservando capitalização, e então imprima o caractere rotacionado.
        if (isupper(text[i]))
        {
            c[i] = (text[i] - 65 + k + 26)% 26 + 65;
        }
        else if (islower(text[i]))
        {
            c[i] = (text[i] - 97 + k + 26)% 26 + 97;
        }
        else
        {
            c[i] = text[i];
        }
    }
    printf("ciphertext: %s\n", c);

    return 0;
}
