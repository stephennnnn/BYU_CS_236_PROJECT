#ifndef PROJECT1_STARTER_CODE_INTERPRETER_H
#define PROJECT1_STARTER_CODE_INTERPRETER_H

#include <map>

#include "Header.h"
#include "Tuple.h"
#include "Relation.h"
#include "Database.h"
#include "DatalogProgram.h"
#include "Predicate.h"

class Interpreter {
private:
   Database db;
   DatalogProgram dlp;

public:
   Interpreter(DatalogProgram d) {
      dlp = d;
   }
   ~Interpreter() {}

   Database getDb() const;

   void run();
   void runSchemes();
   void runFacts();
   void runQueries();
   Relation* evaluateQuery(const Predicate& p);

};


#endif //PROJECT1_STARTER_CODE_INTERPRETER_H
