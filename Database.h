#ifndef PROJECT1_STARTER_CODE_DATABASE_H
#define PROJECT1_STARTER_CODE_DATABASE_H

#include <map>
#include "Relation.h"
using namespace std;

class Database {
//• Database - contains a map from name (string) to Relation
private:
   // map from name to relation
   map<string, Relation> relationMap;

public:
   Database() {}
   ~Database() {}

   void addRelation(string n, Relation r) {
      relationMap.insert({n, r});
   }
   void addTuple(string name, Tuple t) {
      relationMap.at(name).addTuple(t);
   }

   Relation getRelation(string name) {
      return relationMap.find(name)->second; // Returns a copy
   }

   void toString() const {
      string output;
      for (auto i: relationMap) {
         cout << i.first << ": \n" << i.second.relationToString() << endl;
         // first = name, second = relation
         // relationTostring needs to return string
      }
      // could change the cout here to ss, return ss.str(), and cout in main if wanted.
   }

};


#endif //PROJECT1_STARTER_CODE_DATABASE_H
