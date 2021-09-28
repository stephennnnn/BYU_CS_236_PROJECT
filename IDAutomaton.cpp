#include "IDAutomaton.h"
#include <cctype>

void IDAutomaton::S0(const string& input) {
   if (isalpha(input.at(index))) {
      inputRead++;
      index++;
      S1(input);
   }
   else {
      Serr();
   }
}

void IDAutomaton::S1(const string& input) {
   if ((int)input.size() > index) {
      if (isalnum(input.at(index))) {
         inputRead++;
         index++;
         S1(input);
      }
   }
}