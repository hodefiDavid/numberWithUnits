#include <iostream>
#include "NumberWithUnits.hpp"

using namespace std;
using namespace ariel;

int main() {
    ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);
    NumberWithUnits a {2, "km"};   // 2 kilometers


    return 0;
}
