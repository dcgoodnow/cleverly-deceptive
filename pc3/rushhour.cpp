/**
 * @file rushhour.cpp
 * @author Daniel Goodnow
 *
 * @mainpage A simple solution finder that models the popular commercial puzzle
 * game Rush Hour.
 *
 * @detail The program accepts a string of input which describes the layout of
 * the puzzle. It then builds a visual representation of the puzzle board and 
 * uses a recursive algorithm to find the simplest solution to the puzzle. The
 * current implementation only finds solutions that are possible in under 10 
 * moves.
*/

#include <iostream>
#include <queue>
#include <algorithm>
#include <map>


using namespace std;

/**
 * @name car
 * @param xPos Holds the starting x position of a car.
 * @param yPos Holds the starting y position of a car.
 * @param length Length of the car
 * @param orientation Orientation of the car ('H' or 'V').
**/
struct car{
	int xPos;
	int yPos;
	int length;
	char orientation;
};

/**
 * @name Move Forward
 * @brief Moves the specified car forward (if possible)
 * @detail Tests to see if it is possible to move a car forward, if it is, the
 *	car is moved and the board is updated.
 *
 *	@param cars Array of cars for the scenario.
 *	@param carNumber Number of the car to move.
 *	@param board 'Visual' representation of the playing board.
 *
 *	@return True if the car was able to be moved; false if not.
 *
 *	@pre Cars and playing board have been loaded and created.
 *	@post Specified car is moved forward if possible.
**/
bool moveForward(car*, int, char**);

/**
 * @name Move Backward
 * @brief Moves the specified car backward (if possible)
 * @detail Tests to see if it is possible to move a car backward, if it is, the
 *	car is moved and the board is updated.
 *
 *	@param cars Array of cars for the scenario.
 *	@param carNumber Number of the car to move.
 *	@param board 'Visual' representation of the playing board.
 *
 *	@return True if the car was able to be moved; false if not.
 *
 *	@pre Cars and playing board have been loaded and created.
 *	@post Specified car is moved backward if possible.
**/
bool moveBackward(car*, int, char**);

/**
 * @name Solve
 * @brief Finds the shortest possible combination of moves to solve the scenario.
 * @detail Uses a recursive algorithm to perform a depth first search of all
 * possible outcomes of every move on the playing board.
 *
 * @algorithm Tests for the stopping conditions of the first car reaching the 
 * edge of the board or the number of moves exceeding the best yet moves, or 
 * 10 moves, whichever is smaller. If the stopping condition is not met, it 
 * loops through all the cars in the array of cars testing a forward and backward
 * move for each car. If a move is possible, the function is called recursively.
 * If a solution is found, the best moves is updated to the current number of moves.
 *
 * @param cars The array of cars.
 * @param board The 'visual' representation of the board.
 * @param numCars Number of cars in the scenario.
 * @param best The number of moves found in the best solution so far.
 * @param moves The current number of moves for a given attempt.
 *
 * @return True if a solution is found; false if moves exceeds the best solution
 * so far.
 *
 * @pre The car and board must be loaded, best initialized to the maximum
 * number of moves, moves initialized.
 * @post A solution is provided.
 *
**/
bool solve(car*, char**, int, int&, int&);

/**
 * @name Print Grid
 * @brief Prints a visual representation of the playing board.
 * @detail Loops through the two-dimensional board array printing each column
 * of each row.
 *
 * @param toPrint The board to be printed
 *
 * @pre Board is loaded.
 * @post Board is printed to stdout.
**/
void printGrid(char**);
	
