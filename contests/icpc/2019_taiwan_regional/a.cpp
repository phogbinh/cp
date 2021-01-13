#include <bits/stdc++.h>

#define LOCAL
#define MATRIX_SIDE 6
#define MAXIMUM_MOVES_COUNT 10
#define DIRECTIONS_COUNT 4

using namespace std;

struct state
{
	int matrix[ MATRIX_SIDE ][ MATRIX_SIDE ];
	int movesCount;

	friend bool operator<( struct state left, struct state right )
	{
		for ( int row = 0; row < MATRIX_SIDE; row++ )
		{
			for ( int col = 0; col < MATRIX_SIDE; col++ )
			{
				if ( left.matrix[ row ][ col ] != right.matrix[ row ][ col ] )
				{
					return left.matrix[ row ][ col ] < right.matrix[ row ][ col ];
				}
			}
		}
		return false; // they are the same.
	}
};

typedef struct state state_t;

struct parameter
{
	state_t state;
	int row;
	int col;
	int rowDirection;
	int colDirection;	
};

typedef struct parameter parameter_t;

set< state_t > states;
state_t initialState;
int result;
int directions[][ 2 ] = {
	-1, 0, // left
	0, 1,  // up
	1, 0,  // right
	0, -1  // down
};

void Input()
{
	for ( int row = 0; row < MATRIX_SIDE; row++ )
	{
		for ( int col = 0; col < MATRIX_SIDE; col++ )
		{
			cin >> initialState.matrix[ row ][ col ];
		}
	}
	initialState.movesCount = 2; // it takes 2 steps to move the red car standing at the exit out of the board.
}

bool IsRedCarAtExit( const state_t& currentState )
{
	return currentState.matrix[ 2 ][ 4 ] == 1 && currentState.matrix[ 2 ][ 5 ] == 1;
}

bool IsInBoard( int position )
{
	return 0 <= position && position < MATRIX_SIDE;
}

bool HasVehicle( const parameter_t& argument )
{
	int nextRow = argument.row + argument.rowDirection;
	int nextCol = argument.col + argument.colDirection;
	int nextNextRow = argument.row + 2 * argument.rowDirection;
	int nextNextCol = argument.col + 2 * argument.colDirection;
	if ( !( IsInBoard( nextRow ) && IsInBoard( nextCol ) && IsInBoard( nextNextRow ) && IsInBoard( nextNextCol ) ) )
	{
		return false;
	}
	return
	argument.state.matrix[ nextRow ][ nextCol ] != 0
	&&
	argument.state.matrix[ nextRow ][ nextCol ] == argument.state.matrix[ nextNextRow ][ nextNextCol ]; // it is at least a car.
}

void GetVehiclePosition( const parameter_t& argument, int& vehicleRow, int& vehicleCol )
{
	int nextNextRow = argument.row + 2 * argument.rowDirection;
	int nextNextCol = argument.col + 2 * argument.colDirection;
	int nextNextNextRow = argument.row + 3 * argument.rowDirection;
	int nextNextNextCol = argument.col + 3 * argument.colDirection;
	// let it be a car.
	vehicleRow = nextNextRow;
	vehicleCol = nextNextCol;
	if ( !( IsInBoard( nextNextRow ) && IsInBoard( nextNextCol ) && IsInBoard( nextNextNextRow ) && IsInBoard( nextNextNextCol ) ) )
	{
		return;
	}
	if ( argument.state.matrix[ nextNextRow ][ nextNextCol ] == argument.state.matrix[ nextNextNextRow ][ nextNextNextCol ] )
	{
		// uh oh it should be a truck.
		vehicleRow = nextNextNextRow;
		vehicleCol = nextNextNextCol;
	}
}

void Process()
{
	result = 11;
	queue< state_t > queue;
	queue.push( initialState );
	state_t currentState;
	while ( !queue.empty() )
	{
		currentState = queue.front();
		queue.pop();
		if ( IsRedCarAtExit( currentState ) )
		{
			result = min( result, currentState.movesCount );
			continue;
		}
		if ( currentState.movesCount == MAXIMUM_MOVES_COUNT )
		{
			continue;
		}
		if ( currentState.movesCount > MAXIMUM_MOVES_COUNT )
		{
			throw exception();
		}
		if ( states.count( currentState ) ) // current states already exists.
		{
			continue;
		}
		states.insert( currentState );
		for ( int row = 0; row < MATRIX_SIDE; row++ )
		{
			for ( int col = 0; col < MATRIX_SIDE; col++ )
			{
				if ( currentState.matrix[ row ][ col ] == 0 )
				{
					for ( int index = 0; index < DIRECTIONS_COUNT; index++ )
					{
						parameter_t argument;
						argument.state = currentState;
						argument.row = row;
						argument.col = col;
						argument.rowDirection = directions[ index ][ 0 ];
						argument.colDirection = directions[ index ][ 1 ];
						if ( HasVehicle( argument ) )
						{
							int vehicleRow;
							int vehicleCol;
							GetVehiclePosition( argument, vehicleRow, vehicleCol );
							state_t nextState = currentState;
							nextState.matrix[ row ][ col ] = nextState.matrix[ vehicleRow ][ vehicleCol ];
							nextState.matrix[ vehicleRow ][ vehicleCol ] = 0;
							nextState.movesCount++;
							queue.push( nextState );
						}
					}
				}
			}
		}
	}
}

int main()
{
#ifdef LOCAL
	freopen( "input_file", "r", stdin );
#endif // LOCAL
	Input();
	Process();
	cout << ( result <= MAXIMUM_MOVES_COUNT ? result : -1 ) << endl;
	return 0;
}