#ifndef BFSHPP
#define BFSHPP

#include <iostream>
#include <map>
#include <queue>
#include <vector>

using us_int = unsigned short int;

class BFS {
    public:
        BFS(
            std::vector < std::vector <int> > map,
            std::pair <us_int, us_int> coordinate,
            std::vector <char> preferenceEntityList
            );

        void BFSExecution(); // execute the BFS' algorithm

    private:
        void createExploredMap(); // auxiliar method that create a mask with the avaliable paths
        std::queue < std::pair <us_int, us_int> > BFSIteration(std::queue < std::pair <us_int, us_int> > actual);
        bool isValidCoord(us_int x, us_int y);
        bool isEntity(us_int x, us_int y);

        std::vector < std::vector <int> > _map;
        std::pair < us_int, us_int > _coordinate;
        std::vector < std::vector <bool> > _exploredMap;
        std::map <char, int> _preferenceList;
        us_int _dist;
        us_int _N; // N -> rowns // verificar se as variaveis foram inicializadas corretamente
        us_int _M; // M -> cols



};

#endif