//
// Created by david on 4/22/21.
//
#include "NodeData.hpp"
# pragma once


void Node::addNodeIn(Node nd, double rate){
    this->_nodeIn[nd] = rate;
}
void Node::addNodeOut(Node nd, double rate){
    this->_nodeOut[nd] = rate;
}

std::string Node::getUnit() {
    return this->_unit;
}


