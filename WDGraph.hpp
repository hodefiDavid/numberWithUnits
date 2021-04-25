//
// Created by david on 4/21/21.
//


#pragma once

#include <string>
#include <list>
#include "NodeData.hpp"
# pragma once

namespace wdg {
    class WDGraph {
        void resetTags(int num);

        double shortestPath(std::string src, std::string dst);

    public:
        std::map<std::string, Node> allNodes;

        bool unitExist(const std::string &str);
    private:

        void BFS(std::string src, std::string dst);
    };

}
