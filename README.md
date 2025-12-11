# Deli/Restaurant Simulator

This project is a simple C++ console “deli” that lets a user order sandwiches either from a **menu** or by building a **custom** sandwich through a series of questions.

## Features

- Order **from menu** (predefined recipes) or **custom** using an interactive decision tree.
- Inventory of all ingredients with a **boxy, categorized display** (Bread / Protein / Cheese / Veggies / Other).
- Automatically handles **out-of-stock items** by using a substitution graph (e.g., `swiss → provolone → cheddar`).
- Visual **ASCII sandwich stack** printed from bottom to top, with different patterns/colors for bread, protein, cheese, and veggies.
- Runs in a loop so multiple orders can be placed until the user quits.

## Data Structures Used

- **List** (`std::list<Recipe>`)  
  Stores menu recipes and is used to display and select items from the menu.

- **Stack** (`Stack` class)  
  Used to represent the sandwich layers (bottom → top) and to record the user’s choices during custom ordering.

- **Queue** (`std::queue<Ticket>`)  
  Models the order tickets so the kitchen processes them in FIFO order.

- **Hash Table** (`Inventory` with `std::unordered_map<std::string,int>`)  
  Tracks ingredient quantities, supports `has`, `use`, and formatted printing of the inventory.

- **Tree** (`DecisionNode` + `buildOrderingTree` / `runOrdering`)  
  Implements the custom ordering flow as a decision tree of questions (bread → protein → cheese → veggies).

- **Graph** (`SubstitutionGraph`)  
  Represents allowed ingredient substitutions. A BFS is used to find the first available substitute in inventory when something is out of stock.

## Building and Running

From the project root:

```bash
g++ -std=c++17 main.cpp \
    Data_Structures/tree.cpp \
    Data_Structures/hash.cpp \
    Data_Structures/Stack.cpp \
    Data_Structures/Graph.cpp \
    -o deli_sim

./deli_sim