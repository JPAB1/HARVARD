#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
    //Verifique se o programa foi executado com um argumento de linha de comando
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");

        return 1;
    }
    // Para saber o tamanho da string
    int len = strlen(argv[1]);
    //Verificar se o tanho da string é 26
    if (len != 26)
    {
         printf("Usage: ./substitution Tem que conter 26 caracteres\n");
         return 1;
    }
    for (int i = 0; argv[1][i] !='\0'; i++)
    {
        // Verifica se é letras
        if (!isalpha(argv[1][i]))
        {
            printf("Usage: ./substitution tem que conter somente letras\n");
            return 1;
        }
        //transformanto string em maiúsculo
        argv[1][i] = toupper(argv[1][i]);
        //Verifica se contem caractres repetidos
        for (int x = i +1 ; argv[1][x] !='\0'; x++)
        {
            argv[1][x] = toupper(argv[1][x]);
            if (argv[1][x] == argv[1][i])
            {
                printf("Usage: ./substitution contem caracteres repetidos: %c\n ", argv[1][x]);
                return 1;
            }
        }

    }

    string texto = get_string("plaintext: ");
    string letrminus = "abcdefghijklmnopqrstuvwxyz";
    string letrmaius = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char c[100] = "";

    for (int i= 0; texto[i] !='\0'; i++)
    {
        for (int x = 0; letrmaius[x] !='\0'; x++)
        {
            //printf("texto %c", texto[i]);
            if (texto[i] == letrmaius[x])
            {
                  c[i] = argv[1][x];
                  break;
            }
            if (texto[i] == letrminus[x])
            {
                argv[1][x] = tolower(argv[1][x]);
                c[i] = argv[1][x];
                break;
            }
            else if (ispunct(texto[i]) || isspace(texto[i]) || isdigit(texto[i]))
            {
                c[i] = texto[i];
                break;
            }
            //printf("c %c", c[i]);
        }

    }
    printf("criptografado; %s\n", c);
}
