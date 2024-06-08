#include <iostream>
#include <vector>
#include <array>
#include <fstream>

#include "util.h"
#include "kmeans.h"

int main() {
    std::ifstream fin("dataset.csv");
    
    if(!fin.is_open()) {
        std::cerr << "Error opening file";
        return EXIT_FAILURE;
    }
    
    std::vector<std::array<double, 2>> coordinates;
    std::vector<int> labels;

    std::array<double, 2> a;
    while(fin >> a) {
        coordinates.push_back(a);
        int l; fin >> l;
        labels.push_back(l);
    }
    fin.close();

    // kmeans time
    KMeans kmeans(5);
    kmeans.fit(coordinates);

    for(std::array<double, 2> centroid : kmeans._centroids) {
        std::cout << centroid << "\n";
    }
}