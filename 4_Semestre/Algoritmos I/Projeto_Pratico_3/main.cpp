#include <iostream>
#include <vector>

int main() {
    // tamanho da casa da vó
    int N, M;
    std::cin >> N >> M;

    // matriz que irá contem o mapa da casa da vo
    std::vector < std::vector < char > > mapa (N, std::vector <char> (M));

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            std::cin >> mapa[i][j];
        }
    }
    
    // numero de mesas
    int n_mesa;
    std::cin >> n_mesa;

    // vetor de pair's que irá conter as dimensoes das mesas
    std::vector < std::pair <int, int> > mesa_dim (n_mesa);

    for(int i = 0; i < n_mesa; i++) {
        std::cin >> mesa_dim[i].first >> mesa_dim[i].second;
    }

    return 0;
}