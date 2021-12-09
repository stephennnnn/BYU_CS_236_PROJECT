#ifndef PROJECT1_STARTER_CODE_GRAPH_H
#define PROJECT1_STARTER_CODE_GRAPH_H

#include <map>
#include <stack>
#include <set>
#include <iostream>
#include "DatalogProgram.h"

// do I need a forest class? --> implement the forest DFS stuff in your interpreter

class Graph {
private:
   map<int, set<int>> nodeMap;
   vector<bool> visited;
   stack<int> postOrder;
   set<int> tempSet;
   vector<set<int>> components;

public:
   Graph() {}

   void setNodes(DatalogProgram p) {
      int numRules = p.getRules().size();
      for (int i = 0; i < numRules; i++) {
         // insert index and initialize right side of adjacency list to emtpy set
         nodeMap.insert(pair<int,set<int>>(i, {}));
         visited.push_back(false);
      }
   }

   void addEdge(int a, int b) {
      // get node at a, add b into the set of node a
      nodeMap.find(a)->second.insert(b);
      //make sure this overwrites previous set
   }

   const map<int, set<int>> &getNodeMap() const {
      return nodeMap;
   }

   const vector<set<int>> &getComponents() const {
      return components;
   }

   const stack<int> &getPostOrder() const {
      return postOrder;
   }

   void setPostOrder(const stack<int> &postOrder) {
      Graph::postOrder = postOrder;
   }

//   DFS forest reverse graph:
//      for node in graph
//         if not visited
//            DFS(node)
//   end
   void dfsForestReverseGraph() {
      int visitedSize = visited.size();
      for (int i = 0; i < visitedSize; i++) {
         if (!visited.at(i)) {
            dfs(i);
         }
      }
   }

//   DFS forest forward graph:
//      for node in postorder
//         if not visited
//            DFS node
//            add SCC
//   end
   void dfsForestForwardGraph() {
      stack<int> postOrderCopy = postOrder;  // created copy of postOrder so that running dfs on forward graph doesn't screw up the postOrder stack
      while (!postOrderCopy.empty()) {
         int currentNode = postOrderCopy.top();
         if (!visited.at(currentNode)) {
            dfs(currentNode);
            components.push_back(tempSet);
            tempSet.clear();
         }
         postOrderCopy.pop();
      }
   }

//   DFS(node):
//      mark node as visited
//      for each adjacent node in adjacency list
//         if not visited
//            DFS(adjacent node)
//      add node to postorder stack
//      add to SCC
//   end
   void dfs(int n) {
      visited.at(n) = true;
      for (auto adjacentNodeIterator : nodeMap.find(n)->second) {   // for each adjacent node in adjacency list
         if (!visited.at(adjacentNodeIterator)) {
            dfs(adjacentNodeIterator);  //DFS(adjacent node)
         }
      }
      postOrder.push(n);
      tempSet.insert(n);
   }

   void toString() { /// output adjacency list
      cout << "Dependency Graph" << endl;
      for (const auto& nodeIterator : nodeMap) {
         cout << "R" << nodeIterator.first << ":";
         int size = nodeIterator.second.size();
         int counter = 0;
         for (auto adjacentNodeIterator : nodeIterator.second) {
            if (counter == (size - 1)) {
               cout << "R" << adjacentNodeIterator;
            }
            else {
               cout << "R" << adjacentNodeIterator << ",";
            }
            counter++;
         }
         cout << endl;
      }
      cout << endl;
   }


};


#endif //PROJECT1_STARTER_CODE_GRAPH_H

