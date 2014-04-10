#include "PriorityQueue.h"
#include "Heap.cpp"


template < typename DataType, typename KeyType, typename Comparator>
PriorityQueue<DataType, KeyType, Comparator>::PriorityQueue(int maxNumber)
{
	Heap<DataType, KeyType, Comparator> pq(maxNumber);
}
template < typename DataType, typename KeyType, typename Comparator>
void PriorityQueue<DataType, KeyType, Comparator>::enqueue(const DataType &newDataItem)
{
	pq.insert(newDataItem);
}

template < typename DataType, typename KeyType, typename Comparator>
DataType PriorityQueue<DataType, KeyType, Comparator>::dequeue()
{
	return pq.remove();
}
