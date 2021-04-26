//
// Created by david on 4/16/21.
//
#include "NumberWithUnits.hpp"
#include <algorithm>
#include <string>
#include <map>

using namespace ariel;
using namespace std;

double TOLORANCE = 0.00001;

/////////////////////////////////////////////////////////////////////////////////
/////////////Node, hold the rate and the name of the unit////////////////////////
/////////////////////////////////////////////////////////////////////////////////
class Node {

public:
    //_nodeIn represent nodes that entering this node
    //the double value represent the rate between two nodes,
    //between tne node "km" and the node "m" the value of the double would be 1/1000 (because 1 km = 1000 m)
    std::map<string, double> _nodeIn;//note: if NIS==USD==EUR so i cannot use double as key in the map
    //_nodeOut represent nodes that you can reach from this node
    //the double value represent the rate between two nodes,
    //between tne node "km" and the node "m" the value of the double would be 1/1000 (because 1 km = 1000 m)
    std::map<string, double> _nodeOut;

    explicit Node(const std::string &unit);

    ~Node() = default;


    void addNodeIn(Node nd, double rate) {
        this->_nodeIn[nd._unit] = rate;
    }

    void addNodeOut(Node nd, double rate) {
        this->_nodeOut[nd._unit] = rate;
    }

    void setTag(int tag) {
        this->_tag = tag;
    }

    int getTag() const { return this->_tag; }

    std::string getUnit() const {
        return this->_unit;
    }

private:
    std::string _unit; //km/m/h/min...
    //Temporal data which can be used by algorithms
    int _tag;

};

Node::Node(const string &unit) {
    this->_unit = unit;
    this->_tag = 0;
}

/////////////////////////////////////////////////////////////////////////////////
/////////////WDGraph, hold the nodes in graph////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
class WDGraph {

public:
    void resetTags(int num) {
        //change the tags of all the node to the given one
        for (auto &item : this->allNodes) {
            item.second.setTag(num);
        }
    }

    double shortestPath(std::string src, std::string dst) {
        if (src == dst) { return 1; }
        WDGraph::resetTags(0);

        if (WDGraph::BFS(src, dst) != 0) {

            bool check = true;
            stack<string> s;
            s.push(dst);
            while (check) {
                bool insert = false;
                Node *temp = &allNodes[s.top()];
                if (temp->getTag() != 1) {
                    for (const auto &node :temp->_nodeIn) {
                        if (allNodes[node.first].getTag() == temp->getTag() - 1 && !insert) {
                            s.push(node.first);
                            insert = true;
                        }
                    }
                } else {
                    check = false;
                }
            }
            //calculating the rate between to node (ex: km->m, rate = 1000)
            double rate = 1;
            bool last = false;
            while (!s.empty() && !last) {
                Node *temp = &allNodes[s.top()];
                s.pop();
                rate = rate * (temp->_nodeOut[s.top()]);
                if (allNodes[s.top()].getTag() == allNodes[dst].getTag()) {
                    last = true;
                }
            }
            return rate;

        } else {
            return -1;
        }
    }

    std::map<std::string, Node> allNodes;

    bool unitExist(const std::string &unit) const {
        return this->allNodes.contains(unit);
    }

private:

    double BFS(const std::string &src, std::string dst) {

        allNodes[src].setTag(1);
        stack<string> s;
        s.push(src);
        while (!s.empty()) {
            Node *temp = &allNodes[s.top()];
            s.pop();

            for (auto it = temp->_nodeOut.begin(); it != temp->_nodeOut.end(); it++) {
                if (allNodes[it->first].getTag() == 0 || temp->getTag() > allNodes[it->first].getTag()) {
                    allNodes[it->first].setTag(temp->getTag() + 1);
                    s.push(it->first);
                }
            }
        }
        return allNodes[dst].getTag();
    }

};

//the graph is static because I want it to keep all the connction\rate from all objects NumberWithUnits
static WDGraph graph;


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
        while (!str.compare(0, 1, " ")) {
            str.erase(0, 1);
        }

        len = str.find(' ');
        //checks for error
        if (len == -1) {
            sendErrorReadUnits(row);
        }
        try {
            val = stod(str.substr(0, ++len));
        }
            //checks for error
        catch (invalid_argument) {
            sendErrorReadUnits(row);
        }
        str.erase(0, ++len);

        //delete all the " " until we reach the second unit
        while (!str.compare(0, 1, " ")) {
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
        throw string (error);
    }
    this->number = this->number + rate*other.number;
    return *this;
}

NumberWithUnits NumberWithUnits::operator-=(const NumberWithUnits &other) {
    double rate = graph.shortestPath(other.unit, this->unit);
    if (rate==-1){
        string error = "when you used the operator -= you tried to convert to different kind of unit that not "
                       "connected to the unit: "+this->unit+", the unit that you entered was : "+other.unit;
        throw string (error);
    }
    this->number = this->number - rate*other.number;
    return *this;
}

