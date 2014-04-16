/**
 * @file WeightedGraph.cpp
 * @author Daniel Goodnow
 * @mainpage Graph
 * @detail A basic ADT to store a graph data structure. It utilizes an adjacency
 * matrix to store edge data as well as a list of all vertexes. For some reason
 * a one dimension array is used to store the matrix which increases 
 * computation time when accessing the matrix. Also, it includes functions to 
 * generate a path matrix as well as perform color adjacency and even degree
 * tests. 
*/
#include "WeightedGraph.h"

/**
 * @name Constructor
 * @brief Allocates and initializes data members.
 *
 * @param maxNumber Maximum size of the array.
 *
 * @pre none
 * @post Graph exists
*/
WeightedGraph::WeightedGraph(int maxNumber)
{
	maxSize = maxNumber;
	size = 0;
	adjMatrix = new int[maxSize*maxSize];
	pathMatrix = new int[maxSize*maxSize];
	vertexList = new Vertex[maxSize];
}

/**
 *	@name Destructor
 *	@brief Deallocates all memory for the graph.
 *
 *	@pre Graph exists.
 *	@post Graph no longer exists.
 *
*/
WeightedGraph::~WeightedGraph()
{
	size = 0;
	maxSize = 0;
	delete[] vertexList;
	delete[] adjMatrix;
}

/**
 * @name Copy Constructor
 * @brief Creates a new graph that is a copy of other.
 *
 * @param other The graph to be copied from.
 *
 * @pre other exists.
 * @post New graph is created.
*/
WeightedGraph::WeightedGraph(const WeightedGraph& other)
{
	maxSize = other.maxSize;
	size = other.size;
	adjMatrix = new int[maxSize*maxSize];
	vertexList = new Vertex[maxSize];
	for(int i = 0; i < size; i++)
	{
		vertexList[i] = other.vertexList[i];
		for(int j = 0; j < size; j++)
		{
			adjMatrix[toArr(i,j)] = other.adjMatrix[toArr(i,j)];
		}
	}
}

/**
 * @name Overloaded Assignment Operator
 * @brief Copies other into this graph.
 *
 * @param other The graph to be copied from.
 *
 * @pre Graph exists and other exists.
 * @post Graph is a copy of other.
*/
WeightedGraph& WeightedGraph::operator=(const WeightedGraph& other)
{
	if(this == &other)
	{
		return *this;
	}
	clear();

	maxSize = other.maxSize;
	size = other.size;
	delete[] adjMatrix;
	delete[] vertexList;
	adjMatrix = new int[maxSize*maxSize];
	vertexList = new Vertex[maxSize];
	for(int i = 0; i < size; i++)
	{
		vertexList[i] = other.vertexList[i];
		for(int j = 0; j < size; j++)
		{
			adjMatrix[toArr(i,j)] = other.adjMatrix[toArr(i,j)];
		}
	}
	return *this;
}

/**
 * @name Insert Vertex
 * @brief inserts a new vertex into the graph.
 *
 * @param newVertex The vertex to be inserted into the graph.
 *
 * @pre Graph exists and is not full.
 * @post Graph contains the new Vertex and size is increased by 1.
*/
void WeightedGraph::insertVertex(const Vertex& newVertex) throw (logic_error)
{
	if(isFull())
	{
		return;
	}
	vertexList[size] = newVertex;
	size++;
	for(int i = 0; i < size; i++)
	{
		adjMatrix[(size-1)*maxSize + i] = INFINITE_EDGE_WT;
		adjMatrix[i*maxSize + size-1] = INFINITE_EDGE_WT;
	}
}

/**
 * @name Insert Edge
 * @brief Inserts a new edge into the adjacency matrix.
 * @detail Finds the indices of the two vertices and inserts the value wt at the
 * intersection of the indices on the adjacency matrix.
 *
 * @param v1 The first vertex.
 * @param v2 The second vertex.
 * @param wt The weight of the edge.
 *
 * @pre The graph and both vertices exist.
 * @post The graph contains a new edge.
*/
void WeightedGraph::insertEdge( const string& v1, const string& v2, int wt) throw (logic_error)
{
	Vertex temp, temp2;
	if(!retrieveVertex(v1, temp) || !retrieveVertex(v2, temp2))
	{
		return;
	}
	int rNum=0, cNum = 0;
	while(temp.getLabel() != vertexList[rNum].getLabel())
	{
		rNum++;
	}
	while(temp2.getLabel() != vertexList[cNum].getLabel())
	{
		cNum++;
	}
	cout << "Size = " << size << ", idx_v1 = " << rNum << ", idx_v2 = " << cNum << endl;
	adjMatrix[toArr(rNum,cNum)] = wt;
	adjMatrix[toArr(cNum,rNum)] = wt;
}

