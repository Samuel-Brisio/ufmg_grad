#ifndef MAPINSERTORASSIGN
#define MAPINSERTORASSIGN

#include <map>

template <typename T, typename U>
void insert_or_assign(std::map <T, U> map, T key, U value) {
    if (map.find(key) == map.end()) {
        map.insert(std::pair <T, U> (key, value));
    } 
}

#endif