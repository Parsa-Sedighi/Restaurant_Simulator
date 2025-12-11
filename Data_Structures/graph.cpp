#include "graph.h"
#include "hash.h"   // for Inventory
#include <queue>
#include <unordered_set>

void SubstitutionGraph::addSubstitution(const std::string& ingredient,
                                        const std::string& substitute)
{
    adj_[ingredient].push_back(substitute);
}

void SubstitutionGraph::clear() {
    adj_.clear();
}

bool SubstitutionGraph::findAvailableAlternative(const std::string& ingredient,
                                                 const Inventory& inv,
                                                 std::string& resultName) const
{
    // BFS to find first available ingredient
    std::queue<std::string> q;
    std::unordered_set<std::string> visited;

    q.push(ingredient);
    visited.insert(ingredient);

    while (!q.empty()) {
        std::string current = q.front();
        q.pop();

        // Check if this ingredient is available in inventory
        if (inv.has(current, 1)) {        // assumes Inventory::has(name, amount)
            resultName = current;
            return true;
        }

        // Otherwise, enqueue neighbors (substitutes)
        auto it = adj_.find(current);
        if (it != adj_.end()) {
            for (const std::string& neighbor : it->second) {
                if (visited.insert(neighbor).second) { // newly inserted
                    q.push(neighbor);
                }
            }
        }
    }

    // No available substitute found
    return false;
}

bool SubstitutionGraph::useOrSubstitute(const std::string& requested,
                                        Inventory& inv,
                                        int amount,
                                        std::string& usedIngredient) const
{
    std::string candidate;

    // Step 1: find an ingredient (original or substitute) that is available
    if (!findAvailableAlternative(requested, inv, candidate)) {
        // Nothing available
        return false;
    }

    // Step 2: actually consume it from inventory
    if (!inv.use(candidate, amount)) {
        // Inventory changed after check or not enough for 'amount'
        return false;
    }

    usedIngredient = candidate;
    return true;
}