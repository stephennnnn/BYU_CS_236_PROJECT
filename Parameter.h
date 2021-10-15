#ifndef PROJECT1_STARTER_CODE_PARAMETER_H
#define PROJECT1_STARTER_CODE_PARAMETER_H

#include <string>
using namespace std;

class Parameter {
private:

public:
Parameter(string s) {
   p = s;
}
~Parameter() {}
string p;

   const string &getP() const {
      return p;
   }

};


#endif //PROJECT1_STARTER_CODE_PARAMETER_H


// I don't think I need a .cpp for this one.