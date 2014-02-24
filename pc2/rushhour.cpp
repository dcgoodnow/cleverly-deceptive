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
	
int main()
{
	int size;
	cin >> size;
	car* grid = new car[size];
	for( int i = 0; i < size; i++)
	{
		cin >> grid[i].length;
		cin >> grid[i].orientation;
		cin >> grid[i].xPos;
		cin >> grid[i].yPos;
	}

}

bool moveForward(car* cars, int carNumber)
{
	switch(cars[carNumber].orientation)
	{
		case 'H':
			if(cars[carNumber].xPos + cars[carNumber].length != 7)
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
