#ifndef PROJECT1_STARTER_CODE_PREDICATE_H
#define PROJECT1_STARTER_CODE_PREDICATE_H

#include "Parameter.h"
#include <string>
#include <utility>
#include <vector>

using namespace std;

class Predicate {
private:
string ID;
vector<Parameter*> parameterList;

public:

   Predicate() {}
   ~Predicate() {}

// set & getters:
   void setID(string id) {
      ID = std::move(id);
   }
   string getID() const {
      return ID;
   }
   void setParameterList(vector<Parameter*> paramList) {
      parameterList = std::move(paramList);
   }
   vector<Parameter*> getParameterList() const {
      return parameterList;
   }

};

#endif //PROJECT1_STARTER_CODE_PREDICATE_H

// I don't think I need a .cpp for this one.