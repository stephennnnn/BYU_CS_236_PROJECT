#include "UndefinedBlockCommentAutomaton.h"


void UndefinedBlockCommentAutomaton::S0(const string& input) {
   if (input.at(index) == '#') {
      inputRead++;
      index++;
      S1(input);
   }
   else {
      Serr();
   }
}

void UndefinedBlockCommentAutomaton::S1(const string& input) {
   if ((int)input.size() > index) {
      if (input.at(index) == '|') {
         inputRead++;
         index++;
         S2(input);
      }
   }
}

void UndefinedBlockCommentAutomaton::S2(const string& input) {
   if ((int)input.size() > index) {
      if (input.at(index) == '|') {
         inputRead++;
         index++;
         S3(input);
      } else {
         if (input.at(index) == '\n') {   // Accounting for newlines if needed.
            newLines++;
         }
         inputRead++;
         index++;
         S2(input);
      }
   }
   else {
      end_of_file_bool = true;
   }
}

void UndefinedBlockCommentAutomaton::S3(const string& input) {
   if ((int)input.size() > index) {
      if (input.at(index) == '|') {       // Multiple pipes in a row
         inputRead++;
         index++;
         S3(input);
      }
      else if (input.at(index) == '#') {       // Proper block comment
         inputRead++;
         index++;
         Serr();                          // Is not supposed to be proper block comment in this automaton
      }
      else {
         if (input.at(index) == '\n') {   // Accounting for newlines if needed.
            newLines++;
         }
         inputRead++;                     // Block comment with pipe in the middle
         index++;
         S2(input);
      }
   }
   else {
      end_of_file_bool = true;
   }
}
