#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <unordered_map>
#include <vector>

// Forward declaration: Inventory is defined in hash.h
struct Inventory;

// Graph for ingredient substitutions
class SubstitutionGraph {
public:
    // Add a directed substitution:
    // "ingredient" can be replaced by "substitute"
    void addSubstitution(const std::string& ingredient,
                         const std::string& substitute);

    // Remove all nodes/edges
    void clear();

    // Find an ingredient (original or substitute) that is available
    // Returns true and writes result into 'resultName' if found.
    // Uses a BFS/graph search to avoid cycles.
    bool findAvailableAlternative(const std::string& ingredient,
                                  const Inventory& inv,
                                  std::string& resultName) const;

    // Convenience: try to consume 'amount' of ingredient from inventory.
    // If the requested ingredient is out of stock, tries substitutes via the graph.
    // Returns true if something was successfully used, and writes the actual
    // ingredient name used into 'usedIngredient'.
    bool useOrSubstitute(const std::string& requested,
                         Inventory& inv,
                         int amount,
                         std::string& usedIngredient) const;

private:
    // adjacency list: ingredient -> list of possible substitutes (in preference order)
    std::unordered_map<std::string, std::vector<std::string>> adj_;
};

#endif // GRAPH_H