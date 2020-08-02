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
bool check_cycle(int winner, int loser, int initial_winner);

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

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]] += 1;
        }
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    pair_count = 0;
    //pairs[0].winner = -1;
    //pairs[0].loser = -1;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
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
            else
            {
                continue;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    if (pair_count == 0)
    {
        printf("NO PAIRS\n");
        return;
    }
    typedef struct
    {
        int winner;
        int loser;
        int diff;
    }
    comp;
    comp temp_diff[MAX * (MAX - 1) / 2];
    for (int i = 0; i < pair_count; i++)
    {
        temp_diff[i].winner = pairs[i].winner;
        temp_diff[i].loser = pairs[i].loser;
        temp_diff[i].diff = preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner];
    }
    int temp_winner, temp_loser, temp_difference;
    for (int i = 0 ; i < pair_count - 1; i++)
    {
        for (int j = 0 ; j < pair_count - i - 1; j++)
        {
            if (temp_diff[j].diff < temp_diff[j + 1].diff)
            {
                temp_difference = temp_diff[j].diff;
                temp_winner = temp_diff[j].winner;
                temp_loser = temp_diff[j].loser;
                temp_diff[j].diff = temp_diff[j+1].diff;
                temp_diff[j].winner = temp_diff[j+1].winner;
                temp_diff[j].loser = temp_diff[j+1].loser;
                temp_diff[j + 1].diff = temp_difference;
                temp_diff[j + 1].winner = temp_winner;
                temp_diff[j + 1].loser = temp_loser;
            }
        }
    }
    for(int i = 0; i < pair_count; i++)
    {
        pairs[i].winner = temp_diff[i].winner;
        pairs[i].loser = temp_diff[i].loser;
        printf("HIER: %i %i; diff: %i\n", temp_diff[i].winner, temp_diff[i].loser, temp_diff[i].diff);
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = 0;
        }
    }
    for (int i = 0; i < pair_count; i++)
    {
        bool circle = check_cycle(pairs[i].winner, pairs[i].loser, pairs[i].winner);
        printf("Circle: %i \n", circle);
        if (circle == 0)
        {
            locked[pairs[i].winner][pairs[i].loser] = 1;
        }

    }for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            printf("LOCKED: %i over %i: %i\n", i, j, locked[i][j]);
        }
    }
    return;
}

bool check_cycle(int winner, int loser, int initial_winner)
{
    if(locked[loser][initial_winner] == 1)
    {
        return true;
    }
    for(int i = 0; i < candidate_count; i++)
    {
        if(locked[loser][i] == 1)
        {
            check_cycle(loser, i, initial_winner);
        }
    }
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    return;
}

