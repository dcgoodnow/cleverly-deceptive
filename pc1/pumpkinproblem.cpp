#include <iostream>
#include "ListLinked.cpp"
#include <vector>
using namespace std;

void printGrid(char**, int, int);
bool findPumpkin(char** g, int rows, int cols, int &pRow, int &pCol);
int getSize(char** g, int row, int col);
void printPumpkins(char** g, int rows, int cols);

int main()
{
	char input;
	int numRows, numCols;
	cout << "Number of rows: ";
	cin >> numRows;
	cout << numRows << endl;
	cout << "Number of columns: ";
	cin >> numCols;
	cout << numCols << endl;
	char **grid;
	int fRow, fCol;
	int count = 0;

	while( numRows != 0 || numCols != 0 )
	{
		grid = new char*[numRows+2];
		for(int i = 0; i < numRows+2; i++)
		{
			grid[i] = new char[numCols+2];
			if(i == 0 || i == numRows+1)
			{
				for(int j = 0; j < numCols+2; j++)
				{
					grid[i][j]='x';
				}
			}
			else
			{
				grid[i][0] = 'x';
				for(int j = 1; j <= numCols; j++)
				{
					cin >> grid[i][j];
				}
				grid[i][numCols+1] = 'x';
			}

		}
//		printGrid(grid, numRows, numCols);
		cout << endl;
		cout << endl;

		count = 0;
		bool found = true;
		vector<int> patches(5);
		while(found)
		{
			found = findPumpkin(grid, numRows, numCols, fRow, fCol);
			if(found)
			{
				patches[count] = getSize(grid, fRow, fCol);
				count++;
			}
		}
		cout << endl;
		cout << "There were " << count << " patches found. ";
		cout << "Sizes: ";
		for(int i = 0; i<count; i++)
		{
			cout << patches[i] << ' ';
		}
		cout << endl;
		cin >>numRows;
		cin >> numCols;
		patches.clear();
	}
	return 0;
}

void printGrid(char** g, int rows, int cols)
{
	for(int i = 0; i < rows+2; i++)
	{
		cout << g[i] << endl;
	}
}

void printPumpkins(char** g, int rows, int cols)
{
	for(int i = 1; i < rows+1; i++)
	{
		for(int j = 1; j<cols+1; j++)
		{
			if(g[i][j] == 'x')
			{
				cout << 'x';
			}
			else cout << ' ';
		}
		cout << endl;
	}
}


bool findPumpkin(char** g, int rows, int cols, int &pRow, int &pCol)
{
	for(int i = 1; i< rows+1; i++ )
	{
		for(int j = 1; j < cols+1; j++)
		{
			
			if(g[i][j] == 'p')
			{
				pRow = i;
				pCol = j;
				return true;
			}
		}
	}
	return false;
}
int getSize(char** g, int row, int col)
{
	int count = 0;
	if(g[row][col] == 'p')
	{
		g[row][col] = 'x';
		count++;
		count += getSize(g, row+1, col);
		count += getSize(g, row-1, col);
		count += getSize(g, row, col+1);
		count += getSize(g, row, col-1);
	}
	return count;
}
