#include <any>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <cmath>
#include "vector"

using mojamapa_t = std::map<int, int>;
using mojafunkcja_t = std::function<double(std::vector<double>)>;

void wypisz(mojamapa_t mapa, mojafunkcja_t fun) {
    using namespace std;
    for (auto kv : mapa) {
        auto [k, v] = kv;
        cout << "klucz: " << k << "; wartosc " << fun(v) << endl;
    }
}

int main(int argc, char **argv) {
    using namespace std;
    map<int , int> mapa = {{10, 2}};
    map<string , mojafunkcja_t> formatery;
    formatery["sin"] = [](vector<double> x) { return sin(x[0]); };
//    formatery["add"] = [](int x, int y) { return (x + y); };
//    formatery["mod"] = [](int x) { return x%y; };
    try {
        vector<string> argumenty(argv, argv + argc);
        auto selected_f = argumenty.at(1);
        wypisz(mapa, formatery.at(selected_f));
    } catch (std::out_of_range aor) {
        cout << "podaj argument. Dostępne to: ";
        for (auto [k, v] : formatery) cout << " " << k;
        cout << endl;
    }
    return 0;
}