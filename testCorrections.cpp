class heap{
   public:
      heap(int maxSize = 8);
      heap(const heap& other);
      ~heap();
      heap& operator=(const heap& other);
      void insert(int);
      int remove();
      void clear();
      bool isEmpty() const;
      bool isFull() const;

   private:
      void removeHelper(int);
      void insertHelper(int);
      int getParent(int);
      int getLChild(int);
      int getRChild(int);
      void swap(int&, int&);
      int size, maxSize;
      int* data;
};

void heap::insert(int newDataItem)
{
	if(isFull())
	{
		return;
	}
	data[size] = newDataItem;
	int newDataIndex = size;
	size++;
	int parentIndex;
	bool inPlace = false;

	while( newDataIndex > 0 && !inPlace)
	{
		parentIndex = getParent(newDataIndex);
		if(data[newDataIndex] < data[parentIndex])
		{
			inPlace = true;
		}
		else
		{
		   swap(data[newDataIndex], data[parentIndex]);
			newDataIndex = parentIndex;
		}
	}
}

bool heap::isFull() const
{
   if(size-1 == maxSize)
   {
      return true;
   }
   return false;
}

int heap::getParent(int index)
{
   return (index-1)/2;  
}

void heap::swap(int &a, int &b)
{
   int temp = a;
   a = b;
   b = temp;
}

int heap::remove()
{
	if(!isEmpty())
	{
		int toReturn = data[0];
		data[0] = data[size-1];
		size--;
		removeHelper(0);
		return toReturn;
	}
}

bool heap::isEmpty() const
{
   if(size == 0)
   {
      return true;
   }
   return false;
}

void heap::removeHelper(int parent)
{
   if(parent*2 < size)
   {
      int bigger = getLChild(parent);
      int right = getRChild(parent);
      if(data[right] > data[bigger])
      {
         bigger = right;
      }
      int temp;
      if(data[parent] < data[bigger])
      {
         swap(data[parent], data[bigger]);
      }
   }
}

bool BST::remove(int toRemove)
{
   return removeHelper(root, toRemove);
}

bool BST::removeHelper(BSTNode* &parent, int toRemove)
{
   if(parent == NULL)
   {
      return false;
   }
   if(toRemove < parent->data)
   {
      return removeHelper(parent->left, toRemove);
   }
   else if(toRemove > parent->data)
   {
      return removeHelper(parent->right, toRemove);
   }
   else if(toRemove == parent->data)
   {
      if(parent->left == NULL && parent->right == NULL)
      {
         BSTNode* tmp = parent;
         parent = NULL;
         delete tmp;
         return true;
      }
      if(parent->right == NULL)
      {
         BSTNode*tmp = parent->right;
         parent->data = tmp->data;
         parent->left = tmp->left;
         parent->right = tmp->right;
         delete tmp;
         return true;
      }
      else
      {
         BSTNode* tmp = parent->left;
         while(tmp->right != NULL)
         {
            tmp = tmp->right;
         }
         parent->data = tmp->data;
         removeHelper(parent->left, tmp->data);
         return true;
      }
   }
   return false;

}
