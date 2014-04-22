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
      void removeHelper();
      void insertHelper(int);
      int getParent(int);
      int getLChild(int);
      int getRChild(int);
      int size, maxSize;
      int* data;
};
