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
   vector<pair<int, int>> matchingHeaderIndices;
   vector<int> uniqueHeaderIndices;

public:
   Relation() {}

   Relation(string name, Header header) {
      this->name = name;
      this->header = header;
   }

   ~Relation() {}

//   void addIndices(int i, int j) {
//      matchingHeaderIndices.push_back(i, j);
//   }

   void setName(const string &name) {
      Relation::name = name;
   }

   const string &getName() const {
      return name;
   }

   const set<Tuple> &getTuples() const {
      return tuples;
   }

   const Header &getHeader() const {
      return header;
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
      for (auto tupleIterator: tuples) {
         ss << "  "; // indent first value
         for (unsigned int i = 0; i < header.getAttributes().size(); i++) {
            if (i == (header.getAttributes().size() - 1)) {
               ss << header.getAttributes().at(i) << "=" << tupleIterator.getValues().at(i)
                  << endl;   // if last element in tuple, print with newline
            } else {
               ss << header.getAttributes().at(i) << "=" << tupleIterator.getValues().at(i)
                  << ", "; // if not last element, print with comma and space
            }
         }
      }
      return ss.str();
   }

   // ============================================ relational operators ============================================

   Relation *selectType1(int pos1, string val) {   //   • select: parameters are index and value (relation column and value to select)
      Relation *tempRelation = new Relation(name, header);
      for (const auto &tupleIterator: tuples) {
         if (tupleIterator.getValues().at(pos1) == val) {
            tempRelation->addTuple(tupleIterator);
         }
      }
      return tempRelation;
   }

   Relation *selectType2(int pos1, int pos2) {   //   • select: parameters are index and index (relation columns to select on same values)
      Relation *tempRelation = new Relation(name, header);
      for (auto tupleIterator: tuples) {
         if (tupleIterator.getValues().at(pos1) == tupleIterator.getValues().at(pos2)) {
            tempRelation->addTuple(tupleIterator);
         }
      }
      return tempRelation;
   }

   Relation *project(vector<unsigned int> pos) {       //   • project: parameter is list of indices (the columns to keep)
      Relation *tempRelation = new Relation(name, header);
      for (auto tupleIterator: tuples) {
         Tuple tempTuple;
         for (unsigned int i = 0; i < pos.size(); i++) {
            tempTuple.addValue(tupleIterator.getValues().at(pos.at(i)));   //todo: breaking here.
         }
         tempRelation->addTuple(tempTuple);
      }
      return tempRelation;
   }

   Relation *rename(Header header1) {        //   • rename: parameter is list of attributes (defines the new header)
      Relation *tempRelation = new Relation(name, header1);     // Create new relation with proper name and header
      for (auto tupleIterator: tuples) {                   // Go through the tuples of the original vector and add them to the new relation
         Tuple tempTuple;
         for (unsigned int i = 0; i < tupleIterator.getValues().size(); i++) {
            tempTuple.addValue(tupleIterator.getValues().at(i));
         }
         tempRelation->addTuple(tempTuple);
      }
      return tempRelation;
   }


// (Natural) Join + 3 helper functions -------------------------------------------------------------------------------------------------

   Relation join(Relation r1, Relation r2) {
      Header newHeader = combineHeaders(r1.getHeader(), r2.getHeader());
      Relation newRel(r1.getName(), newHeader);   // name is arbitrary, it will be written over.
      for (auto tupleIterator1 : r1.getTuples()){
         for (auto tupleIterator2 : r2.getTuples()) {
            if (isJoinable(tupleIterator1, tupleIterator2)) {
               Tuple newTuple = combineTuples(tupleIterator1,tupleIterator2);
               newRel.addTuple(newTuple);
            }
         }
      }
      return newRel;
   }

   Header combineHeaders(Header h1, Header h2){    // newHeader = header1. Then add unique values from header2 onto the back of header2.
      Header newHeader = h1;
      int counter1 = 0;
      matchingHeaderIndices.clear();
      uniqueHeaderIndices.clear();
      for (auto attributeIterator2 : h2.getAttributes()) {
         bool seen = false;
         int counter2 = 0;
         for (auto attributeIterator1 : h1.getAttributes()) {
            if (attributeIterator2 == attributeIterator1) {             // If attribute is seen, add indices to vector
               seen = true;
               matchingHeaderIndices.push_back(pair<int, int> (counter2, counter1));
            }
            counter2++;
         }
         if (seen == false) {    // if attribute was not seen in original header, add to newHeader
            newHeader.addAttributes(attributeIterator2);
            uniqueHeaderIndices.push_back(counter1);
         }
         counter1++;
      }
      return newHeader;
   }

   bool isJoinable(Tuple t1, Tuple t2) {
      //Receives two tuples and information about where they should match (from the vector you created)
      bool isJoinable = true;
      for (unsigned int i = 0; i < matchingHeaderIndices.size(); i++) {
         if (t1.getValues().at(matchingHeaderIndices.at(i).first) != t2.getValues().at(matchingHeaderIndices.at(i).second)) {
            isJoinable = false;
         }
      }
      return isJoinable;
   }

   Tuple combineTuples(Tuple t1, Tuple t2) {
      Tuple newTuple = t1;
      for (unsigned int i = 0; i < uniqueHeaderIndices.size(); i++) {
         newTuple.addValue(t2.getValues().at(uniqueHeaderIndices.at(i)));
      }
      return newTuple;
   }

   // Union-----------------------------------------------------------------------------------------------------------

   bool unionize(Relation r) {  // relation.unionize(another relation);
      bool addedTuples = false;

      for (auto argTuplesIterator : r.getTuples()) {
         if (tuples.insert(argTuplesIterator).second) {
            addedTuples = true;
            // ex:
            //   C='CS101', N='C. Brown'
            cout << "  ";  // indent first value
            for (unsigned int i = 0; i < argTuplesIterator.getValues().size(); i++) {
               if (i == (argTuplesIterator.getValues().size() - 1)) {
                  cout << header.getAttributes().at(i) << "=" << argTuplesIterator.getValues().at(i) << endl;   // if last element in tuple, print with newline
               } else {
                  cout << header.getAttributes().at(i) << "=" << argTuplesIterator.getValues().at(i) << ", "; // if not last element, print with comma and space
               }
            }
         }
      }
      return addedTuples;
   }
};
#endif //PROJECT1_STARTER_CODE_RELATION_H
