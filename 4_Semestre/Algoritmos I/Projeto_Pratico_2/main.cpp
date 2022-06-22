#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <vector>

void dijkstra(int nodes, std::vector <std::vector < int > > &edges, std::vector <std::vector < int > > &maximum_capacity, int source );

int main() {
    /* 
    N -> cities
    M -> Number of Highway
    Q -> Queries
    */  
    int N, M, Q;
    std::cin >> N >> M >> Q;

    
    std::vector < std::vector < int > > highways (N, std::vector <int> (N)); 

    std::vector <std::vector < int > > maximum_capacity (N, std::vector <int> (N));

    for(int i = 0; i < M; i++) {
        /*
        u -> start city
        v -> end city
        w -> highway capacity
        */
        int u, v, w;
        std::cin >> u >> v >> w;

        highways[u-1][v-1] = std::max(highways[u-1][v-1], w);
    }

    for(int i = 0; i < N; i++) {
        dijkstra(N, highways, maximum_capacity, i);
    }

    for(int i = 0; i < Q; i++) {
        int u, v;
        std::cin >> u >> v;
        std::cout << maximum_capacity[u -1][v - 1] << std::endl;
    }

    return 0;
}

void dijkstra(int nodes, std::vector <std::vector < int > > &edges, std::vector <std::vector < int > > &maximum_capacity, int source ) {
    // pi -> store the maximum capacity between source and a node V
    std::vector < int > pi (nodes, INT32_MIN);
    pi[source] = INT32_MAX;

    std::priority_queue <std::pair <int, int> > pq;

    for(int i = 0; i < nodes; i++) {
        std::pair <int, int> p (pi[i], i);
        pq.push(p);
    }

    while (!pq.empty()) {
        std::pair <int, int> u = pq.top();
        pq.pop();

        for(int i = 0; i < nodes; i++) {
            int weight = edges[u.second][i];

            // if there is no edge
            if(weight == 0) continue;

            int new_pi = std::min(pi[u.second], weight);
            if(pi[i] < new_pi) {
                pq.push(std::pair<int, int> (new_pi, i));
                pi[i] = new_pi;
            }
        }
    }

    for(int i = 0; i < nodes; i++) {
        maximum_capacity[source][i] = pi[i];
    }
}
