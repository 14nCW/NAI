#include <any>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "math.h"
using mojecyfry = std::map<std::string, int>;
using mojafunkcja_t = std::function<double (mojecyfry)>;

void wypisz(mojecyfry cyfry, mojafunkcja_t fun) {
    using namespace std;
        cout << fun(cyfry) << endl;
}

int main(int argc, char **argv) {
    using namespace std;
    vector<string> argumenty(argv, argv + argc);
    map<string, mojafunkcja_t> format;
    map<string, int> cyfry;

    for (int i = 2; i < argumenty.size(); i++) {
        cyfry.insert({
                cyfry.size() == 0 ? "pierwsza" : "druga",
                stoi(argumenty.at(i))
        });
    }

    format["add"] = [](map<string, int> map) {
        return map.at("pierwsza") + map.at("druga");
    };

    format["mod"] = [](map<string, int> map) {
        return map.at("pierwsza") %  map.at("druga");
    };

    format["sin"] = [](map<string, int> map) {
        double x = map.at("pierwsza");
        return sin(x);
    };

    try {
        auto selected_f = argumenty.at(1);
        wypisz(cyfry, format.at(selected_f));
    } catch (std::out_of_range aor) {
        cout << "Niestety. Podales zle argumenty." << endl << "Poprawna forma argumentowania:" << endl << "<add> <int x> <int y>"<< endl << "<mod> <int x> <int y>"<< endl << "<sin> <int x>";
        cout << endl;
    }
    return 0;
}