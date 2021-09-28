#ifndef PROJECT1_STARTER_CODE_IDAUTOMATON_H
#define PROJECT1_STARTER_CODE_IDAUTOMATON_H

#include "Automaton.h"
using namespace std;

class IDAutomaton : public Automaton {
private:
   void S1(const string& input);
public:
   IDAutomaton() : Automaton(TokenType::ID) {} // Call the base constructor

   void S0(const string& input);
};


#endif //PROJECT1_STARTER_CODE_IDAUTOMATON_H
