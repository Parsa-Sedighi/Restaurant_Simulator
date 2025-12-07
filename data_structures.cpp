/*
Class for data structures to be implemented:

Array
Queues
Lists
Trees
Hash Table
Stacks
Graph

*/

// Array

// Queues
class QueueNode {
public:
   int data;
   QueueNode* next;
   
   QueueNode(int dataValue, QueueNode* nextNode = nullptr) {
      data = dataValue;
      next = nextNode;
   }
};

class LinkedL_Queue{
private:
   QueueNode* front;
   QueueNode* end;

public:
   LinkedL_Queue() {
      front = nullptr;
      end = nullptr;
   }
   
   virtual ~LinkedL_Queue() {
      while (front) {
         QueueNode* nodeToDelete = front;
         front = front->next;
         delete nodeToDelete;
      }
   }

 
   
   // Remove from internal front
    int dequeue_front()  {
      // Copy front node's data
      QueueNode* dequeuedNode = front;
      int dequeuedItem = front->data;
      
      // Remove front node
      front = front->next;
      delete dequeuedNode;
      if(nullptr == front){
        end = nullptr;
      }
      return dequeuedItem;
    }

    // Queue (LinkedList, Enqueue to Internal Front, Dequeue from Back)

    // Add to internal front
    bool enqueue_front(int newData)  {
        QueueNode* newNode = new QueueNode(newData);
        if(nullptr == front){
            front = end = newNode;
        }
        else{
            newNode->next = front;
            front = newNode;
        }
        
        return true;
    }
    

};

// Trees

// Hash Table

// Stacks

// Graph