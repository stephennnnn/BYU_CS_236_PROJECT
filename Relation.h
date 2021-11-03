#ifndef PROJECT1_STARTER_CODE_RELATION_H
#define PROJECT1_STARTER_CODE_RELATION_H

#include "Tuple.h"
#include "Header.h"
#include <set>
#include <iostream>
#include <sstream>
using namespace std;

class Relation {
   //• Relation - contains a set of Tuples associated with a name and Header
private:
   string name;
   Header header;
   set<Tuple> tuples;

public:
   Relation () {}

   Relation(string name, Header header) {
      this->name = name;
      this-> header = header;
   }
   ~Relation() {}

   void setName(const string &name) {
      Relation::name = name;
   }

   const string &getName() const {
      return name;
   }

   const set<Tuple> &getTuples() const {
      return tuples;
   }

   void setHeader(const Header &header) {
      Relation::header = header;
   }

   void addTuple(Tuple t) {
      tuples.insert(t);
   }

   string relationToString() { // Just printing out the tuples w/ header attributes.
      // print (header attribute)='(tuple value)'
      // ex:
      //  X='a', Y='c'
      ostringstream ss;
      if (header.getAttributes().size() == 0) {
         return ss.str();
      }
      for (auto tupleIterator : tuples) {
         ss << "  "; // indent first value
         for (unsigned int i = 0; i < header.getAttributes().size(); i++) {
            if (i == (header.getAttributes().size() - 1)) {
               ss << header.getAttributes().at(i) << "=" << tupleIterator.getValues().at(i) <<endl;   // if last element in tuple, print with newline
            }
            else {
               ss << header.getAttributes().at(i) << "=" << tupleIterator.getValues().at(i) << ", "; // if not last element, print with comma and space
            }
         }
      }
      return ss.str();
   }

//   string relationToString() { // Print out predicate, followed by Yes/No(# of tuples if yes), followed by the actual tuples
//      // If relation is empty, Predicate()? No
//      // Else, Predicate()? Yes(# of tuples)
//      //    tuples
//      // ex:
//      //marriedTo('Dan',X)? Yes(1)
//      //  X='Kim'
//      ostringstream ss;
//      if (tuples.empty()) {
//         ss << ;
//      }
//      else {
//         ss << ;
//      }
//      for (auto tupleIterator : tuples) {
//         ss << "  "; // indent first value
//         for (unsigned int i = 0; i < header.getAttributes().size(); i++) {
//            if (i == (header.getAttributes().size() - 1)) {
//               ss << header.getAttributes().at(i) << "=" << tupleIterator.getValues().at(i) <<endl;   // if last element in tuple, print with newline
//            }
//            else {
//               ss << header.getAttributes().at(i) << "=" << tupleIterator.getValues().at(i) << ", "; // if not last element, print with comma and space
//            }
//         }
//      }
//      return ss.str();
//   }

   // =========== operators ===========

   Relation* selectType1(int pos1, string val) {   //   • select: parameters are index and value (relation column and value to select)
      Relation *tempRelation = new Relation(name, header);
      for (const auto& tupleIterator : tuples) {
         if (tupleIterator.getValues().at(pos1) == val) {
            tempRelation->addTuple(tupleIterator);
         }
      }
      return tempRelation;
   }
   Relation* selectType2(int pos1, int pos2) {   //   • select: parameters are index and index (relation columns to select on same values)
      Relation *tempRelation = new Relation(name, header);
      for (auto tupleIterator : tuples) {
        if (tupleIterator.getValues().at(pos1) == tupleIterator.getValues().at(pos2)) {
            tempRelation->addTuple(tupleIterator);
        }
      }
      return tempRelation;
   }
   Relation* project(vector<unsigned int> pos) {       //   • project: parameter is list of indices (the columns to keep)
      Relation *tempRelation = new Relation(name, header);
      for (auto tupleIterator : tuples) {
         Tuple tempTuple;
         for (int i = 0; i < pos.size(); i++) {
            tempTuple.addValue(tupleIterator.getValues().at(pos.at(i)));
         }
         tempRelation->addTuple(tempTuple);
      }
      return tempRelation;
   }
   Relation* rename(Header header1) {        //   • rename: parameter is list of attributes (defines the new header)
      Relation *tempRelation = new Relation(name, header1);     // Create new relation with proper name and header
      for (auto tupleIterator : tuples) {                   // Go through the tuples of the original vector and add them to the new relation
         Tuple tempTuple;
         for (unsigned int i = 0; i < tupleIterator.getValues().size(); i++) {
            tempTuple.addValue(tupleIterator.getValues().at(i));
         }
         tempRelation->addTuple(tempTuple);
      }
      return tempRelation;
   }


//          Note that the list of indices given to project specifies the new order of the columns in the new relation it returns.
//          The methods select, project, rename all return a new Relation object.

};


#endif //PROJECT1_STARTER_CODE_RELATION_H
