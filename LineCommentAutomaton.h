#ifndef PROJECT1_STARTER_CODE_LINECOMMENTAUTOMATON_H
#define PROJECT1_STARTER_CODE_LINECOMMENTAUTOMATON_H

#include "Automaton.h"
using namespace std;

class LineCommentAutomaton : public Automaton {
private:
   void S1(const string& input);

public:
   LineCommentAutomaton() : Automaton(TokenType::COMMENT) {}

   void S0(const string& input);

};

#endif //PROJECT1_STARTER_CODE_LINECOMMENTAUTOMATON_H
