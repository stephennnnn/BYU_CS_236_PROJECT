#ifndef PROJECT1_STARTER_CODE_HEADER_H
#define PROJECT1_STARTER_CODE_HEADER_H

#include <vector>
#include <string>
using namespace std;


class Header {
//• Header - contains vector of attributes (string)
private:
   // string name;            // not printing Headers by themselves, so not necessary.
   vector<string> attributes;

public:
   Header() {}
   ~Header() {}

   void setAttributes(vector<string> a) {
      attributes = a;
   }

   const vector<string> &getAttributes() const {
      return attributes;
   }

};


#endif //PROJECT1_STARTER_CODE_HEADER_H
