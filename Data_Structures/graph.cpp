#include "graph.h"
#include "hash.h"   
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
    std::queue<std::string> q;
    std::unordered_set<std::string> visited;

    q.push(ingredient);
    visited.insert(ingredient);

    while (!q.empty()) {
        std::string current = q.front();
        q.pop();

        // Your Inventory has: bool has(const std::string&, int amount = 1) const;
        if (inv.has(current, 1)) {
            resultName = current;
            return true;
        }

        auto it = adj_.find(current);
        if (it != adj_.end()) {
            for (const std::string& neighbor : it->second) {
                if (visited.insert(neighbor).second) {
                    q.push(neighbor);
                }
            }
        }
    }

    // No available alternative found
    return false;
}

bool SubstitutionGraph::useOrSubstitute(const std::string& requested,
                                        Inventory& inv,
                                        std::string& usedIngredient) const
{
    std::string candidate;
    if (!findAvailableAlternative(requested, inv, candidate)) {
        return false; // nothing available
    }

    // Your Inventory::use(const std::string& name) consumes 1 unit
    if (!inv.use(candidate)) {
        return false;
    }

    usedIngredient = candidate;
    return true;
}