int main()
{
	int size;
	int scenario = 1;
	queue<char**> boards;
	cin >> size;
	while(size != 0)
	{
		car* grid = new car[size];
		char** board = new char*[8];
		for(int i = 0; i < 8; i++)
		{
			board[i] = new char[8];
		}
		for(int i = 0; i < 8; i++)
		{
			for(int j = 0; j<8; j++)
			{
				if(i == 0 || i==7 || j==0 || j==7)
				{
					board[i][j] = 'x';
				}
				else
				{
					board[i][j] = ' ';
				}
			}
		}
		for( int i = 0; i < size; i++)
		{
			cin >> grid[i].length;
			cin >> grid[i].orientation;
			cin >> grid[i].yPos;
			grid[i].yPos++;
			cin >> grid[i].xPos;
			grid[i].xPos++;
			board[grid[i].xPos][grid[i].yPos] = 'x';
			if(grid[i].orientation == 'H')
			{
				if(grid[i].length == 2)
				{
					board[grid[i].xPos+1][grid[i].yPos] = 'x';
				}
				else
				{
					board[grid[i].xPos+1][grid[i].yPos] = 'x';
					board[grid[i].xPos+2][grid[i].yPos] = 'x';
				}
			}
			else
			{
				if(grid[i].length == 2)
				{
					board[grid[i].xPos][grid[i].yPos+1] = 'x';
				}
				if(grid[i].length == 3)
				{
					board[grid[i].xPos][grid[i].yPos+1] = 'x';
					board[grid[i].xPos][grid[i].yPos+2] = 'x';
				}
			}
		}
		int best = 10;
		int moves = 0;
		if(solve(grid, board, size, best, moves))
		{
		}
		cout << "Scenario " << scenario << " requires " << best 
			  << " moves" << endl;
		scenario++;
		cin >> size;
		delete[] grid;
		for(int i = 0; i < 8; i++)
		{
			delete[] board[i];
		}
	}
}

bool moveForward(car* cars, int carNumber, char** board)
{
	switch(cars[carNumber].orientation)
	{
		case 'H':
			if(board[cars[carNumber].xPos + cars[carNumber].length ]
					  [cars[carNumber].yPos] != 'x')
			{
				board[cars[carNumber].xPos + cars[carNumber].length]
							[cars[carNumber].yPos]	= 'x';
				board[cars[carNumber].xPos][cars[carNumber].yPos] = ' ';
				cars[carNumber].xPos++;
				return true;
			}
			else
			{
				return false;
			}
			break;

		case 'V':
			if(board[cars[carNumber].xPos]
					  [cars[carNumber].yPos + cars[carNumber].length ] != 'x')
			{
				board[cars[carNumber].xPos]
							 [cars[carNumber].yPos + cars[carNumber].length]	= 'x';
				board[cars[carNumber].xPos][cars[carNumber].yPos] = ' ';
				cars[carNumber].yPos++;
				return true;
			}
			else
			{
				return false;
			}
			break;
		default:
			return false;
	}
}

bool moveBackward(car* cars, int carNumber, char** board)
{
	switch(cars[carNumber].orientation)
	{
		case 'H':
			if(board[cars[carNumber].xPos-1][cars[carNumber].yPos] != 'x')
			{
				board[cars[carNumber].xPos-1][cars[carNumber].yPos] = 'x';
				cars[carNumber].xPos--;
				board[cars[carNumber].xPos+cars[carNumber].length]
					  [cars[carNumber].yPos] = ' ';
				return true;
			}
			else
			{
				return false;
			}
			break;

		case 'V':
			if(board[cars[carNumber].xPos][cars[carNumber].yPos - 1] != 'x')
			{
				board[cars[carNumber].xPos][cars[carNumber].yPos-1] = 'x';
				cars[carNumber].yPos--;
				board[cars[carNumber].xPos]
					  [cars[carNumber].yPos+cars[carNumber].length] = ' ';
				return true;
			}
			else
			{
				return false;
			}
			break;
		default:
			return false;
	}
}

bool solve(car* cars, char** board, int numCars, int& best, int& moves)
{
	if(cars[0].xPos == 5)
	{
		best = moves;
		return true;
	}
	else if(moves >= best)
	{
		return false;
	}
	for(int i = 0; i<numCars; i++)
	{
		if(moveForward(cars, i, board))
		{
			moves++;
			solve( cars, board, numCars, best, moves);
			moveBackward(cars, i, board);
		}
		if(moveBackward(cars, i, board))
		{
			moves++;
			solve( cars, board, numCars, best, moves);
			moveForward(cars, i, board);
		}
	}
}


void printGrid(char** toPrint)
{
	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			cout << toPrint[j][i];
		}
		cout << endl;
	}
}
