#include <iostream>
#include <vector>
#include <algorithm>
#include <array>
#include <random>
#include <ctime>

class KMeans {
    public:
        std::vector<int> _labels;
        std::vector<std::array<double, 2>> _centroids;

        KMeans(int K, std::string typ);
        void rand_init_centroids();
        void plus_init_centroids();
        void fit(const std::vector<std::array<double, 2>> &data);
    private:
        int _K;
        std::string init_typ;
        std::vector<std::array<double, 2>> _data;
        std::vector<int> _identify_nearest();
        std::array<double, 2> _next_center(std::vector<std::array<double, 2>> centroids); 
};

KMeans::KMeans(int K, std::string typ = "random") {
    _K = K;
    init_typ = typ;
}

void KMeans::rand_init_centroids() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, _data.size() - 1);

    for(int i = 0; i < _K; i++) {
        _centroids.push_back(_data[dis(gen)]);
    }
}

std::vector<int> KMeans::_identify_nearest() {
    std::vector<int> C(_data.size());
    for(size_t i = 0; i < _data.size(); i++) {
        std::array<double, 2> cur = _data[i];
        auto comp = [&cur, i](std::array<double, 2> x, std::array<double, 2> y) {
            double dis_x = 0.0, dis_y = 0.0;
            for(int j = 0; j < 2; j++) {
                dis_x += (cur[j] - x[j]) * (cur[j] - x[j]);
                dis_y += (cur[j] - y[j]) * (cur[j] - y[j]);
            }
            return dis_x < dis_y;
        };
        C[i] = std::min_element(_centroids.begin(), _centroids.end(), comp) - _centroids.begin();
    }
    return C;
}

void KMeans::plus_init_centroids() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, _data.size() - 1);

    _centroids.push_back(_data[dis(gen)]);

    auto next_center = [&](const std::vector<std::array<double, 2>>& centroids) {
        std::vector<int> distances = _identify_nearest();
        std::vector<double> probabilities(_data.size());

        double total_weight = 0.0;
        for(size_t i = 0; i < _data.size(); i++) {
            probabilities[i] = distances[i] * distances[i];
            total_weight += probabilities[i];
        }

        for(size_t i = 0; i < probabilities.size(); i++) {
            probabilities[i] /= total_weight;
        }

        std::random_device rd;
        std::mt19937 gen(rd());
        std::discrete_distribution distribution(probabilities.begin(), probabilities.end());

        int rand_index = distribution(gen);
        return _data[rand_index];
    };

    for(int i = 1; i < _K; i++) {
        _centroids.push_back(next_center(_centroids));
    }

}

void KMeans::fit(const std::vector<std::array<double, 2>> &data) {
    _data = data;
    if(init_typ == "kmeans++") {
        plus_init_centroids();
    } else if(init_typ == "random") {
        rand_init_centroids();
    } else {
        //throw error;
    }

    std::vector<std::array<double, 2>> prev;
    int iteration = 0;
 
    while(prev.empty() || !std::equal(_centroids.begin(), _centroids.end(), prev.begin())) {
        iteration++;
        std::cout << iteration << "\n";
        prev = _centroids;
        std::vector<int> C = _identify_nearest();

        std::vector<std::array<double, 2>> new_centroids(_K, std::array<double, 2>{0.0, 0.0});

        std::vector<int> cnt_label(_K, 0LL);
        for(size_t i = 0; i < _data.size(); i++) {
            for(int j = 0; j < 2; j++) {
                new_centroids[C[i]][j] += _data[i][j];
            }
            cnt_label[C[i]]++;
        }

        for(int i = 0; i < _K; i++) {
            for(int j = 0; j < 2; j++) {
                new_centroids[i][j] /= cnt_label[i];
            }
        }

        _centroids = new_centroids;
    }

    _labels = _identify_nearest();
    std::cout << "Iterations: " << iteration << "\n";
}



