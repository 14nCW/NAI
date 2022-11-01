#include <iostream>
#include <vector>
#include <functional>
#include <random>
#include <map>
#include <chrono>

using domain_t = std::vector<double>;
std::random_device rd;
std::mt19937 mt_generator(rd());

domain_t hill_climbing(const std::function<double(domain_t)> &f, domain_t start_point, std::function<std::vector<domain_t>()> get_close_points, int max_iterations) {
    domain_t best_p = start_point;
    for (int iteration = 0; iteration < max_iterations; iteration++) {
        auto close_points = get_close_points();
        auto best_neighbour = *std::min_element(close_points.begin(), close_points.end(), [f](auto a, auto b){return f(a) > f(b);});
        if (f(best_neighbour) < f(best_p)) best_p = best_neighbour;
    }
    return best_p;
}

int main(int argc, char **argv) {
    std::map<std::string, std::function<double (std::vector<double>)>> hill_formatery;

    hill_formatery["sphere"] = [](domain_t x) {
        return x[0]*x[0];
    };

    hill_formatery["rastrigin"] = [](domain_t x) {
        return 10 + (x[0] * x[0] - 10 * (cos(2 * std::numbers::pi * x[0]) * std::numbers::pi/180));
    };

    hill_formatery["rosenbrock"] = [](domain_t x) {
        return 100 * pow((x[0] - (x[0]*x[0])),2) + pow((1 - x[0]),2);
    };

    hill_formatery["styblinskiTang"] = [](domain_t x) {
        return (pow(x[0],4) - (16 * pow(x[0], 2)) + 5 * x[0])/2;
    };

    auto get_random_point = [=]() -> domain_t {
        std::uniform_real_distribution<double>distr(std::stod(argv[2]), std::stod(argv[3]));
        return {distr(mt_generator), distr(mt_generator)};
    };
    auto get_close_points_random = [=]() -> std::vector<domain_t> {
        std::uniform_real_distribution<double>distr(std::stod(argv[2]),std::stod(argv[3]));
        return {{distr(mt_generator), distr(mt_generator)}};
    };

    for (int i = 0; i < 20; i++) {
        auto start = std::chrono::high_resolution_clock::now();
        auto best1 = hill_climbing(hill_formatery.at(argv[1]), get_random_point(), get_close_points_random, 1000000);
        auto finish = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = finish - start;
        std::cout << "best x = " << best1[0] << " " << elapsed.count() << std::endl;
    }
    return 0;
}