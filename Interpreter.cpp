#include "Interpreter.h"

Database Interpreter::getDb() const {
   return db;
}
void Interpreter::run() {
   runSchemes();
   runFacts();
   runQueries();
}
void Interpreter::runSchemes() {
   for (unsigned int i = 0; i < dlp.getSchemes().size(); i++) {
      // Get name & create header attributes:
      string name;
      name = dlp.getSchemes().at(i).getID();

      Header headerAttributes;
      vector<string> attributes;
//      cout << "Adding attributes to header (" << i << ")" << endl;
      for (unsigned int j = 0; j < dlp.getSchemes().at(i).getParameterList().size(); j++) {
         attributes.push_back(dlp.getSchemes().at(i).getParameterList().at(j)->getP());
//         cout << "Test: " << dlp.getSchemes().at(i).getParameterList().at(j)->getP() << endl;
      }
      headerAttributes.setAttributes(attributes);

      // Create relation:
      Relation relation(name, headerAttributes);

      // Insert relation by name into map in database
      db.addRelation(name, relation);
   }
}
void Interpreter::runFacts() {
   for (const auto & i : dlp.getFacts()) {
      // Get tuple name and values
      string name;
      name = i.getID();

      vector<string> values;
//      cout << "Adding values to tuple (" << i << ")" << endl;
      for (unsigned int j = 0; j < i.getParameterList().size(); j++) {
         values.push_back(i.getParameterList().at(j)->getP());
//         cout << "Test: " << dlp.getFacts().at(i).getParameterList().at(j)->getP() << endl;
      }
      // Create tuple
      Tuple tuple(values);

      db.addTuple(name, tuple);
   }
}
void Interpreter::runQueries() {
   for (auto & query : dlp.getQueries()) {
      Relation* answer = evaluateQuery(query);
      // print query name(parameters)? Yes(# tuples)/No(if tuples = empty)
      cout << query.getID() << "(";
      // print parameters:
      for (unsigned int i = 0; i < query.getParameterList().size(); i++) {
         if (i == (query.getParameterList().size()) - 1) {  // if last parameter, print without comma
            cout << query.getParameterList().at(i)->getP();
         }
         else {
            cout << query.getParameterList().at(i)->getP() << ",";   // if not last parameter, print with comma
         }
      }
      cout << ")? ";
      if (answer->getTuples().empty()) {
         cout << "No" << endl;
      }
      else {
         cout << "Yes(" << answer->getTuples().size() << ")" << endl;
      }
      cout << answer->relationToString();  // print out tuples
   }


}
 Relation* Interpreter::evaluateQuery(const Predicate& p) {
   Relation *answer = new Relation;
   //      get the relation ‘r’ with the same name as the query ‘q’
   *answer = db.getRelation(p.getID());

   vector<unsigned int> positions;
   vector<string> values;
   map<string, unsigned int> posValueMap;
   unsigned int index = 0;
   for (auto currParam : p.getParameterList()) {
      if (currParam->isConstant()) {
         // select type 1
         answer = answer->selectType1(index, currParam->getP());
      }
      // check if already seen
      else {
         if (posValueMap.find(currParam->getP()) == posValueMap.end()) {   // if not seen before, mark as seen.
            positions.push_back(index);
            values.push_back(currParam->getP());
            posValueMap.insert({currParam->getP(), index});
         }
         else {
            answer = answer->selectType2(index, posValueMap.at(currParam->getP()));
         }
      }
      index++;
   }
   //      project using the positions of the variables in ‘q’
   answer = answer->project(positions);
   //      rename to match the names of variables in ‘q’
   Header tempHeader;
   tempHeader.setAttributes(values);
   answer = answer->rename(tempHeader);

   return answer;
}


