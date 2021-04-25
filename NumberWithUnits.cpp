//
// Created by david on 4/16/21.
//
#include "NumberWithUnits.hpp"
#include <algorithm>
#include <string>

using namespace ariel;
using namespace std;
using namespace wdg;


class Node{

public:
    //_nodeIn represent nodes that entering this node
    //the double value represent the rate between two nodes,
    //between tne node "km" and the node "m" the value of the double would be 1/1000 (because 1 km = 1000 m)
    std::map<Node,double> _nodeIn;//note: if NIS==USD==EUR so i cannot use double as key in the map
    //_nodeOut represent nodes that you can reach from this node
    //the double value represent the rate between two nodes,
    //between tne node "km" and the node "m" the value of the double would be 1/1000 (because 1 km = 1000 m)
    std::map<Node,double> _nodeOut;


    Node(const std::string& unit){
        this->_unit=unit;
        this->_tag=0;
    }
    void addNodeIn(Node nd, double rate){
        this->_nodeIn[nd] = rate;
    }
    void addNodeOut(Node nd, double rate){
        this->_nodeOut[nd] = rate;
    }

    void setTag(int tag) {
        this->_tag = tag;
    }
    int getTag() const{return this->_tag;}

    std::string Node::getUnit() {
        return this->_unit;
    }

private:
    std::string _unit; //km/m/h/min...
    //Temporal data which can be used by algorithms
    int _tag;

};

////filename should be in that form "location/filename.txt" just "filename.txt" if the file is in the same folder

//// not working right now !!
void sendErrorReadUnits(int row){
    string Row = to_string(row);
    string errorMsg = "the file doesn't mach the pattern:\n"
                      "\t""1 'unit1' =  'value' 'unit2' \n"
                      "\t""the problem is in row :";
    throw invalid_argument(errorMsg + Row);
}

void NumberWithUnits::buildNodesReadUnits(string firstU,string secondU, double val) {

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

void NumberWithUnits::read_units(ifstream &file) {
    string str;
    int row =0 ;
    while (getline(file,str)){
        int len=0;
        string firstU;
        string secondU;
        double val = 1;
        len = str.find('1');
        if (len == -1 ){
            sendErrorReadUnits(row);
        }
        str.erase(0,len+1);
        len = str.find('=');
        if (len == -1 ){
            sendErrorReadUnits(row);
        }
        firstU = str.substr(0,len);
        str.erase(0,len+1);

        while (!str.compare(0,1," ")){
            str.erase(0,1);
        }
        len = str.find(' ');
        if (len == -1 ){
            sendErrorReadUnits(row);
        }
        try {
            val = stod(str.substr(0,len+1));}
        catch (invalid_argument){
            sendErrorReadUnits(row);
        }
        str.erase(0,len+1);

        while (!str.compare(0,1," ")){
            str.erase(0,1);
        }
        secondU = str;
        erase(firstU, ' ');
        erase(secondU, ' ');
        row++;

        //building The nodes
        buildNodesReadUnits(firstU,secondU,val);
}

}

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

NumberWithUnits::NumberWithUnits(double num, std::string unitIn) {
    ////
    graph.allNodes[unitIn]=Node(unitIn);
    ///////
    //check if the unit exist
    if (graph.unitExist(unitIn)) {
        this->number = num;
        this->unit = unitIn;
    } else {
        throw std::runtime_error("the unit " + unitIn + " does not include in our library");
    }
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



