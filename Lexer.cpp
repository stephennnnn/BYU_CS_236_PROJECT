#include "Lexer.h"
//#include "ColonAutomaton.h"
//#include "ColonDashAutomaton.h"
#include "MatcherAutomaton.h"
#include "IDAutomaton.h"
#include "StringAutomaton.h"
#include "BlockCommentAutomaton.h"
#include "LineCommentAutomaton.h"
#include "UndefinedStringAutomaton.h"
#include "UndefinedBlockCommentAutomaton.h"
#include <cctype>
#include <iostream>

Lexer::Lexer() {
    CreateAutomata();
}

Lexer::~Lexer() {
    for (unsigned int i = 0; i < automata.size(); i++) { // Clear out automata vector. Do I need this->?
       delete automata[i];
    }
    for (unsigned int i = 0; i < tokens.size(); i++) {   // Clear our tokens vector created with constructor.
       delete tokens[i];
    }
}

void Lexer::CreateAutomata() {
//    automata.push_back(new ColonAutomaton());
//    automata.push_back(new ColonDashAutomaton());
    automata.push_back((new MatcherAutomaton(",", TokenType::COMMA)));
    automata.push_back((new MatcherAutomaton(".", TokenType::PERIOD)));
    automata.push_back((new MatcherAutomaton("?", TokenType::Q_MARK)));
    automata.push_back((new MatcherAutomaton("(", TokenType::LEFT_PAREN)));
    automata.push_back((new MatcherAutomaton(")", TokenType::RIGHT_PAREN)));
    automata.push_back((new MatcherAutomaton(":", TokenType::COLON)));
    automata.push_back((new MatcherAutomaton(":-", TokenType::COLON_DASH)));
    automata.push_back((new MatcherAutomaton("*", TokenType::MULTIPLY)));
    automata.push_back((new MatcherAutomaton("+", TokenType::ADD)));
    automata.push_back((new MatcherAutomaton("Schemes", TokenType::SCHEMES)));
    automata.push_back((new MatcherAutomaton("Facts", TokenType::FACTS)));
    automata.push_back((new MatcherAutomaton("Rules", TokenType::RULES)));
    automata.push_back((new MatcherAutomaton("Queries", TokenType::QUERIES)));
    automata.push_back(new IDAutomaton());   // Does the order of these matter?
    automata.push_back(new StringAutomaton());
    automata.push_back(new LineCommentAutomaton());
    automata.push_back(new BlockCommentAutomaton());
    automata.push_back(new UndefinedBlockCommentAutomaton());
    automata.push_back(new UndefinedStringAutomaton());





}

void Lexer::Run(std::string& input) {
//   cout << "Made it into Lexer function:" << endl;
   int lineNumber = 1;
   string stringCopy = input;



   // Reset maxRead?
   while (!stringCopy.empty()) {
//    cout << "While input stringCopy is not empty..." << endl;

      while (!stringCopy.empty() && isspace(stringCopy.at(0))) {        // While the next character is whitespace (handling whitespace)...
         if (stringCopy.at(0) == '\n') {                                // Accounting for newlines in whitespace?
            lineNumber++;
         }
//         cout << stringCopy.at(0);
         stringCopy.erase(0, 1);                                          // ...erase the whitespace
      }

      // Parallel part of algorithm:
      if(stringCopy.empty()) { break; }

      int maxRead = 0;                                // Keep track of max read
      Automaton* maxAutomaton = automata.at(0);    // Keep track of corresponding automaton^

      for (Automaton* automaton : automata) {  // For every single automaton...
         int inputRead = automaton->Start(stringCopy);      // ...feed input...
         if (inputRead > maxRead) {                         // ...compare inputRead to maxRead...
            maxRead = inputRead;                            // ...adjusting value if necessary
            maxAutomaton = automaton;
         }
      }
      // Max part of algorithm:
//      cout << "Max part of algorithm" << endl;
      if (maxAutomaton->GetEndOfFileBool() == true) {
         string tokenString = stringCopy.substr(0, maxRead);
         Token* newToken = new Token(TokenType::UNDEFINED, tokenString, lineNumber);
         lineNumber += maxAutomaton->NewLinesRead();        // Increment line number according to NewLinesRead in token
         tokens.push_back(newToken);
      }
      else if (maxRead > 0) {
         string tokenString = stringCopy.substr(0, maxRead);
         Token* newToken = maxAutomaton->CreateToken(tokenString, lineNumber);
         lineNumber += maxAutomaton->NewLinesRead();        // Increment line number according to NewLinesRead in token
         if (newToken->getTokenType() != TokenType::COMMENT) {
            tokens.push_back(newToken);                     // The parser does not deal with comments, so we do not add them.
         }

      }
      else {
         maxRead = 1;
         string tokenString = stringCopy.substr(0, maxRead);
         Token* newToken = new Token(TokenType::UNDEFINED, tokenString, lineNumber);
         tokens.push_back(newToken);
      }
      stringCopy.erase(0, maxRead);         // Update `input` by removing characters read to create Token (remove maxRead characters from input)

   }
//   cout << "Input string is now empty." << endl;
   // Add end of file token to all tokens:
   auto* eofToken = new Token(TokenType::END_OF_FILE, "", lineNumber);
   tokens.push_back(eofToken);
}

string Lexer::toString() {
   string returnString = "";
   for (unsigned int i = 0; i < tokens.size(); i++) {                 // Iterating through all the tokens...
      returnString += tokens.at(i)->toString() + "\n";                // Add each token in token vector to string with a newline
   }
   returnString += "Total Tokens = " + to_string(tokens.size());  // Addend the string with line indicating total # of tokens

   return returnString;                                               // Return the string
}

vector<Token*> Lexer::getTokenVector() {
   return tokens; // Returns vector of token pointers
}


