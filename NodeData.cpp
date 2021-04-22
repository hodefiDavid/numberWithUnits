//
// Created by david on 4/22/21.
//

#include "NodeData.hpp"


void NodeData::addNodeIn(NodeData nd, double rate){
    this->_nodeIn[nd] = rate;
}
void NodeData::addNodeOut(NodeData nd, double rate){
    this->_nodeOut[nd] = rate;
}

std::string NodeData::getUnit() const {
    return this->_unit;
}