/**
 * @name Retrieve Vertex
 * @brief Searches the vertex list for the vertex with label v and returns it
 * with the parameter vData.
 *
 * @param v The label of the vertex being searched for.
 * @param vData The found vertex.
 *
 * @retval True if found, false if not.
 * 
 * @pre Graph exists.
 * @post none
*/
bool WeightedGraph::retrieveVertex(const string& v, Vertex& vData) const
{
	if(isEmpty())
	{
		return false;
	}
	int i = 0;
	while(i < size-1 && v != vertexList[i].getLabel()) //fix these conditionals
	{
		i++;
	}
	
	if(v == vertexList[i].getLabel())
	{
		vData = vertexList[i];
		return true;
	}
	return false;
}

/**
 * @name Get Edge Weight
 * @brief Gets the weight of the edge between two vertices if those vertices exist.
 *
 * @param v1 First vertex.
 * @param v2 Second vertex.
 * @param wt The weight of the edge between the two vertices.
 *
 * @retval True if vertices exist, false if not.
*/
bool WeightedGraph::getEdgeWeight(const string& v1, const string& v2, int& wt) const 
		throw (logic_error)
{
	Vertex temp, temp2;
	if(!retrieveVertex(v1, temp) || !retrieveVertex(v2, temp2))
	{
		return false;
	}
	int rNum=0, cNum = 0;
	while(temp.getLabel() != vertexList[rNum].getLabel())
	{
		rNum++;
	}
	while(temp2.getLabel() != vertexList[cNum].getLabel())
	{
		cNum++;
	}
	if(adjMatrix[toArr(rNum, cNum)] != INFINITE_EDGE_WT)
	{
		wt = adjMatrix[toArr(rNum, cNum)];
		return true;
	}
	return false;
}

/**
 * @name Remove Vertex
 * @brief Removes a vertex by shifting all data past the index of the vertex 
 * down by one in both the vertex list and adjacency matrix.
 *
 * @param v Label of the vertex to remove.
 * 
 * @pre Graph is not empty and vertex with label v exists.
 * @post Vertex is remove and size is decreased by one.
*/
void WeightedGraph::removeVertex(const string& v) throw (logic_error)
{
	if(isEmpty())
	{
		return;
	}
	Vertex toRemove;
	if(!retrieveVertex(v, toRemove))
	{
		return;
	}
	int i = 0;
	while(v != vertexList[i].getLabel())
	{
		i++;
	}
	for(int j = i+1; j < size; j++)
	{
		vertexList[j-1] = vertexList[j];
		for(int k = 0; k < size; k++)
		{
			adjMatrix[toArr(j-1, k)] = adjMatrix[toArr(j,k)];
		}
	}
	for(int j = 0; j < size; j++)
	{
		for(int k = i+1; k < size; k++)
		{
			adjMatrix[toArr(j, k-1)] = adjMatrix[toArr(j,k)];
		}
	}
	size--;
}

/**
 * @name Remove Edge
 * @brief Removes an edge from the adjacency matrix.
 * @detail Finds the edge and sets it to INFINITE_EDGE_WIDTH
 *
 * @param v1 First vertex.
 * @param v2 Second vertex.
 * 
 * @pre Edge exists.
 * @post Edge is removed.
*/
void WeightedGraph::removeEdge(const string& v1, const string& v2) throw (logic_error)
{
	if(isEmpty() || size == 1)
	{
		return;
	}
	Vertex temp, temp2;
	if(!retrieveVertex(v1, temp) || !retrieveVertex(v2, temp2))
	{
		return;
	}
	int rNum=0, cNum = 0;
	while(temp.getLabel() != vertexList[rNum].getLabel())
	{
		rNum++;
	}
	while(temp2.getLabel() != vertexList[cNum].getLabel())
	{
		cNum++;
	}
	adjMatrix[toArr(rNum,cNum)] = INFINITE_EDGE_WT;
	adjMatrix[toArr(cNum,rNum)] = INFINITE_EDGE_WT;
}

/**
 * @name Is Empty
 * @brief Determines whether a graph is empty or not.
 *
 * @retval True if empty, false if otherwise.
 * 
 * @pre Graph exists.
 * @post none
*/
bool WeightedGraph::isEmpty() const
{
	if(size == 0)
	{
		return true;
	}
	return false;
}

/**
 * @name Is Full
 * @brief Determines whether a graph is full or not.
 *
 * @retval True if full, false if otherwise.
 *
 * @pre Graph exists.
 * @post none
 *
*/
bool WeightedGraph::isFull() const
{
	if(size-1 == maxSize)
	{
		return true;
	}
	return false;
}

/**
 * @name clear
 * @brief Makes the graph 'empty'.
 *
 * @pre Graph exists.
 * @post Graph is empty.
*/
void WeightedGraph::clear()
{
	size = 0;
}

