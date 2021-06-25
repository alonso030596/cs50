#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
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
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
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

        for(int i = 0; i < candidate_count; i++)
        {
            for(int j = 0; j < candidate_count; j++)
            {
                printf("%d  ",preferences[i][j]);
            }

            putchar('\n');
        }

    putchar('\n');

    add_pairs();

    for(int i = 0; i < pair_count; i++)
        {
                printf("%s-%s %d-%d\n",candidates[pairs[i].winner],candidates[pairs[i].loser], preferences[pairs[i].winner][pairs[i].loser], preferences[pairs[i].loser][pairs[i].winner]);
        }

    putchar('\n');

    sort_pairs();

    for(int i = 0; i < pair_count; i++)
        {
                printf("%s-%s %d-%d\n",candidates[pairs[i].winner],candidates[pairs[i].loser], preferences[pairs[i].winner][pairs[i].loser], preferences[pairs[i].loser][pairs[i].winner]);
        }

    putchar('\n');

    lock_pairs();

    for(int i = 0; i < candidate_count; i++)
        {
            for(int j = 0; j < candidate_count; j++)
            {
                printf("%5s  ", locked[i][j] ? "true" : "false");
            }

            putchar('\n');
        }

    putchar('\n');

    print_winner();

    return 0;
}

//Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    int i = 0;
    while(strcmp(name, candidates[i]) && ++i < candidate_count)
        ;

    if(i == candidate_count)
        return false;

    ranks[rank] = i;

    return true;
}

//Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for(int i = 0; i < candidate_count - 1; i++)
    {
        for(int j = 1; i + j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[i + j]]++;
        }
    }

    return;
}

//Record pairs of candidates where one is preferred over the other.
void add_pairs(void)
{
    for(int i = 0; i < candidate_count - 1; i++)
    {
        for(int j = 1; i + j < candidate_count; j++)
        {
            if(preferences[i][i + j] > preferences[i + j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = i + j;
                pair_count++;
            }

            else if(preferences[i][i + j] < preferences[i + j][i])
            {
                pairs[pair_count].winner = i + j;
                pairs[pair_count].loser = i;
                pair_count++;
            }

            else
                ;
        }
    }

    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int difference(int);
    void swap_pairs(pair, pair);

    int i, swap_counter;
    //Bubble sort
    do
    {
        i = 0;
        swap_counter = 0;

        while(i + 1 < pair_count)
        {
            if(difference(i) < difference(i + 1))
            {
                swap_pairs(pairs[i], pairs[i + 1]);
                swap_counter++;
            }
            i++;
        }
    }
    while(swap_counter != 0);

    return;
}

int difference(int index)
{
    return preferences[pairs[index].winner][pairs[index].loser] - preferences[pairs[index].loser][pairs[index].winner];
}

void swap_pairs(pair p1, pair p2)
{
    pair aux;

    aux = p1;
    p1 = p2;
    p2 = aux;

    return;
}

//Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
     for(int i = 0; i < pair_count; i++)
    {
            locked[pairs[i].winner][pairs[i].loser] = true;
    }

    return;
}

//Print the winner of the election
void print_winner(void)
{
    //printf("%s\n",candidates[pairs[0].winner]);
    return;
}