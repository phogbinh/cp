#include <iostream>

using namespace std;

const string TIGER = "Tiger";
const string LION = "Lion";
const int VOTERS_COUNT = 9;
const int LEAST_VOTES_COUNT_KING = 5;

int main( int argc, char* argv[] )
{
    int nTigerVotesCount = 0;
    int nLionVotesCount = 0;

    for ( int i = 0; i < VOTERS_COUNT; i++ )
    {
        string strVoteCandidate;
        cin >> strVoteCandidate;
        if ( strVoteCandidate == TIGER )
        {
            nTigerVotesCount++;
        }
        else
        {
            nLionVotesCount++;
        }
    }
    if ( nTigerVotesCount >= LEAST_VOTES_COUNT_KING )
    {
        cout << TIGER << endl;
    }
    else if ( nLionVotesCount >= LEAST_VOTES_COUNT_KING )
    {
        cout << LION << endl;
    }
}