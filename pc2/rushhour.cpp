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

bool moveForward(car*, int);

bool moveBackward(car*, int);

bool solve(car*, int, int&, int&);
	
int main()
{
	int size;
	cin >> size;
	car* grid = new car[size];
	char board[6][6]; 
	for(int i = 0; i < 6; i++)
	{
		for(int j = 0; j<6; j++)
		{
			board[i][j] = ' ';
		}
	}
	for( int i = 0; i < size; i++)
	{
		cin >> grid[i].length;
		cin >> grid[i].orientation;
		cin >> grid[i].xPos;
		cin >> grid[i].yPos;
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
	if(solve(grid, size, best, moves))
	{
		cout << "The puzzle is solvable in " << best << " moves." << endl;
	}
}

bool moveForward(car* cars, int carNumber, char[6][6] board)
{
	switch(cars[carNumber].orientation)
	{
		case 'H':
			if(cars[carNumber].xPos + cars[carNumber].length != 7 )
			{
				cars[carNumber].xPos++;
				return true;
			}
			else
			{
				return false;
			}
			break;

		case 'V':
			if(cars[carNumber].yPos + cars[carNumber].length != 7)
			{
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

bool moveBackward(car* cars, int carNumber)
{
	switch(cars[carNumber].orientation)
	{
		case 'H':
			if(cars[carNumber].xPos != 0)
			{
				cars[carNumber].xPos--;
				return true;
			}
			else
			{
				return false;
			}
			break;

		case 'V':
			if(cars[carNumber].yPos != 0)
			{
				cars[carNumber].yPos--;
				return true;
			}
			else
			{
				return false;
			}
			break;
	}
}

bool solve(car* cars, int numCars, int& best, int& moves)
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
		if(moveForward(cars, i))
		{
			moves++;
			solve( cars, numCars, best, moves);
			moveBackward(cars, i);
		}
		if(moveBackward(cars, i))
		{
			moves++;
			solve( cars, numCars, best, moves);
			moveForward(cars, i);
		}
	}
}
