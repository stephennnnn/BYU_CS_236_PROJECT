#ifndef PROJECT1_STARTER_CODE_INTERPRETER_H
#define PROJECT1_STARTER_CODE_INTERPRETER_H

#include <map>
#include "Database.h"
#include "DatalogProgram.h"
#include "Graph.h"

class Interpreter {
private:
   Database db;
   DatalogProgram dlp;
   Graph forwardGraph;
   Graph reverseGraph;

public:
   Interpreter(DatalogProgram d) {
      dlp = d;
   }
   ~Interpreter() {}

   Database getDb() const;
   const DatalogProgram &getDlp() const;

   void run();
   void runSchemes();
   void runFacts();
   void runQueries();
   Relation* evaluateQuery(const Predicate& p);
   void evaluateRules();
   void fixedPoint(set<int> scc);
   bool evaluateSingleRule(Rule r);
   void fillGraphs();
   static void sccToString(set<int> s);

};


#endif //PROJECT1_STARTER_CODE_INTERPRETER_H
