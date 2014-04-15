#include "WeightedGraph.h"

WeightedGraph::WeightedGraph(int maxNumber)
{
	maxSize = maxNumber;
	size = 0;
	adjMatrix = new int[maxSize*maxSize];
	pathMatrix = new int[maxSize*maxSize];
	vertexList = new Vertex[maxSize];
}

WeightedGraph::~WeightedGraph()
{
	size = 0;
	maxSize = 0;
	delete[] vertexList;
	delete[] adjMatrix;
}

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
	adjMatrix[toArr(rNum,cNum)] = wt;
	adjMatrix[toArr(cNum,rNum)] = wt;
}

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
		cout << i << endl;
	}
	
	if(v == vertexList[i].getLabel())
	{
		vData = vertexList[i];
		return true;
	}
	return false;
}

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

void WeightedGraph::removeVertex(const string& v) throw (logic_error)
{
	if(isEmpty())
	{
		return;
	}
	if(isFull())
	{
		size--;
		return;
	}
	Vertex toRemove;
	if(!retrieveVertex(v, toRemove))
	{
		return;
	}
	int t = 0;
	while( v != vertexList[t].getLabel()){t++;}

	for(int i = t+1; i < size; i++)
	{
		vertexList[i-1] = vertexList[i];
		for(int j = 0; j < size; j++)
		{
			adjMatrix[toArr(i-1, j)] = adjMatrix[toArr(i, j)];
		}
	}
	for(int i = 0; i < size; i++)
	{
		adjMatrix[toArr(t, i)] = adjMatrix[toArr(t+1, i)];
	}
	size--;
}

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

bool WeightedGraph::isEmpty() const
{
	if(size == 0)
	{
		return true;
	}
	return false;
}

bool WeightedGraph::isFull() const
{
	if(size-1 == maxSize)
	{
		return true;
	}
	return false;
}

void WeightedGraph::clear()
{
	size = 0;
}

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
				if(adjMatrix[toArr(j,m)] != INFINITE_EDGE_WT &&
					adjMatrix[toArr(m,k)] != INFINITE_EDGE_WT &&
					adjMatrix[toArr(j,m)] + adjMatrix[toArr(m,k)] < pathMatrix[toArr(j,k)])
				{
					pathMatrix[toArr(j,k)] = adjMatrix[toArr(j,m)]+adjMatrix[toArr(m,k)];
				}
			}
		}
	}
}
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
#if LAB12_TEST2
		<< vertexList[row].color
#endif
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

bool WeightedGraph::areAllEven() const
{
	return true;
}
