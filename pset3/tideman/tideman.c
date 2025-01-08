#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
// preferências[i][j] é o número de eleitores que preferem i a j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
// locked[i][j] significa que estou bloqueado em mais de j
bool locked[MAX][MAX];

// Each pair has a winner, loser
// Cada dupla tem um vencedor, um perdedor
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
// Matriz de candidatos
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
// Protótipos de função
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
bool creates_cycle(int winner, int loser);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    // Verificar se há uso inválido
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    // Preencher matriz de candidatos
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    // Limpar gráfico de pares bloqueados
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    // Consulta de votos
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        // ranks[i] é a i-ésima preferência do eleitor
        int ranks[candidate_count];

        // Query for each rank
        // Consulta para cada classificação
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
// Atualizar classificações com uma nova votação
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            //printf("ranks %i\n", ranks[i]);
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
// Atualizar preferências de acordo com a classificação de um eleitor
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            int candidate_i = ranks[i];
            int candidate_j = ranks[j];
            preferences[candidate_i][candidate_j]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
// Registre pares de candidatos em que um é preferido em relação ao outro
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for(int j = i+1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
// Ordenar pares em ordem decrescente pela força da vitória
void sort_pairs(void)
{
    for (int i=0; i < pair_count - 1; i++)
    {
        for (int j = i + 1; j < pair_count; j++)
        {
             if (preferences[pairs[i].winner][pairs[i].loser] < preferences[pairs[j].winner][pairs[j].loser])
             {
                pair temp = pairs[i];
                pairs[i] = pairs[j];
                pairs[j] = temp;
             }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
// Bloquear pares no gráfico candidato em ordem, sem criar ciclos
void lock_pairs(void)
{
    for(int i = 0; i < pair_count; i++)
    {
        int winner = pairs[i].winner;
        int loser = pairs[i].loser;
        // Verifica se adicionar o par cria um ciclo
        if (!creates_cycle(winner, loser))
        {
            locked[winner][loser] = true;
        }
    }
}
// Verifica se adicionar o par cria um ciclo
bool creates_cycle(int winner, int loser)
{
    // Verifica se o perdedor já é um vencedor
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i])
        {
            if (i == winner)
            {
                return true;
            }
            else if (creates_cycle(winner, i))
            {
                return true;
            }
        }
    }

    return false;
}
// Print the winner of the election
// Imprimir o vencedor da eleição
void print_winner(void)
{
     for (int i = 0; i < candidate_count; i++)
    {
        bool is_winner = true;

        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                is_winner = false;
                break;
            }
        }

        if (is_winner)
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}

