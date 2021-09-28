#ifndef PROJECT1_STARTER_CODE_STRINGAUTOMATON_H
#define PROJECT1_STARTER_CODE_STRINGAUTOMATON_H

#include "Automaton.h"
using namespace std;

class StringAutomaton : public Automaton {
private:
   void S1(const string& input);

   void S2(const string& input);

public:
   StringAutomaton() : Automaton(TokenType::STRING) {}   // Call the base constructor

   void S0(const string& input);

};

#endif //PROJECT1_STARTER_CODE_STRINGAUTOMATON_H
