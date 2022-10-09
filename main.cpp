#include <any>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "math.h"
//using mojecyfry = std::map<std::string, int>;
using mojafunkcja_t = std::function<int(int)>;

//void wypisz(mojafunkcja_t fun) {
//    using namespace std;
//        cout <<  << endl;
//    }

int main(int argc, char **argv) {
    using namespace std;
    vector<string> argumenty(argv, argv + argc);
    map<string, mojafunkcja_t> argument;
    map<string, int> cyfry;

    for (int i = 0; i < argumenty.size(); i++) {
        cyfry.insert({{ cyfry.size() == 0 ? "pierwsza" : "druga", i}});
    }

    argument["r"] = [&cyfry](int x) {
        return cyfry.at("pierwsza") + cyfry.at("druga");
    };

    
    cout << argument[argumenty.at(0)];

    try {
        vector<string> argumenty(argv, argv + argc);
    } catch (std::out_of_range aor) {
        cout << "podaj argument. Dostępne to: ";
        cout << endl;
    }
    return 0;
}