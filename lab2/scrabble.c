#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Pontos atribuídos a cada letra do alfabeto
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
string alfabeto = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
         printf("Player 2 wins!\n");
    }
    else if (score1 == score2)
    {
         printf("Tie!\n");
    }
}

int compute_score(string word)
{
    // TODO: Compute and return score for string
    int soma = 0;
    for (int i = 0; i < strlen(word) ; i++)
    {
        word[i] = toupper(word[i]);

        for (int x = 0; alfabeto[x] !='\0'; x++)
        {
            if (word[i] == alfabeto[x])
            {
                soma += POINTS[x];
                break;
            }
        }
    }
    return soma;
}
