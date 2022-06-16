#include <iostream>
#include <vector>


int main() {
    /* 
    N -> cities
    M -> Number of Highway
    Q -> Queries
    */  
    int N, M, Q;
    std::cin >> N >> M >> Q;

    std::vector < std::vector < int > > highways (N, std::vector <int> (N)); 

    for(int i = 0; i < M; i++) {
        /*
        u -> start city
        v -> end city
        w -> highway capacity
        */
        int u, v, w;
        std::cin >> u >> v >> w;

        highways[u][v] = w;
    }

    return 0;
}