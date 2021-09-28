#include "BlockCommentAutomaton.h"
// Could throw something in here to deal with the undefined case of hitting eof before the end of the comment.

void BlockCommentAutomaton::S0(const string& input) {
   if (input.at(index) == '#') {
      inputRead++;
      index++;
      S1(input);
   }
   else {
      Serr();
   }
}

void BlockCommentAutomaton::S1(const string& input) {
   if ((int)input.size() > index) {
      if (input.at(index) == '|') {
         inputRead++;
         index++;
         S2(input);
      }
   }
}

void BlockCommentAutomaton::S2(const string& input){
   if ((int)input.size() > index) {
      if (input.at(index) == '|') {
         inputRead++;
         index++;
         S3(input);
      }
      else {
         if (input.at(index) == '\n') {   // Accounting for newlines if needed.
            newLines++;
         }
         inputRead++;
         index++;
         S2(input);
      }
   }
   else {
      Serr();
   }
}

void BlockCommentAutomaton::S3(const string& input) {
   if ((int)input.size() > index) {
      if (input.at(index) == '|') {       // Block comment with multiple pipes in a row     ex; #| balhb alslsl ||#
         inputRead++;
         index++;
         S3(input);
      } else if (input.at(index) == '#') {  // Proper block comment
         inputRead++;
         index++;
      } else {
         if (input.at(index) == '\n') {   // Accounting for newlines if needed.
            newLines++;
         }
         inputRead++;                     // Block comment with pipe in the middle
         index++;                         // ...send back to S2
         S2(input);
      }
   }
   else {
      Serr();
   }
}
