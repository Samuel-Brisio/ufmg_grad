#include "bfs.hpp"

BFS::BFS(
    std::vector < std::vector <char> > map,
    std::pair <us_int, us_int> coordinate,
    std::vector <char> preferenceEntityList
    )
{
   _map = map; 
   _coordinate = coordinate;
   _preferenceEntityList = preferenceEntityList; 
   _dist = 0;

   _N = map.size();
   _M = map[0].size();

   createExploredMap();
}

void BFS::createExploredMap() {
    _exploredMap.resize(_M, std::vector <bool> (_N));
}

void BFS::BFSExecution() {
    std::queue < std::pair <us_int, us_int> > actual;
    actual.push(_coordinate);

    while(actual.size() != 0) {
        actual = BFSIteration(actual);
    }

}

std::queue < std::pair <us_int, us_int> > BFS::BFSIteration(std::queue < std::pair <us_int, us_int> > actual) {
    std::queue < std::pair <us_int, us_int> > nextLayer; // next layer of execution of the BFS
    
    while(actual.size() != 0) {
        std::pair < us_int, us_int > coord;

        coord = actual.front();
        actual.pop();

        isEntity(coord.first, coord.second);

        if(isValidCoord(coord.first + 1, coord.second)) {
            nextLayer.push(std::pair <us_int, us_int> (coord.first + 1, coord.second));
        }
        if(isValidCoord(coord.first - 1, coord.second)) {
            nextLayer.push(std::pair <us_int, us_int> (coord.first - 1, coord.second));
        }
        if(isValidCoord(coord.first, coord.second + 1)) {
            nextLayer.push(std::pair <us_int, us_int> (coord.first, coord.second + 1));
        }
        if(isValidCoord(coord.first, coord.second - 1)) {
            nextLayer.push(std::pair <us_int, us_int> (coord.first, coord.second - 1));
        }
    }

    _dist++;

    return nextLayer;
}

bool BFS::isValidCoord(us_int x, us_int y) {
    char description = _map[x][y];

    if(x < 0 || y < 0 || x >= _N || y >= _M) return false; // if the coordinate is inside the map
    if(description == '-') return false; // if the coordinate is a valid path
    if(_exploredMap[x][y]) return false; // if this coordinate is already explored
    return true;
}

bool BFS::isEntity(us_int x, us_int y) {
    char description = _map[x][y];

    if(description >= 'a' && description <= 'z') {
        //_preferenceList.insert_or_assign(description, _dist);
        insert_or_assign<char, us_int> (_preferenceList, description, _dist);
        return true;
    }
    return false;
}

std::vector <char> BFS::sortedSolution() {
    // sort the vector in the descendent order
    std::vector <std::pair <char, int> > list;

    for(auto e: _preferenceList) {
        list.push_back(e);
    }


    std::sort(list.begin(), list.end(), [](const std::pair <char, us_int> &a, const std::pair <char, int> &b) -> bool {return a.second < b.second;});
    
    std::vector <char> preference;

    for(auto e: list) {
        preference.push_back(e.first);
    }

    return preference;
}