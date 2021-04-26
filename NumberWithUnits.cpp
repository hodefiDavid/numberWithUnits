//
// Created by david on 4/16/21.
//
#include "NumberWithUnits.hpp"
#include "wdgraph.hpp"
#include <algorithm>
#include <string>
#include <map>
#include <sstream>

using namespace ariel;
using namespace std;


WDGraph NumberWithUnits::graph;


/**
 * sendErrorReadUnits function send an error if the function read units failed
 * @param row represent the row number which the error occur
 */
void sendErrorReadUnits(int row) {
    string Row = to_string(row);
    string errorMsg = "the file doesn't mach the pattern:\n"
                      "\t""1 'unit1' =  'value' 'unit2' \n"
                      "\t""the problem is in row :";
    throw invalid_argument(errorMsg + Row);
}

/**
 * buildNodesReadUnits function build Nodes and put the in the graph
 * the function build according to this pattern :
 * 1 'unit1' =  'value' 'unit2'
 *
 * @param firstU represent the first unit
 * @param secondU represent the second unit
 * @param val represent the value of the second unit
 */
void NumberWithUnits::buildNodesReadUnits(const string &firstU, const string &secondU, double val) {

    if (!graph.unitExist(firstU)) {
        graph.allNodes[firstU] = Node(firstU);
    }
    if (!graph.unitExist(secondU)) {
        graph.allNodes[secondU] = Node(secondU);
    }
    graph.allNodes[firstU].addNodeOut(graph.allNodes[secondU], val);
    graph.allNodes[firstU].addNodeIn(graph.allNodes[secondU], 1.0 / val);

    graph.allNodes[secondU].addNodeOut(graph.allNodes[firstU], 1.0 / val);
    graph.allNodes[secondU].addNodeIn(graph.allNodes[firstU], val);
}

/**
 * read_units function read units from ifstream and put the data in the graph
 * every row in the file should be in that pattern :
 * 1 'unit1' =  'value' 'unit2'
 * @param file repersent the read file that the function read from
 */
void NumberWithUnits::read_units(ifstream &file) {
    string str;
    int row = 0;
    while (getline(file, str)) {
        //temporary length in order to locate were we are in the string
        size_t len = 0;

        //firstU and secondU represent units1\2 as shown above
        string firstU;
        string secondU;
        //represent the value of the second unit
        double val = 1;

        len = str.find('1');
        //checks for error
        if (len == -1) { sendErrorReadUnits(row); }
        //delete all the chars until we 1 (include 1)
        str.erase(0, ++len);
        //find the next place '=' appear
        len = str.find('=');
        //checks for error
        if (len == -1) { sendErrorReadUnits(row); }

        firstU = str.substr(0, len);
        //delete all the chars until we '=' (include '=')
        str.erase(0, len + 1);

        //delete all the " " until we reach the value
        while (0 == str.compare(0, 1, " ")) {
            str.erase(0, 1);
        }

        len = str.find(' ');
        //checks for error
        if (len == -1) {
            sendErrorReadUnits(row);
        }
        try {
            val = stod(str.substr(0, len));// + 1
        }
            //checks for error
        catch (exception&) {
            sendErrorReadUnits(row);
        }
        str.erase(0, len + 1);

        //delete all the " " until we reach the second unit
        while (0 == str.compare(0, 1, " ")) {
            str.erase(0, 1);
        }

        secondU = str;
        //delete all the unnecessary " "
        erase(firstU, ' ');
        erase(secondU, ' ');
        row++;

        //building The nodes
        buildNodesReadUnits(firstU, secondU, val);
    }

}

NumberWithUnits::NumberWithUnits(const double num, const std::string &unitIn) {
    //check if the unit exist
    if (graph.unitExist(unitIn)) {
        this->number = num;
        this->unit = unitIn;
    } else {
        throw std::runtime_error("the unit " + unitIn + " does not include in our library");
    }
}


NumberWithUnits NumberWithUnits::operator+() const {
    return *this;
}

NumberWithUnits NumberWithUnits::operator-() {
    return NumberWithUnits(-this->number, this->unit);
}

NumberWithUnits NumberWithUnits::operator+=(const NumberWithUnits &other) {
    double rate = graph.shortestPath(other.unit, this->unit);
    if (rate==-1){
        string error = "when you used the operator += you tried to convert to a different kind of unit that not "
                       "connected to the unit: "+this->unit+", the unit that you entered was : "+other.unit;
        throw runtime_error (error);
    }
    this->number = this->number + rate*other.number;
    return *this;
}

NumberWithUnits NumberWithUnits::operator-=(const NumberWithUnits &other) {
    double rate = graph.shortestPath(other.unit, this->unit);
    if (rate==-1){
        string error = "when you used the operator -= you tried to convert to different kind of unit that not "
                       "connected to the unit: "+this->unit+", the unit that you entered was : "+other.unit;
        throw runtime_error (error);
    }
    this->number = this->number - rate*other.number;
    return *this;
}

//NumberWithUnits ariel::operator-(const NumberWithUnits &other) {
//    return NumberWithUnits(-other.number,other.unit);
//}

NumberWithUnits ariel::operator-(const NumberWithUnits &a, const NumberWithUnits &b) {
    double rate = NumberWithUnits::graph.shortestPath(b.unit, a.unit);
    if (rate==-1){
        string error = "when you used the operator - you tried to convert to different kind of unit that not "
                       "connected to the unit: "+a.unit+", the unit that you entered was : "+b.unit;
        throw runtime_error (error);
    }
    double number = a.number - rate*b.number;
    return NumberWithUnits(number,a.unit);
}

//NumberWithUnits ariel::operator+(const NumberWithUnits &other) {
//    return other;
//}

