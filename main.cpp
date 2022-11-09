#include <iostream>
#include <vector>
#include <random>
#include <chrono>

using namespace std::chrono;

std::random_device rd;
std::mt19937 mt_generator(rd());

auto coords_generator(double r1, double r2) {
    std::uniform_real_distribution<> coords(r1, r2);
    return std::pair<double, double>(coords(mt_generator), coords(mt_generator));
}

auto random_probe = [](auto f,  int iterations, double r1, double r2) {
    auto current_p = coords_generator(r1, r2);
    auto best_point = current_p;

    for (int i = 0; i < iterations; ++i) {
        if (f(current_p) < f(best_point)) {
            best_point = current_p;
        }
        current_p = coords_generator(r1, r2);
    }
    return best_point;
};

int main() {

    auto boothFunc = [](std::pair<double, double> pair) {
        double x = pair.first, y = pair.second;
        return pow((x + 2 * y - 7), 2) + pow((2 * x + y - 5), 2);
    };

    auto matyasFunc = [](std::pair<double, double> pair) {
        double x = pair.first, y = pair.second;
        return 0.26 * (pow(x, 2) + pow(y, 2) - 0.48 * x * y);
    };

    auto treeHumpCamelFunc = [](std::pair<double, double> pair) {
        double x = pair.first, y = pair.second;
        return 2 * pow(x, 2) - 1.05 * pow(x, 4) + pow(x, 6) / 6 + x * y + pow(y, 2);
    };

    for (int i = 1; i <= 20; i++) {
        auto start = high_resolution_clock::now();
        auto bestBooth = random_probe(boothFunc, 1000000, -10, 10);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        std::cout   << "x: "
                    << bestBooth.first
                    << " y: "
                    << bestBooth.second
                    << "Booth: "
                    << boothFunc(bestBooth)
                    << " duration: "
                    << duration.count()
                    << std::endl;
    }

    std::cout << "--------------------------------" << std::endl;

    for (int i = 1; i <= 20; i++) {
        auto start = high_resolution_clock::now();
        auto bestMatyas = random_probe(matyasFunc, 1000000, -10, 10);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        std::cout   << "Matyas: "
                    << matyasFunc(bestMatyas)
                    << " duration: "
                    << duration.count()
                    << std::endl;

    }

    std::cout << "--------------------------------" << std::endl;


    for (int i = 1; i <= 20; i++) {
        auto start = high_resolution_clock::now();
        auto bestTreeHumpCamel = random_probe(treeHumpCamelFunc,  1000000, -5, 5);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        std::cout   << "TreeHumpCamel: "
                    << treeHumpCamelFunc(bestTreeHumpCamel)
                    << " duration: "
                    << duration.count()
                    << std::endl;
    }

    return 0;
}