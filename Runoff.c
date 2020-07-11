#include<cs50.h>
#include<string.h>
#include<stdio.h>

bool vote (int i, int n, string s);
void tabulate (void);
int min (void);
bool print (void);
bool tie (int x);
void eliminate (int x);

#define MAX_c 9
#define MAX_v 100

typedef struct
{
    string name ;
    int votes ;
    bool eliminated ;
}
candidates;
candidates candidate [MAX_c];

int v ; int c ;
int voters[MAX_v][MAX_c];

int main (int argc , string argv[])
{
    c = argc - 1 ;
    if (c > MAX_c)
    { printf("Maximum number of candidates is %i\n", MAX_c); return 1 ; }

     v = get_int("Number of voters: ");
    if (v > MAX_v)
    { printf("Maximum number of voters is %i\n", MAX_v); return 2 ; }

    for(int i = 0; i <= c; i++)
    {
        candidate[i].name = argv[i+1];
        candidate[i].votes = 0;
        candidate[i].eliminated = false ;
    }
    //voters[v][c];
    //.......................................................................................
    for(int i = 1; i <= v; i++)
    {
        for(int n = 1; n <= c; n++)
        {
            string s = get_string("Rank %i: ", n);
            if (vote(i-1, n, s) == false)
            {
                  printf("Invalid vote.\n");
                  return 3;
            }
        }
        printf("\n");
    }
    while (true)
    {
        tabulate();

        if(print())
          printf("\n");
          break;

        int m = min();
        if (tie(m))
        {
            for (int i = 0; i < c; i++)
            {
                if (candidate[i].eliminated == false)
                {
                    printf("%s\n", candidate[i].name);
                }
            }
            break;
        }

        eliminate(m);
    }

    return 0;
}

bool vote(int i, int n, string s)
{
    for (int t = 0; t <= c; t++)
    {
        if(strcmp(s,candidate[t].name) == 0)
           voters[i][n] = t;
           return true;
    }
    printf("invailed vote");
    return false;
}

void tabulate (void)
{
    for(int i = 0; i <= v ; i++)
    {
        if(candidate[voters[i][0]].eliminated == false)
          candidate[voters[i][0]].votes ++ ;
        else
        {
            for (int g = 0 ; g <= c; g++)
            {
                if(candidate[voters[i][g]].eliminated == false)
                    candidate[voters[i][g]].votes ++ ;
            }
        }
    }
}

int min (void)
{
    int x;
    for(int i = 0; i <= c; i++)
    {
        if(candidate[i].eliminated == false)
          x = candidate[i].votes;
    }
    for(int i = 0; i <= c; i++)
    {
        if(candidate[i].votes <= x)
          x = candidate[i].votes;
    }
    return x;
}

bool print(void)
{
    for(int i = 0; i <= c; i++)
    {
        if(candidate[i].votes > v/2)
          printf("%s", candidate[i].name); return true;
          printf("\n");

    }
    return false ;
}

void eliminate (int x)
{
    for(int i = 0; i <= c ; i++)
    {
        if(candidate[i].eliminated==false && candidate[i].votes == x)
           candidate[i].eliminated = true;
    }
}

bool tie (int x)
{
    bool b = true ;
    for(int i = 0; i <=c ; i++)
    {
        if(candidate[i].eliminated == false && candidate[i].votes != x)
        {
            b = false;
        }
    }
    return b ;
}

