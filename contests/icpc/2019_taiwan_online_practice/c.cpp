#include <iostream>
#include <vector>

using namespace std;

class Box
{
public:
    Box()
    {
        /* Body intentionally empty */
    }

    Box( const int nValue ) : m_nValue( nValue )
    {
        /* Body intentionally empty */
    }

    void SetLeft( Box* pBox )
    {
        m_pLeft = pBox;
    }

    void SetRight( Box* pBox )
    {
        m_pRight = pBox;
    }

    Box* GetLeftBox()
    {
        return m_pLeft;
    }

    Box* GetRightBox()
    {
        return m_pRight;
    }

    int GetValue() const
    {
        return m_nValue;
    }

private:
    int m_nValue;
    Box* m_pLeft;
    Box* m_pRight;
};

int g_nBoxesCount;
vector<Box> g_kBoxes;
const int FIRST_BOX_INDEX = 1;
const int COMMAND_ONE = 1;
const int COMMAND_TWO = 2;
const int COMMAND_THREE = 3;
const int COMMAND_FOUR = 4;

void InitializeAllBoxes()
{
    // Initialize all boxes, including the starting ( 0 ) and the ending ( n + 1 ) boxes
    for ( int i = 0; i <= g_nBoxesCount + 1; i++ )
    {
        g_kBoxes.push_back( Box( i ) );
    }
}

void InitializeBoxRelationships()
{
    // Set relationship of starting box
    g_kBoxes[ 0 ].SetLeft( &g_kBoxes[ g_nBoxesCount + 1 ] );
    g_kBoxes[ 0 ].SetRight( &g_kBoxes[ FIRST_BOX_INDEX ] );
    // Set relationship of ending box
    g_kBoxes[ g_nBoxesCount + 1 ].SetLeft( &g_kBoxes[ g_nBoxesCount ] );
    g_kBoxes[ g_nBoxesCount + 1 ].SetRight( &g_kBoxes[ 0 ] );

    // Set relationship of other boxes
    for ( int i = FIRST_BOX_INDEX; i <= g_nBoxesCount; i++ )
    {
        g_kBoxes[ i ].SetLeft( &g_kBoxes[ i - 1 ] );
        g_kBoxes[ i ].SetRight( &g_kBoxes[ i + 1 ] );
    }
}

void Initialize()
{
    g_kBoxes.clear();
    InitializeAllBoxes();
    InitializeBoxRelationships();
}

void DoOneTwoCommon( int nX, int nY )
{
    g_kBoxes[ nX ].GetLeftBox()->SetRight( g_kBoxes[ nX ].GetRightBox() );
    g_kBoxes[ nX ].GetRightBox()->SetLeft( g_kBoxes[ nX ].GetLeftBox() );
}

void DoOne()
{
    int nX, nY;
    cin >> nX;
    cin >> nY;
    // 1
    DoOneTwoCommon( nX, nY );
    // 2
    g_kBoxes[ nY ].GetLeftBox()->SetRight( &g_kBoxes[ nX ] );
    g_kBoxes[ nX ].SetLeft( g_kBoxes[ nY ].GetLeftBox() );
    // 3
    g_kBoxes[ nX ].SetRight( &g_kBoxes[ nY ] );
    g_kBoxes[ nY ].SetLeft( &g_kBoxes[ nX ] );
}

void DoTwo()
{
    int nX, nY;
    cin >> nX;
    cin >> nY;
    // 1
    DoOneTwoCommon( nX, nY );
    // 2
    g_kBoxes[ nY ].GetRightBox()->SetLeft( &g_kBoxes[ nX ] );
    g_kBoxes[ nX ].SetRight( g_kBoxes[ nY ].GetRightBox() );
    // 3
    g_kBoxes[ nX ].SetLeft( &g_kBoxes[ nY ] );
    g_kBoxes[ nY ].SetRight( &g_kBoxes[ nX ] );
}

void DoThree()
{
    int nX, nY;
    cin >> nX;
    cin >> nY;
    // 1.1
    Box* pXLeftBox = g_kBoxes[ nX ].GetLeftBox();
    Box* pXRightBox = g_kBoxes[ nX ].GetRightBox();
    // 1.2
    Box* pYLeftBox = g_kBoxes[ nY ].GetLeftBox();
    Box* pYRightBox = g_kBoxes[ nY ].GetRightBox();
    // 2.1
    g_kBoxes[ nX ].SetLeft( pYLeftBox );
    g_kBoxes[ nX ].SetRight( pYRightBox );
    // 2.2
    g_kBoxes[ nY ].SetLeft( pXLeftBox );
    g_kBoxes[ nY ].SetRight( pXRightBox );
    // 3.1
    pXLeftBox->SetRight( &g_kBoxes[ nY ] );
    pXRightBox->SetLeft( &g_kBoxes[ nY ] );
    // 3.2
    pYLeftBox->SetRight( &g_kBoxes[ nX ] );
    pYRightBox->SetLeft( &g_kBoxes[ nX ] );
}

void DoFour()
{
    for ( int i = 0; i <= g_nBoxesCount + 1; i++ )
    {
        Box* pLeftBox = g_kBoxes[ i ].GetLeftBox();
        Box* pRightBox = g_kBoxes[ i ].GetRightBox();
        g_kBoxes[ i ].SetLeft( pRightBox );
        g_kBoxes[ i ].SetRight( pLeftBox );
    }
}

void ProcessCommands()
{
    int nCommandsCount;
    cin >> nCommandsCount;
    for ( int i = 0; i < nCommandsCount; i++ )
    {
        int nCommand;
        cin >> nCommand;
        switch ( nCommand )
        {
            case COMMAND_ONE:
                DoOne();
                break;
            case COMMAND_TWO:
                DoTwo();
                break;
            case COMMAND_THREE:
                DoThree();
                break;
            case COMMAND_FOUR:
                DoFour();
                break;
            default:
                throw "Command not found.";
        }
    }
}

void PrintResult()
{
    Box* pStartBox;
    Box* pEndBox;
    if ( g_kBoxes[ 0 ].GetRightBox() == &g_kBoxes[ g_nBoxesCount + 1 ] )
    {
        // Right -> Left
        pStartBox = &g_kBoxes[ g_nBoxesCount + 1 ];
        pEndBox = &g_kBoxes[ 0 ];
    }
    else
    {
        // Left -> Right
        pStartBox = &g_kBoxes[ 0 ];
        pEndBox = &g_kBoxes[ g_nBoxesCount + 1 ];
    }

    Box* pCurrentBox = pStartBox;
    int nCount = 0;
    long long int nResult = 0;
    while ( true )
    {
        pCurrentBox = pCurrentBox->GetRightBox();
        if ( pCurrentBox == pEndBox )
        {
            break;
        }
        nCount++;
        if ( nCount % 2 == 1 )
        {
            nResult += ( long long int ) pCurrentBox->GetValue();
        }
    }
    cout << nResult << endl;
}

void Solve()
{
    Initialize();
    ProcessCommands();
    PrintResult();
}

int main( int argc, char* argv[] )
{
    while ( cin >> g_nBoxesCount )
    {
        Solve();
    }
}