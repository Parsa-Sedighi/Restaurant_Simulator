#include <iostream>
#include <vector>
#include <queue>
#include "Data_Structures/tree.cpp"

using namespace std;
int main (){
    cout << "Welcome to Restuarant Simulator!" << endl;


    cout << " Would you like menu or custom order?" << endl;



    // Takes orders, passes them to simulation
    

    
    Sandwich s;

    DecisionNode* root = buildOrderingTree();
    runOrdering(root, s);

    std::cout << "\n--- Your Sandwich ---\n";
    std::cout << s.size << " " << s.bread << " sandwich\n";
    std::cout << "Protein: " << s.protein << "\n";
    std::cout << "Toasted: " << (s.toasted ? "Yes" : "No") << "\n";
    std::cout << "Cheese: " << (s.cheese.empty() ? "None" : s.cheese) << "\n";
    std::cout << "Sauce: "  << (s.sauce.empty()  ? "None" : s.sauce)  << "\n";
    
    return 0;
};