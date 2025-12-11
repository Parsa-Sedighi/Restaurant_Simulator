// Data_Structures/Stack.cpp
#include "Stack.h"
#include <iostream>

// ANSI escape colors
static const std::string RESET  = "\033[0m";
static const std::string BROWN  = "\033[38;5;94m";
static const std::string BEIGE  = "\033[38;5;180m";
static const std::string YELLOW = "\033[38;5;226m";
static const std::string GREEN  = "\033[38;5;46m";
static const std::string RED    = "\033[38;5;196m";
static const std::string WHITE  = "\033[38;5;255m";

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
    std::cout << "\n--- Sandwich Stack (bottom -> top) ---\n";

    for (std::size_t i = 0; i < data_.size(); ++i) {
        const std::string& layer = data_[i];
        std::string color;
        std::string pattern;

        // 1) BREAD (brown, =) 
        if (layer.find("italian") != std::string::npos ||
            layer.find("white")   != std::string::npos ||
            layer.find("wheat")   != std::string::npos)
        {
            color   = BROWN;
            pattern = "=================";
        }
        // 2) PROTEINS (meats & veggie patty) - +++
        else if (layer.find("turkey")  != std::string::npos) {
            color   = BEIGE;
            pattern = "+++++++++++++++";
        }
        else if (layer.find("ham")     != std::string::npos) {
            color   = RED;
            pattern = "+++++++++++++++";
        }
        else if (layer.find("chicken") != std::string::npos) {
            color   = WHITE;
            pattern = "+++++++++++++++";
        }
        else if (layer.find("veggie")  != std::string::npos) {
            // veggie "patty" protein
            color   = GREEN;
            pattern = "+++++++++++++++";
        }
        // 3) CHEESE - ::::
        else if (layer.find("cheddar")   != std::string::npos) {
            color   = YELLOW;
            pattern = ":::::::::::::::";
        }
        else if (layer.find("swiss")     != std::string::npos ||
                 layer.find("provolone") != std::string::npos)
        {
            color   = WHITE;
            pattern = ":::::::::::::::";
        }
        else if (layer.find("tomato")     != std::string::npos)
        {
            color   = RED;
            pattern = "@@@@@@@@@@@@@@@";
        }
        // 4) VEGGIES - ^^^^ (lettuce, tomato, onion, etc.)
        else if (layer.find("lettuce") != std::string::npos ||
                 layer.find("onion")   != std::string::npos ||
                 layer.find("pickle")  != std::string::npos)
        {
            color   = GREEN;
            pattern = "^^^^^^^^^^^^^^^";
        }
        // 5) FALLBACK
        else {
            color   = RESET;
            pattern = "???????????????";
        }

        std::cout << color << pattern << RESET << "  (" << layer << ")\n";
    }
}