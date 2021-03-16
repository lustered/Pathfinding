#include <queue>
const int MAXPRIORITY = 10;

template <typename T>
class qpqueue
{
  public:
   qpqueue();

   void push (const T & item, int p);
   // insert item with priority p,
   // 0 <= p <= MAXPRIORITY

   void pop();
   // find the non-empty queue with largest index and remove its
   // front element
   // Precondition: the queue is not empty, the function throws
   //      underflowError exception if the queue is empty

   T& top();
   // find the non-empty queue with largest index and return
   // its front element.
   // Precondition: the queue is not empty, the function
   // throws the underflowErr exception if the queue is empty

   const T& top() const;
   // constant version of top();

   bool empty() const;
   // is the queue empty?

   int size() const;
   // return the number of elements in the queue

  private:
   queue<T> priority[MAXPRIORITY +1];
   // priority[i] contains all elements with priority i
   //  in their order of insertion
   int pqsize;
   // number of elements in the priority queue
};
