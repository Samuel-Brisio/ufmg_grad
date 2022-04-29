#ifndef BFSHPP
#define BFSHPP

#include <iostream>
#include <queue>

using s_int = short unsigned int;

class BFS {
    public:
        BFS(size_t position, s_int bicicle);  // mapa, posicao da pessoa, nome da bicicleta
        size_t bfs_execution();

    private:
        std::queue < std::pair <size_t, size_t> > cells;
        char **map;
        bool **explored_map;
        size_t M;
        size_t N;
        size_t position;
        s_int bike;


};

#endif