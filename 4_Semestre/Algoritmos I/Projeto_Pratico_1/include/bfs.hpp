#ifndef BFSHPP
#define BFSHPP

#include <iostream>
#include <queue>
#include <vector>

using su_int = short unsigned int;

class BFS {
    public:
        BFS(char** map, su_int M, su_int N, std::pair<su_int, su_int> position, su_int bicicle);  // mapa, posicao da pessoa, nome da bicicleta
        su_int bfs_execution();

        void explore(std::vector<su_int> pos);

    private:
        std::queue < std::vector <su_int> > cells;
        char **map;
        bool **explored_map;
        su_int M;
        su_int N;
        std::pair<su_int, su_int> position;
        su_int bike;


};

#endif