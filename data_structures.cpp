#include <string>
#include <iostream>
#include <fstream>
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

// List


// Queues
template <typename T>
class QueueNode {
public:
   T data;
   QueueNode* next;
   
   QueueNode(int dataValue, QueueNode* nextNode = nullptr) {
      data = dataValue;
      next = nextNode;
   }
};

template <typename T>
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
struct tree {
   std::string data;
   tree* right = nullptr;
   tree* left  = nullptr;

   ~ tree(){
      delete right;
      delete left;
   }

};

tree* make_tree(std::string data, tree* leftNode, tree* rightNode) {
   tree* node = new tree;
   node->data = data;
   node->left = leftNode;
   node->right = rightNode;
   return node;
}

tree* make_tree(std::string data) {
   tree* node = new tree;
   node->data = data;
   return node;
}

std::ostream& operator<< (std::ostream&os, tree* node){
   if(node == nullptr)
   {
      return os;
   }
   os << node->data << "\n" << node->left << node->right;
   return os;
}


// Hash Table

// Stacks

// Graph