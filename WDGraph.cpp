//
// Created by david on 4/22/21.
//
#include <stack>
#include "WDGraph.hpp"
#include <string>
#include <list>
#include <utility>

using namespace std;

void WDGraph::resetTags(int num) {
    //change the tags of all the node to the given one
    for (auto &item : this->allNodes) {
        item.second.setTag(num);
    }
}

double WDGraph::shoretesPath(std::list<NodeData> *l, std::string src, std::string dst) {
    if (src==dst){return 1;}
    WDGraph::resetTags(0);
    WDGraph::BFS(src, dst);
    if (allNodes[dst].getTag()==0){
        return -1;
    }
    bool check = true;
    stack<string> s;
    s.push(dst);
    while (check) {
        bool insert = false;
        NodeData *temp = &allNodes[s.top()];
        if (temp->getTag() != 1) {
            for (const auto &node :temp->_nodeIn) {
                if (node.first.getTag() == temp->getTag() - 1 && !insert) {
                    s.push(node.first.getUnit());
                    insert= true;
                }
            }
        } else {
            check = false;
        }
    }
    //calculating the rate between to node (ex: km->m, rate = 1000)
    double rate=1;
    bool last = false;
    while (!s.empty() && !last){
        NodeData *temp = &allNodes[s.top()];
        s.pop();
        rate = rate * (temp->_nodeOut[allNodes[s.top()]]);
        if(allNodes[s.top()].getTag()==allNodes[dst].getTag()){
           last= true;
        }
    }
    return rate;
}

void WDGraph::BFS(std::string src, std::string dst) {

    allNodes[src].setTag(1);
    stack<string> s;
    s.push(src);
    while (!s.empty()) {
        NodeData *temp = &allNodes[s.top()];
        s.pop();

        for (auto it = temp->_nodeOut.begin(); it != temp->_nodeOut.end(); it++) {
            if (it->first.getTag() == 0 || temp->getTag() > it->first.getTag()) {
                allNodes[it->first.getUnit()].setTag(temp->getTag()+1);
                s.push(it->first.getUnit());
            }
        }
    }
}

