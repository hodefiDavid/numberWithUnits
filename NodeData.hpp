//
// Created by david on 4/21/21.
#include<map>
#include <utility>

#include <string>
#include <list>
# pragma once

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
    void addNodeIn(Node nd, double rate);
    void addNodeOut(Node nd, double rate);

    void setTag(int tag) {
        this->_tag = tag;
    }
    int getTag() const{return this->_tag;}

    std::string getUnit();

private:
    std::string _unit; //km/m/h/min...
    //Temporal data which can be used by algorithms
    int _tag;
};


