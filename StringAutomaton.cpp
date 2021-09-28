#include "StringAutomaton.h"

void StringAutomaton::S0(const string& input) {
   if (input.at(index) == '\'') {
      inputRead++;
      index++;
      S1(input);
   }
   else {
      Serr();
   }
}

void StringAutomaton::S1(const string& input) {
   if ((int)input.size() > index) {
      if (input.at(index) == '\'') {
         inputRead++;
         index++;
         S2(input);
      } else {
         if (input.at(index) == '\n') {
            newLines++;
         }
         inputRead++;
         index++;
         S1(input);
      }
   }
   else {
      end_of_file_bool = true;
   }
}

void StringAutomaton::S2(const string& input){
   if ((int)input.size() > index) {
      if (input.at(index) == '\'') {
         inputRead++;
         index++;
         S1(input);
      }
   }
}

