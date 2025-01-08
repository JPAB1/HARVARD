#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes =  Continue consultando por votos
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank = Consulta para cada classificação
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");

    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates =
        // Calcular os votos dados aos candidatos restantes
        tabulate();

        // Check if election has been won = Verificar se a eleição foi vencida
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates = Elimine os candidatos do último lugar
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins = Se empatar, todos ganham
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes =
        // Eliminar qualquer pessoa com número mínimo de votos
        eliminate(min);

        // Reset vote counts back to zero = Redefinir a contagem de votos de volta a zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }

    return 0;

}

// Record preference if vote is valid = Registrar preferência se o voto for válido
bool vote(int voter, int rank, string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name ) == 0)
        {
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates = Tabular votos para candidatos não eliminados
void tabulate(void)
{
    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            int voto = preferences[i][j];
            if (!candidates[voto].eliminated)
            {
                candidates[voto].votes += 1;
                break;
            }
        }

    }
    return;
}

// Print the winner of the election, if there is one =
//Imprima o vencedor da eleição, se houver
bool print_winner(void)
{
    float voc = voter_count / 2 + 0.1;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes >= voc)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
// Devolver o número mínimo de votos que qualquer candidato restante tem
int find_min(void)
{
    int min = voter_count;
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated && min > candidates[i].votes)
        {
            min = candidates[i].votes;
        }
    }
    return min;
}

// Return true if the election is tied between all candidates, false otherwise
// Retorno verdadeiro se a eleição estiver empatada entre todos os candidatos, falso caso contrário
bool is_tie(int min)
{
    for (int i =0; i < candidate_count; i++)
    {
        if(!candidates[i].eliminated && candidates[i].votes!=min)
        {
            return false;
        }
    }
    return true;
}

// Eliminate the candidate (or candidates) in last place
// Eliminar o candidato (ou candidatos) em último lugar
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}
