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
#include <string>


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

/*
 * @name Make String
 * @brief converts a 2d array of characters into a string (1d array of chars)
 *
 * @param toString 2d array to convert
 *
 * @retval the string to return
*/
string makeString(char**);


struct puzzle{
	char** board;
	car* grid;
	int moves;
};

/*
 * @name Copy Puzzle
 * @brief copies all values of one puzzle to another
 *
 * @param a puzzle to copy from
 * @param b puzzle to copy to
 * @param size Number of cars in puzzle
 *
*/
void copyPuzzle(puzzle a, puzzle&  b, int size);

/**
 * @name Check Solution
 * @brief checks if a puzzle is a solution to the puzzle
 *
 * @param test the puzzle to be tested
 * @retval True if the solution, false if not
*/
bool checkSoln(puzzle& test);
	
int main()
{
	int size;
	int scenario = 1;
	queue<puzzle> boards;
	map<string, int> dejaVu;
	cin >> size;
	puzzle attempt;
	while(size != 0)
	{
		attempt.grid = new car[size];
		attempt.board = new char*[8];
		attempt.moves = 0;
		for(int i = 0; i < 8; i++)
		{
			attempt.board[i] = new char[8];
		}
		for(int i = 0; i < 8; i++)
		{
			for(int j = 0; j<8; j++)
			{
				if(i == 0 || i==7 || j==0 || j==7)
				{
					attempt.board[i][j] = 'x';
				}
				else
				{
					attempt.board[i][j] = ' ';
				}
			}
		}
		for( int i = 0; i < size; i++)
		{
			cin >> attempt.grid[i].length;
			cin >> attempt.grid[i].orientation;
			cin >> attempt.grid[i].yPos;
			attempt.grid[i].yPos++;
			cin >> attempt.grid[i].xPos;
			attempt.grid[i].xPos++;
			attempt.board[attempt.grid[i].xPos][attempt.grid[i].yPos] = 'x';
			if(attempt.grid[i].orientation == 'H')
			{
				if(attempt.grid[i].length == 2)
				{
					attempt.board[attempt.grid[i].xPos+1][attempt.grid[i].yPos] = 'x';
				}
				else
				{
					attempt.board[attempt.grid[i].xPos+1][attempt.grid[i].yPos] = 'x';
					attempt.board[attempt.grid[i].xPos+2][attempt.grid[i].yPos] = 'x';
				}
			}
			else
			{
				if(attempt.grid[i].length == 2)
				{
					attempt.board[attempt.grid[i].xPos][attempt.grid[i].yPos+1] = 'x';
				}
				if(attempt.grid[i].length == 3)
				{
					attempt.board[attempt.grid[i].xPos][attempt.grid[i].yPos+1] = 'x';
					attempt.board[attempt.grid[i].xPos][attempt.grid[i].yPos+2] = 'x';
				}
			}
		}
		string key = makeString(attempt.board);
		boards.push(attempt);
		dejaVu.insert(pair<string, int>(key,1));
		puzzle temp, forward, backward;

		while(!boards.empty())
		{
			
			copyPuzzle(boards.front(), temp, size);
			boards.pop();
			if(checkSoln(temp) ||temp.moves == 40)
			{
				cout << "Scenario " << scenario << " requires " << temp.moves 
					  << " moves" << endl;
				break;
			}
			for(int i = 0; i < size; i++)
			{
				copyPuzzle(temp, forward, size);
				copyPuzzle(temp, backward, size);
				if(moveForward(forward.grid, i, forward.board))
				{
					string forwardKey = makeString(forward.board);
					map<string, int>::iterator it;
					it = dejaVu.find(forwardKey);
					if(it == dejaVu.end())
					{
						forward.moves++;
						boards.push(forward);
						dejaVu.insert(pair<string, int>(forwardKey,1));
					}
				}
				if(moveBackward(backward.grid, i, backward.board))
				{
					string backwardKey = makeString(backward.board);
					map<string, int>::iterator it;
					it = dejaVu.find(backwardKey);
					if(it == dejaVu.end())
					{
						backward.moves++;
						boards.push(backward);
						dejaVu.insert(pair<string, int>(backwardKey,1));
					}
				}
			}
		}

		while(!boards.empty())
		{
			boards.pop();
		}
		cin >> size;
		delete[] attempt.grid;
		for(int i = 0; i < 8; i++)
		{
			delete[] attempt.board[i];
		}
		delete[] attempt.board;
		attempt.grid = NULL;
		attempt.board = NULL;
		delete[] forward.grid;
		for(int i = 0; i < 8; i++)
		{
			delete[] forward.board[i];
		}
		delete[] forward.board;
		forward.grid = NULL;
		forward.board = NULL;
		delete[] backward.grid;
		for(int i = 0; i < 8; i++)
		{
			delete[] backward.board[i];
		}
		delete[] backward.board;
		backward.grid = NULL;
		backward.board = NULL;
		scenario++;
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

string makeString(char** b)
{
	string temp;
	for(int i = 0; i < 8; i++)
	{
		temp += b[i];
	}
	return temp;
}
void copyPuzzle(puzzle a, puzzle  &b, int size)
{
	b.grid = new car[size];
	b.board = new char*[8];
	b.moves = a.moves;

	for(int i = 0; i < size; i++)
	{
		b.grid[i].xPos = a.grid[i].xPos;
		b.grid[i].yPos = a.grid[i].yPos;
		b.grid[i].length = a.grid[i].length;
		b.grid[i].orientation = a.grid[i].orientation;
	}
	for(int i = 0; i < 8; i++)
	{
		b.board[i] = new char[8];
		for(int j = 0; j < 8; j++)
		{
			b.board[i][j] = a.board[i][j];
		}
	}
}

bool checkSoln(puzzle &test)
{
	if(test.grid[0].xPos == 5)
	{
		return true;
	}
	return false;
}
