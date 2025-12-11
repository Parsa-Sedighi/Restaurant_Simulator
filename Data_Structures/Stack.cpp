// Data_Structures/Stack.cpp
#include "Stack.h"
#include <iostream>  // for std::cout

Stack::Stack() = default;

void Stack::push(const std::string& value) {
    data_.push_back(value);
}

void Stack::pop() {
    if (data_.empty()) {
        throw std::runtime_error("Stack::pop() called on empty stack");
    }
    data_.pop_back();
}

std::string& Stack::top() {
    if (data_.empty()) {
        throw std::runtime_error("Stack::top() called on empty stack");
    }
    return data_.back();
}

const std::string& Stack::top() const {
    if (data_.empty()) {
        throw std::runtime_error("Stack::top() called on empty stack");
    }
    return data_.back();
}

bool Stack::empty() const {
    return data_.empty();
}

std::size_t Stack::size() const {
    return data_.size();
}

const std::vector<std::string>& Stack::elements() const {
    return data_;
}

void Stack::print() const {
    std::cout << "--- Sandwich Stack (bottom -> top) ---\n";
    for (std::size_t i = 0; i < data_.size(); ++i) {
        std::cout << data_[i] << "\n";
    }
}

