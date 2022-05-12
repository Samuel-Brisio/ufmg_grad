// include the libraries
#include <iostream>
#include <vector>
#include <algorithm>

#include "gs.hpp"

void makePeoplePreferenceList(std::vector < std::vector <int> > peoplePreference);
void makePeopleList(std::vector <char> List);
void makeBicicleList(std::vector <int> List);

int main() {

    // read the input

    int n; // number of people and bicicles
    int rows, cols; // n = number of rows || m = number of columns
    
    std::cin >> n;
    std::cin >> rows >> cols;

    // create the matrix that will store the map
    std::vector < std::vector < char > > pinpolhosMap (rows, std::vector <char> (cols) );

    std::vector < char > peopleList (n);
    std::vector < int > bicicleList (n);

    std::vector < std::vector <int> > peoplePreference (n, std::vector <int> (n)); 
    std::vector < std::vector <char> > biciclePreference (n, std::vector <char> (n)); 


    for(int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cin >> pinpolhosMap[i][j];
        }
    }


    makePeoplePreferenceList(peoplePreference);
    /*
    makePeopleList(peopleList);
    makeBicicleList(bicicleList);

    // call BFS


    // call Gale_Shapley
    GaleShapley gs(peopleList, bicicleList, peoplePreference, biciclePreference);
    gs.gpExecution();

    // output
    gs.printResult();
    */

    return 0;
}

void makePeopleList(std::vector <char> List) {
    int size = List.size();

    for(int i = 0; i < size; i++) {
        List[i] = 'a' + i;
    }
}
void makeBicicleList(std::vector <int> List) {
    int size = List.size();

    for(int i = 0; i < size; i++) {
        List[i] = i;
    }
}

void makePeoplePreferenceList(std::vector < std::vector <int> > peoplePreference) {
    int size = peoplePreference.size();

    // preferece is a auxiliar vector this will store the unnordered preference list
    std::vector <std::pair <int, int> > preference (size);

    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            std::cin >> preference[j].first;
            preference[j].second = j;
        }

        // sort the vector in the descendent order
        std::sort(preference.begin(), preference.end(), [](const std::pair <int, int> &a, const std::pair <int, int> &b) -> bool {return a.first > b.first;});
        
        for(int j = 0; j < size; j++) {
            peoplePreference[i][j] == preference[j].second;
        }
    }
}