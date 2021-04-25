#include <iostream>
#include "WDGraph.hpp"
#include "NodeData.hpp"

using namespace std;
using namespace wdg;

int main() {


//    WDGraph g;
    Node a =(Node("a"));
    string s = a.getUnit();
    cout<<s;
//    NodeData b = NodeData("b");
//    NodeData c = NodeData("c");
//
//    g.allNodes["a"]= a;
//    g.allNodes["b"]=b;
//    g.allNodes["c"]=c;
//    cout<<g.unitExist("k")<<endl;
//    cout<<g.unitExist("a")<<endl;
//    cout<<g.unitExist("c")<<endl;
//    cout<<g.allNodes.size()<<endl;

    return 0;
}
