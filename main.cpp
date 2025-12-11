// main.cpp
#include <iostream>
#include <queue>
#include <list>
#include <string>

#include "Data_Structures/tree.h"
#include "Data_Structures/hash.h"
#include "Data_Structures/Stack.h"
#include "Data_Structures/graph.h"

struct Ticket {
    int id;
    Sandwich order;
};

struct Recipe {
    std::string name;
    Sandwich base;
};

int main() {
    // 1) Inventory (hash table)
    Inventory containers;

    // 2) Substitution graph
    SubstitutionGraph subs;
    // Cheese substitutions
    subs.addSubstitution("provolone", "cheddar");
    subs.addSubstitution("cheddar", "swiss");
    subs.addSubstitution("swiss", "provolone");
    // Bread substitutions
    subs.addSubstitution("italian", "white");
    subs.addSubstitution("white",   "wheat");
    subs.addSubstitution("wheat",   "italian");

    // Protein substitutions
    subs.addSubstitution("turkey","chicken");
    subs.addSubstitution("chicken","ham");
    subs.addSubstitution("ham","turkey");
    //subs.addSubstitution("veggie","ham");
   
    // (You can add more substitutions later if you like)

    // 3) Menu (List of recipes)
    std::list<Recipe> recipes;

    // Recipe 1: Classic Turkey
    {
        Recipe r;
        r.name           = "Classic Turkey";
        r.base.bread     = "italian";
        r.base.protein   = "turkey";
        r.base.cheese    = "cheddar";
        r.base.veggies.push_back("lettuce");
        r.base.veggies.push_back("tomato");
        recipes.push_back(r);
    }

    // Recipe 2: Veggie Delight
    {
        Recipe r;
        r.name           = "Veggie Delight";
        r.base.bread     = "wheat";
        r.base.protein   = "veggie";
        r.base.cheese    = "provolone";
        r.base.veggies.push_back("lettuce");
        r.base.veggies.push_back("tomato");
        r.base.veggies.push_back("onion");
        recipes.push_back(r);
    }

    // Build the decision tree once
    DecisionNode* root = buildOrderingTree();

    int nextTicketId = 1;
    bool running = true;

    while (running) {
        // Show inventory at the start of each loop
        std::cout << "\n========================================\n";
        std::cout << "Current Inventory:\n";
        containers.print();
        std::cout << "========================================\n\n";

        // Show menu
        std::cout << "=== Menu (predefined recipes) ===\n";
        int menuIndex = 1;
        for (std::list<Recipe>::const_iterator it = recipes.begin();
             it != recipes.end(); ++it, ++menuIndex)
        {
            std::cout << menuIndex << ") " << it->name
                      << " - " << it->base.bread
                      << " / " << it->base.protein
                      << " / " << it->base.cheese
                      << "\n";
        }
        std::cout << "\n";

        // Ask user what they want to do
        std::cout << "Order from menu, custom, or quit?\n";
        std::cout << "Type 'menu', 'custom', or 'quit' (or m / c / q): ";
        std::string mode;
        std::getline(std::cin, mode);

        // Normalize basic options
        if (mode == "q" || mode == "Q" || mode == "quit" || mode == "Quit") {
            std::cout << "Goodbye!\n";
            break;
        }

        bool useMenu = false;
        if (mode == "menu" || mode == "Menu" || mode == "m" || mode == "M" || mode == "1") {
            useMenu = true;
        }

        // This will hold the sandwich to be built
        Sandwich s;
        Stack orderChoices;

        if (useMenu) {
            // ----- MENU ORDER -----
            if (recipes.empty()) {
                std::cout << "No recipes on the menu. Switching to custom.\n";
            } else {
                std::cout << "\nYou chose: MENU order.\n";
                std::cout << "Please choose a recipe by number:\n";
                menuIndex = 1;
                for (std::list<Recipe>::const_iterator it = recipes.begin();
                     it != recipes.end(); ++it, ++menuIndex)
                {
                    std::cout << menuIndex << ") " << it->name << "\n";
                }
                std::cout << "Enter number: ";

                std::string numStr;
                std::getline(std::cin, numStr);
                int selected = 1;
                try {
                    selected = std::stoi(numStr);
                } catch (...) {
                    selected = 1;
                }

                if (selected < 1) selected = 1;
                if (selected > (int)recipes.size()) selected = (int)recipes.size();

                int currentIndex = 1;
                for (std::list<Recipe>::const_iterator it = recipes.begin();
                     it != recipes.end(); ++it, ++currentIndex)
                {
                    if (currentIndex == selected) {
                        s = it->base;
                        std::cout << "You selected: " << it->name << "\n";
                        break;
                    }
                }
            }
        }

        // If user did not choose menu, or menu fallback
        if (!useMenu || s.bread.empty()) {
            std::cout << "\nYou chose: CUSTOM order.\n";
            std::cout << "=== Taking a custom order ===\n";
            runOrdering(root, s, containers, orderChoices);

            std::cout << "\nYour custom choices (in order):\n";
            orderChoices.print();
        }

        // Put final sandwich into a ticket queue (we process immediately, but this shows Queue usage)
        std::queue<Ticket> orderQueue;
        Ticket ticket;
        ticket.id    = nextTicketId++;
        ticket.order = s;
        orderQueue.push(ticket);

        // Kitchen: process queue and build sandwich stack
        while (!orderQueue.empty()) {
            Ticket current = orderQueue.front();
            orderQueue.pop();
        
            std::cout << "\n=== Building Sandwich for Ticket #" << current.id << " ===\n";
        
            Stack sandwichStack;
            std::string used;
            const Sandwich& ord = current.order;
        
            // Helper lambda: adds a layer, prints substitution info
            auto addLayer = [&](const std::string& requested,
                                const std::string& roleLabel) {
                if (requested.empty()) return;
                                
                if (subs.useOrSubstitute(requested, containers, used)) {
                    sandwichStack.push(used);
                
                    if (used == requested) {
                        std::cout << "Using " << used << " (" << roleLabel << ")\n";
                    } else {
                        std::cout << "Substituted " << requested
                                  << " -> " << used
                                  << " (" << roleLabel << ")\n";
                    }
                } else {
                    std::cout << "Out of " << requested
                              << " (" << roleLabel << ") and all substitutes.\n";
                }
            };
        
            // Bottom bread
            addLayer(ord.bread, "bread (bottom)");
        
            // Protein
            addLayer(ord.protein, "protein");
        
            // Cheese
            addLayer(ord.cheese, "cheese");
        
            // Veggies (each one individually)
            for (std::size_t i = 0; i < ord.veggies.size(); ++i) {
                addLayer(ord.veggies[i], "veggie");
            }
        
            // Top bread
            addLayer(ord.bread, "bread (top)");
        
            // Pretty-print sandwich
            sandwichStack.print();
        }
        
        std::cout << "\n=== Current inventory ===\n";
        // Ask user if they want another order
        containers.print();
        std::cout << "\nTake another order? (y/n): ";
        std::string again;
        std::getline(std::cin, again);
        if (again != "y" && again != "Y" && again != "yes" && again != "Yes") {
            running = false;
            std::cout << "Exiting order loop.\n";
        }
    }

    //std::cout << "\n=== Final inventory ===\n";
    //containers.print();

    return 0;
}