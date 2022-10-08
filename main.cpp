#include <any>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "math.h"
using mojafunkcja_t = std::function<int>;

void wypisz(mojafunkcja_t fun) {
    using namespace std;
    cout << "dupa mariana: " << endl;
}

int main(int argc, char **argv) {
    using namespace std;
    map<string, mojafunkcja_t> argument;
    argument["r"] = [](int x) {  };

    try {
        vector<string> argumenty(argv, argv + argc);
        auto selected_f = argumenty.at(1);
        wypisz(argument.at(selected_f));
    } catch (std::out_of_range aor) {
        cout << "podaj argument. Dostępne to: ";
        cout << endl;
    }
    return 0;
}