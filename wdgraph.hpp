//
// Created by david on 4/26/21.
//
#include <algorithm>
#include <string>
#include <map>
#include <utility>
#pragma once
static double TOLORANCE = 0.00001;
/////////////////////////////////////////////////////////////////////////////////
/////////////Node, hold the rate and the name of the unit////////////////////////
/////////////////////////////////////////////////////////////////////////////////
class Node {

public:
    //_nodeIn represent nodes that entering this node
    //the double value represent the rate between two nodes,
    //between tne node "km" and the node "m" the value of the double would be 1/1000 (because 1 km = 1000 m)
    std::map<std::string, double> _nodeIn;//note: if NIS==USD==EUR so i cannot use double as key in the map
    //_nodeOut represent nodes that you can reach from this node
    //the double value represent the rate between two nodes,
    //between tne node "km" and the node "m" the value of the double would be 1/1000 (because 1 km = 1000 m)
    std::map<std::string, double> _nodeOut;

    Node() :_tag(0), _unit(""){}

    Node(std::string unit) :_tag(0), _unit(std::move(unit)){
//        this->_unit = unit;
//        this->_tag = 0;
    }

//    ~Node() = default;


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
            std::stack<std::string> s;
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
        std::stack<std::string> s;
        s.push(src);
        while (!s.empty()) {
            Node *temp = &allNodes[s.top()];
            s.pop();

            for (auto it = temp->_nodeOut.begin(); it != temp->_nodeOut.end(); it++) {
                if (allNodes[it->first].getTag() == 0 || temp->getTag() < allNodes[it->first].getTag()) {
                    allNodes[it->first].setTag(temp->getTag() + 1);
                    s.push(it->first);
                }
            }
        }
        return allNodes[dst].getTag();
    }

};



