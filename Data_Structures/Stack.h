// Data_Structures/Stack.h
#ifndef STACK_H
#define STACK_H

#include <vector>
#include <string>
#include <stdexcept>
#include <cstddef>
#include <iostream>

class QGraphicsScene;

class Stack {
public:
    Stack();

    void push(const std::string& value);
    void pop();

    std::string& top();
    const std::string& top() const;

    bool empty() const;
    std::size_t size() const;

    // For GUI or debugging: view all layers bottom -> top
    const std::vector<std::string>& elements() const;

    // Print bottom -> top
    void print() const;

    void drawToScene(QGraphicsScene* scene, int startX, int startY, int width, int heightPerItem) const;

private:
    std::vector<std::string> data_;
};

#endif // STACK_H