NumberWithUnits ariel::operator-(const NumberWithUnits &other) {
    return NumberWithUnits(-other.number,other.unit);
}

NumberWithUnits ariel::operator-(const NumberWithUnits &a, const NumberWithUnits &b) {
    double rate = graph.shortestPath(b.unit, a.unit);
    if (rate==-1){
        string error = "when you used the operator - you tried to convert to different kind of unit that not "
                       "connected to the unit: "+a.unit+", the unit that you entered was : "+b.unit;
        throw string (error);
    }
    double number = a.number - rate*b.number;
    return NumberWithUnits(number,a.unit);
}

NumberWithUnits ariel::operator+(const NumberWithUnits &other) {
    return other;
}

NumberWithUnits ariel::operator+(const NumberWithUnits &a, const NumberWithUnits &b) {
    double rate = graph.shortestPath(b.unit, a.unit);
    if (rate==-1){
        string error = "when you used the operator + you tried to convert to different kind of unit that not "
                       "connected to the unit: "+a.unit+", the unit that you entered was : "+b.unit;
        throw string (error);
    }
    double number = a.number + rate*b.number;
    return NumberWithUnits(number,a.unit);
}

bool ariel::operator<(const NumberWithUnits &a, const NumberWithUnits &b) {
    double rate = graph.shortestPath(b.unit, a.unit);
    if (rate==-1){
        string error = "when you used the operator < you tried to convert to a different kind of unit that not "
                       "connected to the unit: "+a.unit+", the unit that you entered was : "+b.unit;
        throw string (error);
    }

    bool ans = (a.number < rate*b.number) || (a.number < rate*b.number+TOLORANCE);
    return ans;
}

bool ariel::operator>(const NumberWithUnits &a, const NumberWithUnits &b) {
    double rate = graph.shortestPath(b.unit, a.unit);
    if (rate==-1){
        string error = "when you used the operator < you tried to convert to a different kind of unit that not "
                       "connected to the unit: "+a.unit+", the unit that you entered was : "+b.unit;
        throw string (error);
    }
    bool ans = (a.number > rate*b.number)||(a.number > rate*b.number-TOLORANCE);
    return ans;
}

bool ariel::operator<=(const NumberWithUnits &a, const NumberWithUnits &b) {
    double rate = graph.shortestPath(b.unit, a.unit);
    if (rate==-1){
        string error = "when you used the operator < you tried to convert to a different kind of unit that not "
                       "connected to the unit: "+a.unit+", the unit that you entered was : "+b.unit;
        throw string (error);
    }
    bool ans = (a.number <= rate*b.number) || (a.number <= rate*b.number + TOLORANCE);
    return ans;
}

bool ariel::operator>=(const NumberWithUnits &a, const NumberWithUnits &b) {
    double rate = graph.shortestPath(b.unit, a.unit);
    if (rate==-1){
        string error = "when you used the operator < you tried to convert to a different kind of unit that not "
                       "connected to the unit: "+a.unit+", the unit that you entered was : "+b.unit;
        throw string (error);
    }
    bool ans = (a.number >= rate*b.number) || (a.number + TOLORANCE >= rate*b.number);
    return ans;
}

bool ariel::operator==(const NumberWithUnits &a, const NumberWithUnits &b) {
    double rate = graph.shortestPath(b.unit, a.unit);
    if (rate==-1){
        string error = "when you used the operator < you tried to convert to a different kind of unit that not "
                       "connected to the unit: "+a.unit+", the unit that you entered was : "+b.unit;
        throw string (error);
    }
    bool ans = (a.number == rate*b.number) || ((a.number <= rate*b.number + TOLORANCE)&& (a.number + TOLORANCE >= rate*b.number) );
    return ans;
}

bool ariel::operator!=(const NumberWithUnits &a, const NumberWithUnits &b) {
    bool ans = (a==b);
    //revert the operator ==
    return !ans;
}

std::ostream &ariel::operator<<(ostream &os, const NumberWithUnits &nwu) {
    string str = std::to_string (nwu.number);
    str.erase ( str.find_last_not_of('0') + 1, string::npos );
    if (str.ends_with('.')){
        str.erase(str.find_last_not_of('.')+1,string::npos);}
    str= str+"["+nwu.unit+"]";
    return os<<str;
}

std::istream &ariel::operator>>(istream &is, NumberWithUnits &nwu) {
    string str;
    string tempUnit;
    getline(is,str);
    size_t len = 0;
    double val;
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
    str.erase(0, ++len);
    len = str.find(']');
    if (len == -1) { sendErrorReadUnits(0);}
    tempUnit = str.substr(0, ++len);
    erase(tempUnit, ' ');

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



