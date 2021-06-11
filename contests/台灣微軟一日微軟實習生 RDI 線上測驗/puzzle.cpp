#include <iostream>
#include <bitset>
#include <string>
#include <vector>

using namespace std;

const int PUZZLE_PIECE_SIDE = 3;
const int PUZZLE_PIECE_BITSET_SIZE = PUZZLE_PIECE_SIDE * PUZZLE_PIECE_SIDE;
const char PUZZLE_ASTERISK = '*';
const char PUZZLE_DOT = '.';
const string ERROR_PUZZLE_PIECE_VALUE_IS_INVALID = "The given puzzle piece value is invalid";

void GetInputPuzzlePiece( char pPuzzlePiece[][ PUZZLE_PIECE_SIDE ] )
{
    for ( int nRow = 0; nRow < PUZZLE_PIECE_SIDE; nRow++ )
    {
        for ( int nColumn = 0; nColumn < PUZZLE_PIECE_SIDE; nColumn++ )
        {
            cin >> pPuzzlePiece[ nRow ][ nColumn ];
        }
    }
}

void PrintPuzzlePiece( char pPuzzlePiece[][ PUZZLE_PIECE_SIDE ] )
{
    for ( int nRow = 0; nRow < PUZZLE_PIECE_SIDE; nRow++ )
    {
        for ( int nColumn = 0; nColumn < PUZZLE_PIECE_SIDE; nColumn++ )
        {
            cout << pPuzzlePiece[ nRow ][ nColumn ];
        }
        cout << endl;
    }
}

void GetInputData( char pFirstPuzzlePiece[][ PUZZLE_PIECE_SIDE ], char pSecondPuzzlePiece[][ PUZZLE_PIECE_SIDE ] )
{
    GetInputPuzzlePiece( pFirstPuzzlePiece );
    GetInputPuzzlePiece( pSecondPuzzlePiece );
}

bitset< PUZZLE_PIECE_BITSET_SIZE > GetBitset( char pPuzzlePiece[][ PUZZLE_PIECE_SIDE ] )
{
    bitset< PUZZLE_PIECE_BITSET_SIZE > kPuzzlePieceBitset;
    for ( int nRow = 0; nRow < PUZZLE_PIECE_SIDE; nRow++ )
    {
        for ( int nColumn = 0; nColumn < PUZZLE_PIECE_SIDE; nColumn++ )
        {
            int nBitPosition = nRow * PUZZLE_PIECE_SIDE + nColumn;
            char kPuzzlePieceValue = pPuzzlePiece[ nRow ][ nColumn ];
            switch ( kPuzzlePieceValue )
            {
                case PUZZLE_ASTERISK:
                    kPuzzlePieceBitset[ nBitPosition ] = true;
                    break;
                case PUZZLE_DOT:
                    kPuzzlePieceBitset[ nBitPosition ] = false;
                    break;
                default:
                    throw ERROR_PUZZLE_PIECE_VALUE_IS_INVALID;
            }
        }
    }
    return kPuzzlePieceBitset;
}

bitset< PUZZLE_PIECE_BITSET_SIZE > GetNinetyDegreeRotatedBitset( bitset< PUZZLE_PIECE_BITSET_SIZE >& kPuzzlePieceBitset )
{
    bitset< PUZZLE_PIECE_BITSET_SIZE > kNinetyDegreeRotatedBitset;
    // Bit 0 - 2
    kNinetyDegreeRotatedBitset[ 0 ] = kPuzzlePieceBitset[ 6 ];
    kNinetyDegreeRotatedBitset[ 1 ] = kPuzzlePieceBitset[ 3 ];
    kNinetyDegreeRotatedBitset[ 2 ] = kPuzzlePieceBitset[ 0 ];
    // Bit 3 - 5
    kNinetyDegreeRotatedBitset[ 3 ] = kPuzzlePieceBitset[ 7 ];
    kNinetyDegreeRotatedBitset[ 4 ] = kPuzzlePieceBitset[ 4 ];
    kNinetyDegreeRotatedBitset[ 5 ] = kPuzzlePieceBitset[ 1 ];
    // Bit 6 - 8
    kNinetyDegreeRotatedBitset[ 6 ] = kPuzzlePieceBitset[ 8 ];
    kNinetyDegreeRotatedBitset[ 7 ] = kPuzzlePieceBitset[ 5 ];
    kNinetyDegreeRotatedBitset[ 8 ] = kPuzzlePieceBitset[ 2 ];
    return kNinetyDegreeRotatedBitset;
}

vector< bitset< PUZZLE_PIECE_BITSET_SIZE > > GetBitsets( char pPuzzlePiece[][ PUZZLE_PIECE_SIDE ] )
{
    vector< bitset< PUZZLE_PIECE_BITSET_SIZE > > kPuzzlePieceBitsets;
    bitset< PUZZLE_PIECE_BITSET_SIZE > kPuzzlePieceBitset = GetBitset( pPuzzlePiece );
    bitset< PUZZLE_PIECE_BITSET_SIZE > kPuzzlePieceNinetyDegreeRotatedBitset = GetNinetyDegreeRotatedBitset( kPuzzlePieceBitset );
    bitset< PUZZLE_PIECE_BITSET_SIZE > kPuzzlePieceOneHundredAndEightyDegreeRotatedBitset = GetNinetyDegreeRotatedBitset( kPuzzlePieceNinetyDegreeRotatedBitset );
    bitset< PUZZLE_PIECE_BITSET_SIZE > kPuzzlePieceTwoHundredAndSeventyDegreeRotatedBitset = GetNinetyDegreeRotatedBitset( kPuzzlePieceOneHundredAndEightyDegreeRotatedBitset );
    kPuzzlePieceBitsets.push_back( kPuzzlePieceBitset );
    kPuzzlePieceBitsets.push_back( kPuzzlePieceNinetyDegreeRotatedBitset );
    kPuzzlePieceBitsets.push_back( kPuzzlePieceOneHundredAndEightyDegreeRotatedBitset );
    kPuzzlePieceBitsets.push_back( kPuzzlePieceTwoHundredAndSeventyDegreeRotatedBitset );
    return kPuzzlePieceBitsets;
}

void Process()
{
    char kFirstPuzzlePiece[ PUZZLE_PIECE_SIDE ][ PUZZLE_PIECE_SIDE ];
    char kSecondPuzzlePiece[ PUZZLE_PIECE_SIDE ][ PUZZLE_PIECE_SIDE ];
    GetInputData( kFirstPuzzlePiece, kSecondPuzzlePiece );
    vector< bitset< PUZZLE_PIECE_BITSET_SIZE > > kFirstPuzzleBitsets = GetBitsets( kFirstPuzzlePiece );
    vector< bitset< PUZZLE_PIECE_BITSET_SIZE > > kSecondPuzzleBitsets = GetBitsets( kSecondPuzzlePiece );
    for ( auto kFirstPuzzleBitset : kFirstPuzzleBitsets )
    {
        for ( auto kSecondPuzzleBitset : kSecondPuzzleBitsets )
        {
            if ( ( kFirstPuzzleBitset ^= kSecondPuzzleBitset ).all() )
            {
                cout << "YES" << endl;
                return;
            }
        }
    }
    cout << "NO" << endl;
}

int main( int nArgc, char* pArgv[] )
{
    Process();
    return 0;
}