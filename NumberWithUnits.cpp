//
// Created by david on 4/16/21.
//

#include "NumberWithUnits.hpp"

using namespace ariel;
using namespace std;

//// not working right now !!
////filename should be in that form "location/filename.txt" just "filename.txt" if the file is in the same folder

NumberWithUnits NumberWithUnits::operator+() const {
    return *this;
}

NumberWithUnits NumberWithUnits::operator-() {
    return NumberWithUnits(0, "");
}

NumberWithUnits NumberWithUnits::operator+=(const NumberWithUnits &other) {
    return NumberWithUnits(0, "");
}

NumberWithUnits NumberWithUnits::operator-=(const NumberWithUnits &other) {
    return NumberWithUnits(0, "");
}

NumberWithUnits ariel::operator-(const NumberWithUnits &other) {
    return NumberWithUnits(0, "");
}

NumberWithUnits ariel::operator-(const NumberWithUnits &, const NumberWithUnits &) {
    return NumberWithUnits(0, "");
}

NumberWithUnits ariel::operator+(const NumberWithUnits &other) {
    return NumberWithUnits(0, "");
}

NumberWithUnits ariel::operator+(const NumberWithUnits &other, const NumberWithUnits &other1) {
    return NumberWithUnits(0, "");
}

bool ariel::operator<(const NumberWithUnits &nwu1, const NumberWithUnits &nwu2) {
    return false;
}

bool ariel::operator>(const NumberWithUnits &nwu1, const NumberWithUnits &nwu2) {
    return false;
}

bool ariel::operator<=(const NumberWithUnits &nwu1, const NumberWithUnits &nwu2) {
    return false;
}

bool ariel::operator>=(const NumberWithUnits &nwu1, const NumberWithUnits &nwu2) {
    return false;
}

bool ariel::operator==(const NumberWithUnits &lhs, const NumberWithUnits &rhs) {
    return false;
}

bool ariel::operator!=(const NumberWithUnits &lhs, const NumberWithUnits &rhs) {
    return false;
}

std::ostream &ariel::operator<<(ostream &os, const NumberWithUnits &nwu) {
    return os;
}

std::istream &ariel::operator>>(istream &is, NumberWithUnits &nwu) {
    return is;
}

void NumberWithUnits::read_units(ifstream &file) {

}

NumberWithUnits ariel::operator*(const NumberWithUnits &nwu, double n) {
    return NumberWithUnits(0, "");
}

NumberWithUnits ariel::operator*(double number, const NumberWithUnits &nwu) {
    return NumberWithUnits(0, "");
}

NumberWithUnits ariel::operator*(const NumberWithUnits &nwu, int number) {
    return NumberWithUnits(0, "");
}

NumberWithUnits ariel::operator*(int number, const NumberWithUnits &nwu) {
    return NumberWithUnits(0, "");
}






//    //the methode to get line at the time brought by https://www.w3schools.com/cpp/cpp_files.asp
//    string text;
//    // Read from the text file
//    ifstream MyReadFile("filename.txt");
//
//    // Use a while loop together with the getline() function to read the file line by line
////    while (getline (MyReadFile, myText)) {
////    // Output the text from the file
////    cout << myText;
////    }
//
//    // Close the file
//    MyReadFile.close();
//
//}



