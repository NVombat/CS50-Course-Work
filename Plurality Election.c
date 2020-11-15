#include <stdio.h>
#include <string.h>
#include <cs50.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[]) //Command Line Arguments
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1; //Argc stores number of command line arguments
    if (candidate_count > MAX) //Make sure candidates are not in excess
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++) //Updating structure
    {
        candidates[i].name = argv[i + 1]; //Updates names in struct - Argv stores CLA in string format
        candidates[i].votes = 0; //Sets votes to 0
    }

    int voter_count = get_int("Number of voters: "); //Gets number of voters from user

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    int i;

    for(i=0; i<candidate_count; i++) //Runs through each candidate
    {
        if(strcmp(name,candidates[i].name)==0) //Compares voters choice with name of candidates
        {
            candidates[i].votes += 1; //If name matches then vote is valid and that candidates vote is also added/updated
            return true;
        }
    }
    return false; //If name does not match then vote is invalid
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    //Find Max number of votes any candidate has
    int max=candidates[0].votes; //Sets first candidate as the max number of votes

    for (int i = 1; i < candidate_count; i++)
    {
        if(max<candidates[i].votes) //Checks whole candidate list to see if any candidate has more votes
        max=candidates[i].votes; //If yes ^ then it sets max as that particular value of votes
    }

    for (int i = 0; i < candidate_count; i++) //Runs through candidates
    {
        if(candidates[i].votes==max) //If a candidate has max number of votes - It means no one has more votes than him
        printf("%s\n", candidates[i].name); //That candidate is the winner - name is printed
    }
    //There can be multiple winners as multiple candidates can have max number of votes

    return;
}