NumberWithUnits ariel::operator+(const NumberWithUnits &a, const NumberWithUnits &b) {
    double rate = NumberWithUnits::graph.shortestPath(b.unit, a.unit);
    if (rate==-1){
        string error = "when you used the operator + you tried to convert to different kind of unit that not "
                       "connected to the unit: "+a.unit+", the unit that you entered was : "+b.unit;
        throw runtime_error(error);
    }
    double number = a.number + rate*b.number;
    return NumberWithUnits(number,a.unit);
}

bool ariel::operator<(const NumberWithUnits &a, const NumberWithUnits &b) {
    double rate =  NumberWithUnits::graph.shortestPath(b.unit, a.unit);
    if (rate==-1){
        string error = "when you used the operator < you tried to convert to a different kind of unit that not "
                       "connected to the unit: "+a.unit+", the unit that you entered was : "+b.unit;
        throw runtime_error (error);
    }

    bool ans = (a.number < rate*b.number);// || (a.number < rate*b.number+TOLORANCE);
    return ans;
}

bool ariel::operator>(const NumberWithUnits &a, const NumberWithUnits &b) {
    double rate =  NumberWithUnits::graph.shortestPath(b.unit, a.unit);
    if (rate==-1){
        string error = "when you used the operator < you tried to convert to a different kind of unit that not "
                       "connected to the unit: "+a.unit+", the unit that you entered was : "+b.unit;
        throw runtime_error (error);
    }
    bool ans = (a.number > rate*b.number) && (abs(a.number - rate*b.number)>TOLORANCE);
    return ans;
}

bool ariel::operator<=(const NumberWithUnits &a, const NumberWithUnits &b) {
    double rate =  NumberWithUnits::graph.shortestPath(b.unit, a.unit);
    if (rate==-1){
        string error = "when you used the operator < you tried to convert to a different kind of unit that not "
                       "connected to the unit: "+a.unit+", the unit that you entered was : "+b.unit;
        throw runtime_error (error);
    }
    bool ans = (a.number <= rate*b.number) || (a.number <= rate*b.number + TOLORANCE);
    return ans;
}

bool ariel::operator>=(const NumberWithUnits &a, const NumberWithUnits &b) {
    double rate =  NumberWithUnits::graph.shortestPath(b.unit, a.unit);
    if (rate==-1){
        string error = "when you used the operator < you tried to convert to a different kind of unit that not "
                       "connected to the unit: "+a.unit+", the unit that you entered was : "+b.unit;
        throw runtime_error (error);
    }
    bool ans = (a.number >= rate*b.number) || (a.number + TOLORANCE >= rate*b.number);
    return ans;
}


bool ariel::NumberWithUnits::operator==(const NumberWithUnits& b)const{
    double rate =  NumberWithUnits::graph.shortestPath(b.unit, unit);
    if (rate==-1){
        string error = "when you used the operator < you tried to convert to a different kind of unit that not "
                       "connected to the unit: "+unit+", the unit that you entered was : "+b.unit;
        throw runtime_error (error);
    }
    bool ans = (number == rate*b.number) || ((number <= rate*b.number + TOLORANCE)&& (number + TOLORANCE >= rate*b.number) );
    return ans;
}


bool ariel::NumberWithUnits::operator!=(const NumberWithUnits &b) const{
    bool ans = (*this==b);
    //revert the operator ==
    return !ans;
}

std::ostream &ariel::operator<<(ostream &os, const NumberWithUnits &nwu) {
//    string str = std::to_string (nwu.number);
//    str.erase ( str.find_last_not_of('0') + 1, string::npos );
//    if (str.ends_with('.')){
//        str.erase(str.find_last_not_of('.')+1,string::npos);}
//    str= str+"["+nwu.unit+"]";
//    string str = to_string(nwu.number)+"["+nwu.unit+"]";
    return os<< nwu.number << "[" << nwu.unit << "]";
}

std::istream &ariel::operator>>(istream &is, NumberWithUnits &nwu) {
    string str;
    string tempUnit;
    if (!getline(is,str,']'))
    { sendErrorReadUnits(0);}

    size_t len = 0;
    double val = 0;
    len = str.find('[');
    //checks for error
    if (len == -1) { sendErrorReadUnits(0);}
    try {
        val = stod(str.substr(0, ++len));
    }
        //checks for error
    catch (invalid_argument) {
        sendErrorReadUnits(0);
    }
    str.erase(0, len);//+1
//    len = str.find(']');
//    if (len == -1) { sendErrorReadUnits(0);}
//    tempUnit = str.substr(0, len+1);
    tempUnit = str;
    erase(tempUnit, ' ');
    if(!NumberWithUnits::graph.unitExist(tempUnit)){
        sendErrorReadUnits(0);
    }
    str.erase(0, len+1);//+1//neew
    while (0 ==str.compare(0, 1, " ")) {
        str.erase(0, 1);
    }
    nwu.unit = tempUnit;
    nwu.number = val;
    return is;
}

NumberWithUnits ariel::operator*(const NumberWithUnits &nwu, double num) {
    return NumberWithUnits(nwu.number*num, nwu.unit);
}

NumberWithUnits ariel::operator*(double num, const NumberWithUnits &nwu) {
    return NumberWithUnits(nwu.number*num, nwu.unit);
}

NumberWithUnits ariel::operator*(const NumberWithUnits &nwu, int num) {
    return NumberWithUnits(nwu.number*((double)num), nwu.unit);
}

NumberWithUnits ariel::operator*(int num, const NumberWithUnits &nwu) {
    return NumberWithUnits(nwu.number*((double)num), nwu.unit);
}



