// Data_Structures/Graph.h
#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <unordered_map>
#include <vector>

// Inventory is defined in hash.h
struct Inventory;

// Graph modeling ingredient substitutions
// Example: "swiss" -> "cheddar" means cheddar can replace swiss.
class SubstitutionGraph {
public:
    // Add a directed edge: ingredient can be replaced by substitute
    void addSubstitution(const std::string& ingredient,
                         const std::string& substitute);

    void clear();

    // Find an available ingredient (original or substitute) in inventory.
    // Returns true and writes the chosen ingredient into resultName.
    bool findAvailableAlternative(const std::string& ingredient,
                                  const Inventory& inv,
                                  std::string& resultName) const;

    // Try to use requested ingredient from inventory.
    // If it's out, use a substitute found via the graph.
    // Returns true if something was actually used, and writes the name used.
    bool useOrSubstitute(const std::string& requested,
                         Inventory& inv,
                         std::string& usedIngredient) const;

private:
    // adjacency list: ingredient -> list of possible substitutes
    std::unordered_map<std::string, std::vector<std::string>> adj_;
};

#endif // GRAPH_H