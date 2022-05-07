// include the libraries
#include <iostream>
#include <vector>

#include "gs.hpp"

int main() {
    int n;
    std::cin >> n;

    std::vector < char > peopleList (n);
    std::vector < int > bicicleList (n);

    for( int i = 0; i < n; i++ ) {
        std::cin >> peopleList[i];
    }

    for( int i = 0; i < n; i++) {
        std::cin >> bicicleList[i];
    }

    std::vector < std::vector < int > > peoplePreferece (n, std::vector <int> (n));
    std::vector < std::vector < char > > biciclePreference (n, std::vector < char > (n));
    
    // read the people' preference list
    for ( int i = 0; i < n; i++ ) {
        for ( int j = 0; j < n; j++) {
            std::cin >> peoplePreferece[j][i];
        }
    }

    // read the bicicle' preference list 
    for ( int i = 0; i < n; i++ ) {
        for ( int j = 0; j < n; j++) {
            std::cin >> biciclePreference[j][i];
        }
    }

    // read the input

    // call Gale_Shapley


    GaleShapley gs(peopleList, bicicleList, peoplePreferece, biciclePreference);

    gs.gpExecution();

    gs.printResult();

    // output

    return 0;
}