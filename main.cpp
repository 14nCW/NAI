#include <any>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using mojafunkcja_t = std::function<std::string(std::string)>;

int main(int argc, char **argv) {
    using namespace std;
    map<string, mojafunkcja_t> argumenty;
    argumenty["r"] = [](string x) { return "test"; };

    try {
        vector<string> argumenty(argv, argv + argc);
        auto selected_f = argumenty.at(1);
    } catch (std::out_of_range aor) {
        cout << "podaj argument. Dostępne to: ";
        cout << endl;
    }
    return 0;
}