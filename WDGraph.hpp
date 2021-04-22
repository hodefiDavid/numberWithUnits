//
// Created by david on 4/21/21.
//

#ifndef WDGRAPH_WDGRAPH_HPP
#define WDGRAPH_WDGRAPH_HPP

#include <string>
#include <list>
#include "NodeData.hpp"

class WDGraph{
    void resetTags(int num);
    double shoretesPath( std::list<NodeData> *l,std::string src,std::string dst);
private:
    std::map<std::string , NodeData> allNodes;
    void BFS(std::string src,std::string dst);

};
















#endif //WDGRAPH_WDGRAPH_HPP
