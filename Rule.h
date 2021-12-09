#ifndef PROJECT1_STARTER_CODE_RULE_H
#define PROJECT1_STARTER_CODE_RULE_H

#include "Predicate.h"
#include <vector>
#include <iostream>

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
   Predicate getHeadPredicate() const {
      return headPredicate;
   }
   void setBodyPredicates(vector<Predicate> bodyPreds) {
      bodyPredicates = bodyPreds;
   }
   vector<Predicate> getBodyPredicates() const {
      return bodyPredicates;
   }

   void toString() {
      // print out head predicate ----------
      cout << headPredicate.getID() << "(";
      for (unsigned int i = 0; i < headPredicate.getParameterList().size(); i++) {
         if (i == (headPredicate.getParameterList().size()) - 1) {  // if last parameter, print without comma
            cout << headPredicate.getParameterList().at(i)->getP();
         }
         else {
            cout << headPredicate.getParameterList().at(i)->getP() << ",";   // if not last parameter, print with comma
         }
      }
      cout << ") :- ";

      // print out body predicates ----------
      for (unsigned int i = 0; i < bodyPredicates.size(); i++) {
         cout << bodyPredicates.at(i).getID() << "(";
         // print out parameters inside predicate
         for (unsigned int j = 0; j < bodyPredicates.at(i).getParameterList().size(); j++) {
            if (j == (bodyPredicates.at(i).getParameterList().size()) - 1) {  // if last parameter, print without comma
               cout << bodyPredicates.at(i).getParameterList().at(j)->getP();
            }
            else {
               cout << bodyPredicates.at(i).getParameterList().at(j)->getP() << ",";   // if not last parameter, print with comma
            }
         }
         // if last bodyPredicate, print with period, else print with comma
         if (i == (bodyPredicates.size() - 1)) {
            cout << ")." << endl;
         }
         else {
            cout << "),";
         }
      }
   }
};


#endif //PROJECT1_STARTER_CODE_RULE_H
