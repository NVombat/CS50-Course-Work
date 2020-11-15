#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

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

//Array of "pair" structures
pair pairs[MAX * (MAX - 1) / 2]; //Number of pairs (n(n-1))/2

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
bool check_cycle(void);
bool explore_nodes(int curr_node, int node_list[]);
void lock_pairs(void);
void print_winner(void);

int main(int argc, char *argv[])
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
bool vote(int rank, string name, int ranks[]) //Runs Per Vote - 3 times per voter
{
    int i;

    for(i=0; i<candidate_count; i++)
    {
        if(strcmp(name, candidates[i])==0) //compares voters choice with name
        {
            ranks[rank]=i; //updates ranks array(for each voter) to store the index of the candidate at current rank in array
            return true;
        }
    }
    return false; //return false and exit for invalid vote
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[]) //Runs 1 time per voter
{
    int i, j;

    for(i=0; i<candidate_count; i++)
    {
        for(j=i+1; j<candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++; //For each voter updates preference table where if [0, 1, 2] is the ranks array then 0 over 1 and 1 over 2 and so on...
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i+1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i]) //Checks preferences to see if 'i' is preferred over 'j' and assigns winner and loser in the PAIR STRUCT as per the value
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++; //appends pair count - Keep track of pair count
            }
            else if (preferences[i][j] < preferences[j][i]) //Checks preferences to see if 'j' is preferred over 'i' and assigns winner and loser in the PAIR STRUCT as per the value
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
void sort_pairs(void)
{
    int vote_diff[pair_count]; //to calculate and store vote differences for each struct between pair of candidates
    int temp1, temp2, temp3;
    int i, j;

    for (i = 0; i < pair_count; i++)
    {
        vote_diff[i]=preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner]; //Calculates vote differences by subtracting winner votes from loser votes
    }

    //Bubble Sort
    bool done=false;
    while(!done)
    {
        done=true;
        for(j=0; j<pair_count; j++)
        {
            if(vote_diff[j]<vote_diff[j+1])
            {
                //swaps vote difference along with individual winner and loser pairs
                temp1=vote_diff[j];
                temp2=pairs[j].winner;
                temp3=pairs[j].loser;

                vote_diff[j]=vote_diff[j+1];
                pairs[j].winner=pairs[j+1].winner;
                pairs[j].loser=pairs[j+1].loser;

                vote_diff[j+1]=temp1;
                pairs[j+1].winner=temp2;
                pairs[j+1].loser=temp3;

                done=false;
            }
        }
    }

    return;
}

//Check for cycles and return true or false
bool check_cycle(void)
{
    int node_list[candidate_count]; //To check visited nodes
    bool is_cycle;

    for (int i=0; i<candidate_count; i++)//Run for each candidate
    {
        //printf("\nChecking nodes for root candidate %d", i);
        for(int x=0; x<candidate_count; x++)
        {
            node_list[x]=-1; //Setting Node List to -1 (Invalid) before each candidate check
        }
        is_cycle=explore_nodes(i, node_list);
        if(is_cycle)
        {
            //printf("\nCycle detected");
            return true; //Return true if cycle is detected
        }
    }

    return false; //False if no cycle is detected
}

//Implementing Depth First Search Principle
//Explore Nodes Through Recursion
bool explore_nodes(int curr_node, int node_list[]) //curr_node = i = current candidate under observation
{
    //printf("\nCurrent node: %d", curr_node);
    for(int i=0; i<candidate_count; i++)
    {
        if(curr_node==node_list[i]) //Checks if current node(candidate) is part of the node list (has been visited) //Checking if its been revisited
        {
            return true; //If yes - Cycle is there
        }
    }

    node_list[curr_node]=curr_node; //If current node isn't in the node list then add the current node to the list
    for(int j=0; j<candidate_count; j++)
    {
        if(locked[curr_node][j]==true) //If edge forms from current node to candidate 'j' continue exploring using recursion
            {
                return explore_nodes(j, node_list);
            }
    }

    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    int i;
    for (i = 0; i < pair_count; i++)
    {
        locked[pairs[i].winner][pairs[i].loser]=true; //Set all locked array elements to true

        if(check_cycle()==true)
        {
            locked[pairs[i].winner][pairs[i].loser]=false; //If cycle is detected then set to false(same as skipping it)
        }
    }

    return;
}

// Print the winner of the election
void print_winner(void)
{
    int rank;

    for (int i = 0; i < candidate_count; i++)
    {
        rank = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == false) //Checks to see if no candidate(inner loop) has "beaten" the given candidate(Outer loop) and if so rank will equal candidate_count because that many people would not have locked over the candidate
            {
                rank++;
            }
        }

        // Prints all the names that are the source of the graph
        if (rank == candidate_count) //If no one has beaten the given candidate from the outer loop then Candidate is the source of the graph
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}
