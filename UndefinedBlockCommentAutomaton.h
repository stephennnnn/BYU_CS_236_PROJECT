#ifndef PROJECT1_STARTER_CODE_UNDEFINEDBLOCKCOMMENTAUTOMATON_H
#define PROJECT1_STARTER_CODE_UNDEFINEDBLOCKCOMMENTAUTOMATON_H

#include "Automaton.h"
using namespace std;


class UndefinedBlockCommentAutomaton : public Automaton {
private:
   void S1(const string& input);

   void S2(const string& input);

   void S3(const string& input);

public:
   UndefinedBlockCommentAutomaton() : Automaton(TokenType::UNDEFINED) {}

   void S0(const string& input);
};


#endif //PROJECT1_STARTER_CODE_UNDEFINEDBLOCKCOMMENTAUTOMATON_H
