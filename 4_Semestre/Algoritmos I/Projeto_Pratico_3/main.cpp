#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <set>
#include <functional>

int max_area_histogram(std::vector <int> arr, std::vector < std::pair <int, int>> &reac);
int find_max_area(std::vector< std::vector < bool >> &mapa, std::vector < std::pair <int, int>> &reac);

int main() {
    // tamanho da casa da vó
    int N, M;
    std::cin >> N >> M;

    // matriz que irá contem o mapa da casa da vo
    std::vector < std::vector < bool >> mapa (N, std::vector <bool> (M));

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            char temp;
            std::cin >> temp;
            mapa[i][j] = (temp == '.') ? true: false;
        }
    }
    
    // numero de mesas
    int n_mesa;
    std::cin >> n_mesa;

    // vetor de pares que irá conter a area da mesa e sua largura
    std::vector < std::pair <int, int >> mesa_dim (n_mesa);

    //le a entrada, que contem as informções da dimensão das mesas e calcula a sua area
    for(int i = 0; i < n_mesa; i++) {
        // pair.first -> area da mesa
        // pair.second -> largura da mesa 
        int c, l;
        std::cin >> c >> l;
        mesa_dim[i].first = c * l;
        mesa_dim[i].second = l;
    }

    std::vector < std::pair <int, int>> reactangles;

    // Encontra as areas retangulares livres
    find_max_area(mapa, reactangles);

    std::sort(mesa_dim.rbegin(), mesa_dim.rend());
    std::sort(reactangles.begin(), reactangles.end());

    int reac_size = reactangles.size() - 1;

    std::vector <std::set <int, std::greater<int> >> areas_disponiveis (reactangles[reac_size].first);

    // Colaca as areas disponiveis em um vetor de sets, para retirar areas duplicadas
    for(int i = reac_size; i >= 0; i--) {
        areas_disponiveis[reactangles[i].first - 1].insert(reactangles[i].second);
    }

    int area_max = reactangles[reac_size].first;

    // Encontra a maior mesa
    for (auto mesa: mesa_dim) {
        for (int i = area_max - 1; i >= mesa.first - 1; i--) {
            for (auto area_largura: areas_disponiveis[i]) {

                int mesa_max_dim = std::max(mesa.first / mesa.second, mesa.second);
                int mesa_min_dim = mesa.first / mesa_max_dim;

                int reac_max_dim = std::max( (i + 1 ) / area_largura, area_largura);
                int reac_min_dim = (i + 1) / reac_max_dim;
                
                if(mesa_max_dim > reac_max_dim) continue;
                if(mesa_min_dim > reac_min_dim) continue;

                int mesa_largura = mesa.second;
                int comprimento = mesa.first / mesa_largura;
                std::cout << comprimento << ' ' << mesa_largura << std::endl;
                return 0;
            }
        }
    }

    return 0;
}


int max_area_histogram(std::vector <int> arr, std::vector < std::pair <int, int>> &reac) {
    std::stack <int> hstack, pstack;
    int max_area = 0;
    arr.push_back(0);

    for (int i = 0; i < arr.size(); i++) {
        int last_width = arr.size() + 1;
        
        while (!hstack.empty() && hstack.top() > arr[i]) {
            last_width = pstack.top();
            int area = (i - pstack.top()) * (hstack.top());
            reac.push_back(std::pair <int, int> (area, i - pstack.top()));

            max_area = std::max(area, max_area);
            hstack.pop();
            pstack.pop();
        }

        if (hstack.empty() || hstack.top() < arr[i]) {
            hstack.push(arr[i]);
            pstack.push(std::min(last_width, i));
        }
    }

    return max_area;
}

int find_max_area(std::vector< std::vector < bool >> &mapa, std::vector < std::pair <int, int>> &reac) {

    std::vector <int> arr (mapa[0].size());

    int max_area = 0;

    for (int i = 0; i < mapa.size(); i++) {
        for(int j = 0; j < mapa[0].size(); j++) {
            if (mapa[i][j] == false) arr[j] = 0;
            else arr[j] += 1;
        }
        max_area = std::max(max_area, max_area_histogram(arr, reac));
    }

    return max_area;
}