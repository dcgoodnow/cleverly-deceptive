/**
 * @file rushhour.cpp
 * @author Daniel Goodnow
*/

#include <iostream>

using namespace std;


struct car{
	int xPos;
	int yPos;
	int length;
	char orientation;
};

bool moveForward(car*, int, char**);

bool moveBackward(car*, int, char**);

bool solve(car*, char*[8], int, int&, int&);
	
int main()
{
	int size;
	cin >> size;
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
			if(i == 0 || i==7 || j==0 || j==8)
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
		cin >> grid[i].xPos;
		grid[i].xPos++;
		cin >> grid[i].yPos;
		grid[i].yPos++;
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
			if(grid[i].length == 2)
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
		cout << "The puzzle is solvable in " << best << " moves." << endl;
	}
}

bool moveForward(car* cars, int carNumber, char** board)
{
	switch(cars[carNumber].orientation)
	{
		case 'H':
			if(board[cars[carNumber].xPos + cars[carNumber].length -1]
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
			if(board[cars[carNumber].xPos + cars[carNumber].length -1]
					  [cars[carNumber].yPos] != 'x')
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
	}
}

bool solve(car* cars, char* board[8], int numCars, int& best, int& moves)
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
