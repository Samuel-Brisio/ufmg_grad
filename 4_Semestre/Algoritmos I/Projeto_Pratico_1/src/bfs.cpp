#include <iostream>

#include "bfs.hpp"

// BFS class contructor
BFS::BFS(char** map, su_int N, su_int M, std::pair<su_int, su_int> position, su_int bicicle) {
    this->map = map; // a pointer to the map
    this->N = N; // number of lines
    this->M = M; // number of columns
    this-> position = position; // person' position
    this->bike = bicicle; // bicicle tag

    explored_map = new bool*[N];
    for(int i = 0; i < N; i++) {
        explored_map[i] = new bool [M];
    }
}

// Execute the BFS algorithm
su_int BFS::bfs_execution() {
    std::vector <su_int> pos {position.first, position.second, su_int(0)};
    cells.push(pos);
    
    while(map[pos[0]][pos[1]] != bike || cells.size() != 0) {
        pos = cells.front();
        cells.pop();

        su_int x = pos[0];
        su_int y = pos[1];

        if(map[x][y] == bike) {
            return pos[2];
        }

        explore(pos);
    }

    return 0;
    
}

// explore the neighbors cells
void BFS::explore(std::vector <su_int> pos) {
    std::pair<short int , short int > neighbors[4];
    neighbors[0] = {1, 0};
    neighbors[1] = {-1, 0};
    neighbors[2] = {0, 1};
    neighbors[3] = {0, -1};

    for(auto n: neighbors) {
        std::vector <su_int> aux (3);
        aux[0] = n.first + pos[0];
        aux[1] = n.second + pos[1];
        aux[2] = pos[2] + 1;

        short int x = aux[0]; 
        short int y = aux[1];

        // if the neighbor is a available path and is not already explored
        if (map[x][y] != '-' && explored_map[x][y] == false) {
            cells.push(pos);
        }
    }
}