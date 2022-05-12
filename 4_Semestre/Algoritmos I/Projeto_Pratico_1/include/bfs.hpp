#ifndef BFSHPP
#define BFSHPP

#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <vector>

#include "map_insert_or_assign.hpp"

using us_int = unsigned short int;

class BFS {
    public:
        BFS(
            std::vector < std::vector <char> > map,
            std::pair <us_int, us_int> coordinate,
            std::vector <char> preferenceEntityList
            );

        void BFSExecution(); // execute the BFS' algorithm
        std::vector <char> sortedSolution();

    private:
        void createExploredMap(); // auxiliar method that create a mask with the avaliable paths
        std::queue < std::pair <us_int, us_int> > BFSIteration(std::queue < std::pair <us_int, us_int> > actual);
        bool isValidCoord(us_int x, us_int y);
        bool isEntity(us_int x, us_int y);

        std::vector < std::vector <char> > _map;
        std::pair < us_int, us_int > _coordinate;
        std::vector <char> _preferenceEntityList; // List of Entity
        std::vector < std::vector <bool> > _exploredMap;
        std::map <char, us_int> _preferenceList; // preference solution
        us_int _dist;
        us_int _N; // N -> rowns // verificar se as variaveis foram inicializadas corretamente
        us_int _M; // M -> cols



};

#endif