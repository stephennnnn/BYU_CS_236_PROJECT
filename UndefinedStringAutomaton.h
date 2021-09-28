#ifndef PROJECT1_STARTER_CODE_UNDEFINEDSTRINGAUTOMATON_H
#define PROJECT1_STARTER_CODE_UNDEFINEDSTRINGAUTOMATON_H

#include "Automaton.h"
using namespace std;

class UndefinedStringAutomaton : public Automaton {
private:
   void S1(const string& input);

   void S2(const string& input);

public:
   UndefinedStringAutomaton() : Automaton(TokenType::UNDEFINED) {}

   void S0(const string& input);
};


#endif //PROJECT1_STARTER_CODE_UNDEFINEDSTRINGAUTOMATON_H
