#ifndef PROJECT1_STARTER_CODE_DATALOGPROGRAM_H
#define PROJECT1_STARTER_CODE_DATALOGPROGRAM_H

#include "Predicate.h"
#include "Rule.h"
#include <iostream>
#include <set>

#include <string>
#include <vector>
using namespace std;

class DatalogProgram {
private:
    vector<Predicate> schemes;
    vector<Predicate> facts;
    vector<Predicate> queries;
    vector<Rule> rules;
    set<string> domain;

public:
   DatalogProgram() {}
   ~DatalogProgram() {}

   // Setters:
   void addScheme(Predicate pred) {
      schemes.push_back(pred);
   }
   void addFact(Predicate pred) {
      facts.push_back(pred);
   }
   void addRule(Rule rule) {
      rules.push_back(rule);
   }
   void addQuery(Predicate pred) {
      queries.push_back(pred);
   }
   void addDomain(string d) {
      domain.insert(d);
   }

   // Getters:
   const vector<Predicate> &getSchemes() const {
      return schemes;
   }
   const vector<Predicate> &getFacts() const {
      return facts;
   }
   const vector<Predicate> &getQueries() const {
      return queries;
   }
   const vector<Rule> &getRules() const {
      return rules;
   }

   // Printing:
   void toString() {
      cout << "Schemes(" << schemes.size() << "):" << endl;
      for (unsigned int i = 0; i < schemes.size(); i++) {                        // Print out individual schemes
         cout << "  " << schemes.at(i).getID() << "(";
         for (unsigned int j = 0; j < schemes.at(i).getParameterList().size(); j++) {
            if (j < (schemes.at(i).getParameterList().size() - 1)) {    // Print out commas out correctly
               cout << schemes.at(i).getParameterList().at(j)->getP() << ",";
            }
            else {
               cout << schemes.at(i).getParameterList().at(j)->getP();
            }
         }
         cout << ")" << endl;
      }
      cout << "Facts(" << facts.size() << "):" << endl;
      for (unsigned int i = 0; i < facts.size(); i++) {                          // Print out individual facts
         cout << "  " << facts.at(i).getID() << "(";
         for (unsigned int j = 0; j < facts.at(i).getParameterList().size(); j++) {
            if (j < (facts.at(i).getParameterList().size() - 1)) {      // Print out commas correctly
               cout << facts.at(i).getParameterList().at(j)->getP() << ",";
            }
            else {
               cout << facts.at(i).getParameterList().at(j)->getP();
            }
         }
         cout << ")." << endl;
      }
      cout << "Rules(" << rules.size() << "):" << endl;
      for (unsigned int i = 0; i < rules.size(); i++) {
         // print each head predicate: headPredicate :-
         cout << "  " << rules.at(i).getHeadPredicate().getID() << "(";
         for (unsigned int j = 0; j < rules.at(i).getHeadPredicate().getParameterList().size(); j++) {
            if (j < (rules.at(i).getHeadPredicate().getParameterList().size() - 1)) {
               cout << rules.at(i).getHeadPredicate().getParameterList().at(j)->getP() << ",";
            }
            else {
               cout << rules.at(i).getHeadPredicate().getParameterList().at(j)->getP();
            }
         }
         cout << ") :- ";
         // print body predicates separated by commas. End with period.
         for (unsigned int j = 0; j < rules.at(i).getBodyPredicates().size(); j++) {
            cout << rules.at(i).getBodyPredicates().at(j).getID() << "(";
            for (unsigned int k = 0; k < rules.at(i).getBodyPredicates().at(j).getParameterList().size(); k++) {
               if (k < (rules.at(i).getBodyPredicates().at(j).getParameterList().size() - 1)) {
                  cout << rules.at(i).getBodyPredicates().at(j).getParameterList().at(k)->getP() << ",";
               }
               else {
                  cout << rules.at(i).getBodyPredicates().at(j).getParameterList().at(k)->getP();
               }
            }
            if (j < (rules.at(i).getBodyPredicates().size() - 1)) {
               cout << "),";
            }
         }
         cout << ")." << endl;
      }
      cout << "Queries(" << queries.size() << "):" << endl;
      for (unsigned int i = 0; i < queries.size(); i++) {
         cout << "  " << queries.at(i).getID() << "(";
         for (unsigned int j = 0; j < queries.at(i).getParameterList().size(); j++) {
            if (j < (queries.at(i).getParameterList().size() - 1)) {
               cout << queries.at(i).getParameterList().at(j)->getP() << ",";
            }
            else {
               cout << queries.at(i).getParameterList().at(j)->getP();
            }
         }
         cout << ")?" << endl;
      }
      cout << "Domain(" << domain.size() << "):" << endl;
      for (string domainItem : domain) {
         cout << "  " << domainItem << endl;
      }
   }
};

#endif //PROJECT1_STARTER_CODE_DATALOGPROGRAM_H
