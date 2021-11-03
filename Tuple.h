#ifndef PROJECT1_STARTER_CODE_TUPLE_H
#define PROJECT1_STARTER_CODE_TUPLE_H

#include <vector>
#include <string>
using namespace std;

class Tuple {
//• Tuple - contains vector of values (string)
private:
   vector<string> values;

public:
   Tuple() {};

   Tuple(vector<string> v) {
      values = v;
   }

   ~Tuple() {}

   bool operator<(const Tuple &rhs) const {
      return values < rhs.values;
   }

   const vector<string> &getValues() const {
      return values;
   }

   void addValue(string s) {
      values.push_back(s);
   }

   // Watch for pointers

};


#endif //PROJECT1_STARTER_CODE_TUPLE_H
