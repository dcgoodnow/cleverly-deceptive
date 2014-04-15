#include "WeightedGraph.h"

WeightedGraph::WeightedGraph(int maxNumber)
{
	maxSize = maxNumber;
	size = 0;
	adjMatrix = new int[maxSize*maxSize];
	vertexList = new Vertex[maxSize];
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
	while(i < size && v != vertexList[i].getLabel()) //fix these conditionals
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
}

