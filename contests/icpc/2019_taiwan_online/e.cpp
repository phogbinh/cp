#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int g_nMinX;
void FindMinX()
{
    g_nMinX = INT_MAX;
    for ( int i = 0; i < g_n; i++ )
    {
        if ( g_kPoints[ i ].first < g_nMinX )
        {
            g_nMinX = g_kPoints[ i ].first;
        }
    }
}

int g_nMaxX;
void FindMaxX()
{
    g_nMaxX = 0;
    for ( int i = 0; i < g_n; i++ )
    {
        if ( g_kPoints[ i ].first > g_nMaxX )
        {
            g_nMaxX = g_kPoints[ i ].first;
        }
    }
}

int g_nMinY;
void FindMinY()
{
    g_nMinY = INT_MAX;
    for ( int i = 0; i < g_n; i++ )
    {
        if ( g_kPoints[ i ].second < g_nMinY )
        {
            g_nMinY = g_kPoints[ i ].second;
        }
    }
}

int g_nMaxY;
void FindMaxY()
{
    g_nMaxY = 0;
    for ( int i = 0; i < g_n; i++ )
    {
        if ( g_kPoints[ i ].second > g_nMaxY )
        {
            g_nMaxY = g_kPoints[ i ].second;
        }
    }
}

int g_nMinYOfMinX;
void FindMinYOfMinX()
{
    g_nMinYOfMinX = INT_MAX;
    for ( int i = 0; i < g_n; i++ )
    {
        if ( g_kPoints[ i ].first == g_nMinX && g_kPoints[ i ].second < g_nMinYOfMinX )
        {
            g_nMinYOfMinX = g_kPoints[ i ].second;
        }
    }
}

int g_nMaxYOfMinX;
void FindMaxYOfMinX()
{
    g_nMaxYOfMinX = 0;
    for ( int i = 0; i < g_n; i++ )
    {
        if ( g_kPoints[ i ].first == g_nMinX && g_kPoints[ i ].second > g_nMaxYOfMinX )
        {
            g_nMaxYOfMinX = g_kPoints[ i ].second;
        }
    }
}

int g_nMinYOfMaxX;
void FindMinYOfMaxX()
{
    g_nMinYOfMaxX = INT_MAX;
    for ( int i = 0; i < g_n; i++ )
    {
        if ( g_kPoints[ i ].first == g_nMaxX && g_kPoints[ i ].second < g_nMinYOfMaxX )
        {
            g_nMinYOfMaxX = g_kPoints[ i ].second;
        }
    }
}

int g_nMaxYOfMaxX;
void FindMaxYOfMaxX()
{
    g_nMaxYOfMaxX = 0;
    for ( int i = 0; i < g_n; i++ )
    {
        if ( g_kPoints[ i ].first == g_nMaxX && g_kPoints[ i ].second > g_nMaxYOfMaxX )
        {
            g_nMaxYOfMaxX = g_kPoints[ i ].second;
        }
    }
}

int g_nMinXOfMinY;
void FindMinXOfMinY()
{
    g_nMinXOfMinY = INT_MAX;
    for ( int i = 0; i < g_n; i++ )
    {
        if ( g_kPoints[ i ].second == g_nMinY && g_kPoints[ i ].first < g_nMinXOfMinY )
        {
            g_nMinXOfMinY = g_kPoints[ i ].first;
        }
    }
}

int g_nMaxXOfMinY;
void FindMaxXOfMinY()
{
    g_nMaxXOfMinY = 0;
    for ( int i = 0; i < g_n; i++ )
    {
        if ( g_kPoints[ i ].second == g_nMinY && g_kPoints[ i ].first > g_nMaxXOfMinY )
        {
            g_nMaxXOfMinY = g_kPoints[ i ].first;
        }
    }
}

int g_nMinXOfMaxY;
void FindMinXOfMaxY()
{
    g_nMinXOfMaxY = INT_MAX;
    for ( int i = 0; i < g_n; i++ )
    {
        if ( g_kPoints[ i ].second == g_nMaxY && g_kPoints[ i ].first < g_nMinXOfMaxY )
        {
            g_nMinXOfMaxY = g_kPoints[ i ].first;
        }
    }
}

int g_nMaxXOfMax;
void FindMaxXOfMaxY()
{
    g_nMaxXOfMax = 0;
    for ( int i = 0; i < g_n; i++ )
    {
        if ( g_kPoints[ i ].second == g_nMaxY && g_kPoints[ i ].first > g_nMaxXOfMax )
        {
            g_nMaxXOfMax = g_kPoints[ i ].first;
        }
    }
}

vector<pair<int, int>> g_kPoints;
int g_n;
int main()
{

    cin >> g_n;
    for ( int i = 0; i < g_n; i++ )
    {
        int nX;
        int nY;
        cin >> nX;
        cin >> nY;
        g_kPoints.push_back( make_pair( nX, nY ) );
    }

    // min/ max x
    FindMinX();
    FindMaxX();
    // min/ max y
    FindMinY();
    FindMaxY();
    // ( min_x, ? )
    FindMinYOfMinX();
    FindMaxYOfMinX();
    // ( max_x, ? )
    FindMinYOfMaxX();
    FindMaxYOfMaxX();
    // ( ?, min_y )
    FindMinXOfMinY();
    FindMaxXOfMinY();
    // ( , max_y )
    FindMinXOfMaxY();
    FindMaxXOfMaxY();

    cout << "Min X: " << g_nMinX << endl;
    cout << "Max X:" << g_nMaxX << endl;
    system( "pause" );
}