/**
 * @name Show Shortest Paths
 * @brief Gets the shortest path matrix and outputs it.
 *
 * @pre Graph exists.
 * @post Path graph is output to std out.
*/
void WeightedGraph::showShortestPaths() const
{
	getPaths();
#if LAB12_TEST2
	cout << vertexList[row].color << endl;
#endif

	cout << endl << "Path matrix : " << endl << '\t';
	for ( int col = 0 ; col < size ; col++ )
		cout << col << '\t';
	cout << endl;
	for ( int row = 0 ; row < size ; row++ )
	{
		cout << row << '\t';
		for ( int col = 0 ; col < size ; col++ )
		{
			int wt = pathMatrix[toArr(row,col)];
			if ( wt == INFINITE_EDGE_WT)
				cout << "- \t";
			else
				cout << wt << '\t';
		}
		cout << endl;
	}
}

/**
 * @name Get Paths
 * @brief Helper function for showShortestPaths.
 * @detail Uses Floyd's algorithm to generate a path matrix.
 *
 * @pre Graph exists
 * @post Path matrix is updated.
*/
void WeightedGraph::getPaths() const
{
	if(isEmpty()){return;}
	for(int i = 0; i<size; i++)
	{
		for(int j = 0; j<size; j++)
		{
			pathMatrix[toArr(i,j)] = adjMatrix[toArr(i,j)];
		}
	}

	for(int i = 0; i < size; i++)
	{
		pathMatrix[toArr(i,i)] = 0;
	}

	for(int j = 0; j<size; ++j)
	{
		for(int k = 0; k<size; ++k)
		{
			for(int m = 0; m<size; ++m)
			{
				if(pathMatrix[toArr(j,m)] != INFINITE_EDGE_WT &&
					pathMatrix[toArr(m,k)] != INFINITE_EDGE_WT &&
					(pathMatrix[toArr(j,m)] + pathMatrix[toArr(m,k)]) < pathMatrix[toArr(j,k)])
				{
					pathMatrix[toArr(j,k)] = pathMatrix[toArr(j,m)]+pathMatrix[toArr(m,k)];
				}
			}
		}
	}
}

/**
 * @name Get Edge
 * @brief Returns the edge at the given row and column.
 *
 * @param r Row
 * @param c Column
 *
 * @retval Edge weight at r,c.
 *
 * @pre Graph exists.
 * @post none
**/
int WeightedGraph::getEdge(int r, int c) const
{
	return adjMatrix[toArr(r,c)];
}

void WeightedGraph::showStructure () const

// Outputs a graph's vertex list and adjacency matrix. This operation
// is intended for testing/debugging purposes only.

{
    if ( size == 0 ) {
       cout << "Empty graph" << endl;
    } else {
       cout << endl << "Vertex list : " << endl;
       for ( int row = 0 ; row < size ; row++ )
           cout << row << '\t' << vertexList[row].getLabel()
		<< '\t' << vertexList[row].getColor()
		<< endl;

       cout << endl << "Edge matrix : " << endl << '\t';
       for ( int col = 0 ; col < size ; col++ )
           cout << col << '\t';
       cout << endl;
       for ( int row = 0 ; row < size ; row++ )
       {
           cout << row << '\t';
           for ( int col = 0 ; col < size ; col++ )
           {
               int wt = getEdge(row,col);
               if ( wt == INFINITE_EDGE_WT)
                  cout << "- \t";
               else
                  cout << wt << '\t';
           }
           cout << endl;
       }
    }
}

/**
 * @name Has Proper Coloring
 * @brief Checks vertices at each edge for same color.
 *
 * @retval True if no adjacent vertices have the same color, false otherwise.
 *
 * @pre Graph is not empty.
 * @post none
 */
bool WeightedGraph::hasProperColoring() const
{
	if(isEmpty()){return true;}
	
	for(int i = 0; i < size; i++)
	{
		for(int j=0; j < size; j++)
		{
			if(adjMatrix[toArr(i,j)] != INFINITE_EDGE_WT &&
				vertexList[i].getColor() == vertexList[j].getColor())
			{
				return false;
			}
		}
	}
	return true;
}

/**
 * @name Are All Even
 * @brief Checks the degree of all vertices.
 *
 * @retval True if all vertices have even degrees.
 *
 * @pre Graph is not empty.
 * @post none
 */
bool WeightedGraph::areAllEven() const
{
	if(isEmpty()){return true;}
	
	int degree;
	for(int i = 0; i < size; i++)
	{
		degree=0;
		for(int j = 0; j < size; j++)
		{
			if(adjMatrix[toArr(i,j)] != INFINITE_EDGE_WT)
			{
				degree++;
				if(i == j)
				{
					degree++;
				}
			}
		}
		if(degree%2 == 1)
		{
			return false;
		}
	}
	return true;
}
