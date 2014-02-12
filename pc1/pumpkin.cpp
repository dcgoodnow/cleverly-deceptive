/**
 * @file pumpkin.cpp
 * @author Daniel Goodnow
 * @date February 11, 2014
 *
 * @mainpage Pumpkin Patch Finder
 * @detail This program accepts input of rectangular garden patches and
 * determines the number and size of pumpkin patches that are present in the
 * garden. It uses a simple branching recursion function to determine the sizes
 * of the patches. 
 *
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool findPumpkin(char** g, int rows, int cols, int &pRow, int &pCol);
int getSize(char** g, int row, int col);
void loadGrid( char** g, int, int);


/** 
 * @name main
 * @brief main program loop
 * @detail handles the main functionality of the program during its lifetime. 
 * It initializes a series of variables receives the first inputs, then entrers
 * a loop where it will remain until row/column input of "0 0" is entered, 
 * which will effectively terminate the program. In this loop, the pumpkin grid
 * is loaded, and then the grid is searched for pumpkin patches. Once the grid 
 * has been searched, the list of patches is sorted and output to the standard
 * output. Then the new row and column specifications are input and the grid is
 * deallocated. At this point the loop ends. 
 *
 * @pre program is uninitialized
 * @post program is terminated
*/
int main()
{
	char input;
	int numRows, numCols;
	cin >> numRows;
	cin >> numCols;
	char **grid;
	int fRow, fCol;
	int count = 0;
	int gardens = 1;
	vector<int> patches(100);

	while( numRows != 0 || numCols != 0 )
	{
		grid = new char*[numRows+2];
		loadGrid( grid, numRows, numCols);

		count = 0;
		bool found = true;

		//find patches
		while(found)
		{
			found = findPumpkin(grid, numRows, numCols, fRow, fCol);
			if(found)
			{
				patches[count] = getSize(grid, fRow, fCol);
				count++;
				if(count%100 == 0)
				{
					patches.resize(count+100);
				}
			}
		}

		//sort and print patches
		sort(patches.begin(), patches.begin() + count);
		cout << "Garden # " << gardens << ": " << count << " patches, sizes:";
		for(int i = 0; i < count; i++)
		{
			cout << ' ' << patches[i];
		}
		cout << endl;

		//delete the grid
		for(int i = 0; i < numRows+2; i++)
		{
			delete[] grid[i];
		}
		delete[] grid;
		grid = NULL;
		cin >> numRows;
		cin >> numCols;
		patches.clear();
		patches.resize(100);
		gardens++;

	}
	return 0;
}

/**
 * @name loadGrid
 * @brief Loads the garden from standard input
 * @detail Uses nested for loops to read in each character of the garden 
 * individually. Also adds a column of "x"'s on the left and right ends of the 
 * grid and a row of "x"'s to the top and bottom of the grid. This helps the 
 * prevents the getsize function from going outside the bounds of the grid
 * without using a large amount of if/else statements.
 *
 * @param g grid to load into
 * @param rows number of rows
 *	@param cols number of columns
 *
 *	@pre Grid is unallocated
 *	@post grid is allocated and filled
*/
void loadGrid( char** g, int rows, int cols)
{		
	for(int i = 0; i < rows+2; i++)
	{
		g[i] = new char[cols+2];
		if(i == 0 || i == rows+1)
		{
			for(int j = 0; j < cols+2; j++)
			{
				g[i][j]='x';
			}
		}
		else
		{
			g[i][0] = 'x';
			for(int j = 1; j <= cols; j++)
			{
				cin >> g[i][j];
			}
			g[i][cols+1] = 'x';
		}
	}
}

/**
 * @name findPumpkin
 * @brief finds the next pumpkin in the garden
 * @detail Searches through the garden grid using nested for loops and returns
 * the location of the first pumpkin it locates.
 *
 *	@param g grid to load into
 *	@param rows number of rows
 *	@param cols number of columns
 *	@param pRow row location of found pumpkin
 *	@param pCol column location of found pumpkin
 *
 *	@return true if a pumpkin is found, false if no pumpkin is found
 *
 *	@post variables used for pRow and pCol now contain value of the found
 *	pumpkin.
*/
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

/**
 * @name getSize
 * @brief finds size of the current patch
 *
 * @detail Uses a recursive algorithm to find the size of a given patch.
 *
 * @bAlgortihm Checks if the current element is a pumpkin, if not it returns 
 * the count (this is the stopping condition). If it is, it changes the element
 * to an x so it is not counted more than once and recursively calls getSize in
 * all 4 directions and adds the result to the count. The bounds of the grid do
 * not need to be considered because the grid is bounded by x's and will there-
 * fore prevent the function from attempting to access data outside the array.
 *
 * @param	g grid to load into
 * @param	rows number of rows
 * @param	cols number of columns
 *
 * @return size of the patch
 *
*/
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
