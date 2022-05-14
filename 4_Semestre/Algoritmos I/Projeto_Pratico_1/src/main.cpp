// include the libraries
#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

#include "bfs.hpp"
#include "gs.hpp"

using us_int = unsigned short int;

void makePeoplePreferenceList(std::vector < std::vector <int> > &peoplePreference);
void makePeopleList(std::vector <char> &List, std::set <char>  set);
void makeBicicleList(std::vector <int> &List, std::set <int>  set);

int main() {

    // read the input

    int n; // number of people and bicicles
    int rows, cols; // n = number of rows || m = number of columns
    
    std::cin >> n;
    std::cin >> rows >> cols;

    // create the matrix that will store the map
    std::vector < std::vector < char > > pinpolhosMap (rows, std::vector <char> (cols) );

    std::set < char > peopleList;
    std::set < int > bicicleList;

    std::vector < char > peopleListV;
    std::vector < int > bicicleListV;

    std::vector < std::vector <int> > peoplePreference (n, std::vector <int> (n)); 
    std::vector < std::vector <char> > biciclePreference (n, std::vector <char> (n)); 

    std::vector < std::pair <us_int, us_int> > bicicleCoordinates;

    // read the map
    for(int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cin >> pinpolhosMap[i][j];
            char c = pinpolhosMap[i][j];
            if (isdigit(c)) {
                bicicleList.insert(c - '0');
                bicicleCoordinates.push_back(std::pair <us_int, us_int> (i, j));    
            }
            else if (c >= 'a' && c <= 'z') peopleList.insert(c);
        }
    }

    // read and make the turist preference list
    makePeoplePreferenceList(peoplePreference);
    
    makePeopleList(peopleListV, peopleList);
    makeBicicleList(bicicleListV, bicicleList);

    for(int i = 0; i < n; i++) {
        std::cout << (char)('a' + i) << " -> ";
        for(auto e: peoplePreference[i]) std::cout << e << " ";
        std::cout << std::endl;
    }

    // call BFS

    for(int i = 0; i < n; i++) {
        BFS bfs(pinpolhosMap, bicicleCoordinates[i], peopleListV);
        bfs.BFSExecution();
        int bicicle = pinpolhosMap[bicicleCoordinates[i].first][bicicleCoordinates[i].second] - '0';
        biciclePreference[bicicle] = bfs.sortedSolution();
    }

    for(auto bike: biciclePreference) {
        for (auto e: bike) std::cout << e << " ";
        std::cout << std::endl;
    }





    // call Gale_Shapley
    GaleShapley gs(peopleListV, bicicleListV, peoplePreference, biciclePreference);
    gs.gpExecution();

    // output
    gs.printResult();

    return 0;
}

void makePeopleList(std::vector <char> &List, std::set <char>  set){
    int size = set.size();

    for(auto e: set) List.push_back(e);

}
void makeBicicleList(std::vector <int> &List, std::set <int>  set) {
    int size = set.size();

    for(auto e: set) List.push_back(e);
}

void makePeoplePreferenceList(std::vector < std::vector <int> > &peoplePreference) {
    int size = peoplePreference.size();

    // preferece is a auxiliar vector this will store the unnordered preference list
    std::vector <std::pair <int, int> > preference (size);

    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            std::cin >> preference[j].first;
            preference[j].second = j;
        }

        // sort the vector in the descendent order
        std::sort(preference.begin(), preference.end(), [](const std::pair <int, int> &a, const std::pair <int, int> &b) -> bool {
            if (a.first < b.first) return false;
            if (a.first > b.first) return true;
            return a.second < b.second;
            });
        
        for(int j = 0; j < size; j++) {
            peoplePreference[i][j] = preference[j].second;
        }
    }
}