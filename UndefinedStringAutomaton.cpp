#include "UndefinedStringAutomaton.h"

void UndefinedStringAutomaton::S0(const string& input) {
   if (input.at(index) == '\'') {
      inputRead++;
      index++;
      S1(input);
   }
   else {
      Serr();
   }
}

void UndefinedStringAutomaton::S1(const string& input) {
   if ((int)input.size() > index) {
      if (input.at(index) == '\'') {
         inputRead++;
         index++;
         S2(input);
      } else {
         inputRead++;
         index++;
         S1(input);
      }
   }
}

void UndefinedStringAutomaton::S2(const string& input) {
   if ((int)input.size() > index) {
      if (input.at(index) == '\'') {
         inputRead++;
         index++;
         S1(input);
      } else {
         Serr();  // This case would be a properly defined string.
      }
   }
}