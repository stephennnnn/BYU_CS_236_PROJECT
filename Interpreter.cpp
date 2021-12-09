#include "Interpreter.h"

   Database Interpreter::getDb() const {
      return db;
   }
   void Interpreter::run() {
      runSchemes();
      runFacts();
      evaluateRules();
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
   cout << "Query Evaluation" << endl;
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

//--------------------------------------------------------------------------------------------- (project 4) & 5

   void Interpreter::evaluateRules() {
      // Create graph nodes
      forwardGraph.setNodes(dlp);
      reverseGraph.setNodes(dlp);

      // Create graph edges
      fillGraphs();

      // find SCC:
      reverseGraph.dfsForestReverseGraph();  // (rule index as priority)
      forwardGraph.setPostOrder(reverseGraph.getPostOrder());
      forwardGraph.dfsForestForwardGraph();  // (reverse post order as priority)

      // call fixed point on each SCC:
      for (const auto& sccIterator : forwardGraph.getComponents()) {
         fixedPoint(sccIterator);   // todo: getting stuck in an infinite loop in this for loop or in fixedPoint
      }
   }

   void Interpreter::fixedPoint(set<int> scc) {  // pass in set of ints. Find rules that correspond to these ints and add them to a vector<Rule>. Evaluate that vector of rules as normal
      // find rules that correspond to SCC and add them to vector
      vector<Rule> componentRules;
      for (auto setIterator : scc) {
         componentRules.push_back(dlp.getRules().at(setIterator));
      }

      cout << "Rule Evaluation" << endl;
      cout << "SCC: ";
      // Print out SCC
      int sccSize = scc.size();
      int counter = 0;
      for (auto sccIterator : scc) {
         if (counter == (sccSize - 1)) {
            cout << "R" << sccIterator << endl;
         }
         else {
            cout << "R" << sccIterator << ", ";
         }
      }

      // Fixed point algorithm:
      bool keepGoing = true;
      int loopCounter = 0;
      do {  // Always run at least once
         keepGoing = false; // set loop to not run again unless tuples are added to database.

         // iterate through all rules and call evaluateSingleRule on them
         for (auto ruleIterator : componentRules) {
            ruleIterator.toString();                     // print out rule followed by new tuples
            if (evaluateSingleRule(ruleIterator)) {
               keepGoing = true;                         // if tuples were added to database, keep going.
            }
         }

         loopCounter++;
         // check scc only has 1 rule, check if set corresponding set in graph loops on itself
         // change output formatting
         // makefile in
      }
      while (keepGoing);

      cout << endl << loopCounter << " passes through the Rules." << endl << endl;
   }

   bool Interpreter::evaluateSingleRule(Rule r) {  // print out rule (everytime), print out new tuples (there may not be new tuples everytime)
      bool added = false;

      //--------------------Call evaluateQuery on body predicates and store new relations into a vector
      vector<Relation> relationVector;
      for (unsigned int i = 0; i < r.getBodyPredicates().size(); i++) {
         relationVector.push_back(*evaluateQuery(r.getBodyPredicates().at(i)));
      }

      //--------------------Call Join in order they are added to vector (left to right, low index to high index)
      Relation joinedRel = relationVector.at(0);   // 1st rel in vector
      for (unsigned int i = 1; i < (relationVector.size()); i++) {
         // combine rel.at(i) w/ rel.at(i+1)
         joinedRel = joinedRel.join(joinedRel, relationVector.at(i));
      }

      //--------------------Call project on the resulting relation using the columns from the head predicate

            // Find indices of joined relation
      vector<unsigned int> positions;
      for (unsigned int i = 0; i < r.getHeadPredicate().getParameterList().size(); i++) { // What we are looking for          -- go through the columns of the head predicate
         for (unsigned int j = 0; j < joinedRel.getHeader().getAttributes().size(); j++) {   // Where we are looking for it   -- check the indices that they match in the joined relation
            if (joinedRel.getHeader().getAttributes().at(j).compare(r.getHeadPredicate().getParameterList().at(i)->getP()) == 0) {
               positions.push_back(j);
               break;
            }
         }
      }

            // project
      Relation finalRel = *joinedRel.project(positions);

      //--------------------Union the final relation with the relation that appears in the database (search map and call union)


      if (db.getRelationByReference(r.getHeadPredicate().getID()).unionize(finalRel)) {
         added = true;
      }

      return added;
   }

   const DatalogProgram &Interpreter::getDlp() const {
      return dlp;
   }

   void Interpreter::fillGraphs() {
      // fill out right side of adjacency lists for both forward and reverse graphs
      for (int i = 0; i < dlp.getRules().size(); i++) {                   // For every rule...
         for (const Predicate& bodyPreds : dlp.getRules().at(i).getBodyPredicates()) {    // ...get bodyPreds...
            for (int j = 0; j < dlp.getRules().size(); j++) {             // ...and check bodyPreds against every rule.
               if (bodyPreds.getID() == dlp.getRules().at(j).getHeadPredicate().getID()) {  // if bodyPred matches a headPred,
                  forwardGraph.addEdge(i, j); // add headPred index (j) to dependent set of rule (i) in map
                  reverseGraph.addEdge(j, i); // add bodyPred index to (i)....???? in order to create the reverse graph
               }
            }
         }
      }
   }



