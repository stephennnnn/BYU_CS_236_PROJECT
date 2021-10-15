#ifndef PROJECT1_STARTER_CODE_RULE_H
#define PROJECT1_STARTER_CODE_RULE_H

#include "Predicate.h"
#include <vector>

class Rule {
private:
   Predicate headPredicate;

   vector<Predicate> bodyPredicates;

public:
   Rule() {}
   ~Rule() {}

   //Setters and getters:
   void setHeadPredicate(Predicate headPred) {
      headPredicate = headPred;
   }
   Predicate getHeadPredicate() {
      return headPredicate;
   }
   void setBodyPredicates(vector<Predicate> bodyPreds) {
      bodyPredicates = bodyPreds;
   }
   vector<Predicate> getBodyPredicates() {
      return bodyPredicates;
   }
};


#endif //PROJECT1_STARTER_CODE_RULE_H
