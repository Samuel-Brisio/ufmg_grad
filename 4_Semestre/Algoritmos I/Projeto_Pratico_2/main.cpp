#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <vector>

void dijkstra(int nodes, std::vector <std::vector < int > > &edges, std::vector <std::vector < int > > &maximum_capacity, int source );
void make_heap(std::vector <std::pair <int, int> > &heap, std::vector <int> &index, int number);

void heapify(std::vector <std::pair <int, int> > &arr, int n, int i, std::vector <int> &index)
{
    int largest = i; // Initialize largest as root
    int l = 2 * i + 1; // left = 2*i + 1
    int r = 2 * i + 2; // right = 2*i + 2
 
    // If left child is larger than root
    if (l < n && arr[l].second > arr[largest].second)
        largest = l;
 
    // If right child is larger than largest so far
    if (r < n && arr[r].second > arr[largest].second)
        largest = r;
 
    // If largest is not root
    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        std::swap(index[i], index[largest]);

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest, index);
    }
}


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

        highways[u-1][v-1] = w;
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
    std::vector < int > pi (nodes, -1);
    pi[source] = INT32_MAX;

    std::vector <std::pair <int, int> > heap;
    std::vector <int> index; 

    for(int i = 0; i < nodes; i++) {
        std::pair <int, int> p (i, pi[i]);
        heap.push_back(p);
        index.push_back(i);
    }

    // Build heap (rearrange array)
    make_heap(heap, index, nodes);

    int size = heap.size();

    while (size != 0) {
        std::pair <int, int> u = heap[0];
        heap[0].second = INT32_MIN;

        for(int i = 0; i < nodes; i++) {
            int weight = edges[u.first][i];

            // if there is no edge
            if(weight == 0) continue;

            int new_pi = std::min(pi[u.first], weight);
            if(pi[i] < new_pi) {
                heap[index[i]] = std::pair <int, int> (i, new_pi);
                make_heap(heap, index, nodes);
                pi[i] = new_pi;
            }
        }
        size--;
    }

    pi[source] = 0;
    for(int i = 0; i < nodes; i++) {
        maximum_capacity[source][i] = pi[i];
    }

}

void make_heap(std::vector <std::pair <int, int> > &heap, std::vector <int> &index, int number) {
     // Build heap (rearrange array)
    for (int i = number / 2 - 1; i >= 0; i--) {
        heapify(heap, number, i, index);
    }
}