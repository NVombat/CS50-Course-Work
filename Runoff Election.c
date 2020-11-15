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

int main(int argc, string argv[]) //Command line arguments
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1; //ARGC stores number of command line arguments and -1 since first argument is ./runoff
    if (candidate_count > MAX_CANDIDATES) //Checks if candidates are not in excess
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1]; //ARGV stores CLA in string type format - Each name is stored in structure for each candidate
        candidates[i].votes = 0; //Sets candidate votes to 0
        candidates[i].eliminated = false; //Sets eliminated status to false
    }

    voter_count = get_int("Number of voters: "); //Gets number of voters from User
    if (voter_count > MAX_VOTERS) //Checks for excess voters
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++) //For each voter to vote
    {

        // Query for each rank
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
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated) //If candidate has not been eliminated then print name as winner
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    int i;
    for(i=0; i<candidate_count; i++) //Runs through each candidate
    {
        if(!candidates[i].eliminated) //If candidate has not been eliminated then...
        {
            if(strcmp(name,candidates[i].name)==0) //Checks if voter choice matches a candidate name
            {
                preferences[voter][rank]=i; //Updates preference table where voter x(some voter) has candidate i(current candidate) as their rank j(current rank)
                //printf("%i %i = %i\n", voter, rank, i);
                return true;
            }
        }
    }
    return false; //Return false for invalid vote
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    int check = 0;
    for (int i = 0; i < voter_count; i++)
    {
        if (!candidates[preferences[i][check]].eliminated) //If not eliminated, only adds vote for rank 1 candidates (top choice of every voter)
        {
            candidates[preferences[i][check]].votes++; //Updates vote
            check = 0; //So that choice of next voter is yet again their rank 1 candidate
        }
        else
        {
            check++; //If candidate has been eliminated then candidate in next rank gets vote
            i--; //To start from the previous voter again
        }
    }
    /*
    int i, j;

    for(i=0; i<voter_count; i++)
    {
        for(j=0; j<candidate_count; j++)
        {
            if(!candidates[j].eliminated)
            {
                if(preferences[i][0]==j)
                {
                    candidates[j].votes+=1;
                    //printf("Candidate %i Votes = %i", i, candidates[j].votes);
                }
            }
            if(candidates[j].eliminated==true)
            {
                if(preferences[i][j+1]==j)
                {
                    candidates[j+1].votes+=1;
                    //printf("Candidate %i Votes = %i", i, candidates[j+1].votes);
                }
            }
        }
    }
    return;
    */
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    int i;

    for(i=0; i<candidate_count; i++) //Runs through each candidate
    {
        if(!candidates[i].eliminated) //If not eliminated then...
        {
            if(candidates[i].votes>((voter_count)/2)) //If any candidate has more than 50% of the total votes they win election
            {
                printf("%s\n", candidates[i].name); //Print name of winner
                return true;
            }
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int i;
    int min=candidates[0].votes; //Sets first candidates votes to be minimum

    for(i=1; i<candidate_count; i++) //Runs through each candidate
    {
        if(!candidates[i].eliminated) //If not eliminated then...
        {
            if(candidates[i].votes<min) //If any candidate has fewer votes than first candidate, they become the minimum
            {
                min=candidates[i].votes;
            }
        }
    }
    return min; //Returns minimum votes
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    int i;
    for(i=0; i<candidate_count; i++) //Runs through each candidate
    {
        if(!candidates[i].eliminated) //If candidate not eliminated then...
        {
            if(candidates[i].votes!=min) //If any candidate does not have minimum number of votes it cant be a tie
            {
                return false; //Returns false if not a tie
            }
        }
    }
    return true; //Only if all candidates have minimum number of votes it will return true and will be a tie
}

// Eliminate the candidate (or candidiates) in last place
void eliminate(int min)
{
    int i;

    for(i=0; i<candidate_count; i++) //Runs through each candidate
    {
        if(candidates[i].votes==min) //If candidate has minimum number of votes then...
        {
            candidates[i].eliminated=true; //Elimination status of candidate is set to true and candidate is eliminated
        }
    }
    return;
}
