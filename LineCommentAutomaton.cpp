#include "LineCommentAutomaton.h"


void LineCommentAutomaton::S0(const string& input) {
   if (input.at(index) == '#') {
      inputRead++;
      index++;
      if (input.at(index) == '|') {
         Serr();     // Would be a block comment or an undefined block comment.
         return;
      }
      S1(input);
   }
   else {
      Serr();
   }
}

void LineCommentAutomaton::S1(const string& input) {
   if ((int)input.size() > index) {
      if (input.at(index) == '\n') {
         return;
      }
//      else if {
//
//      }
      else {
         inputRead++;
         index++;
         S1(input);
      }
   }
}

