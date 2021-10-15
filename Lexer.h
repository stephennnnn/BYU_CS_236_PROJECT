#ifndef LEXER_H
#define LEXER_H
#include <vector>
#include "Automaton.h"
#include "Token.h"
using namespace std;

class Lexer
{
private:
    vector<Automaton*> automata;
    vector<Token*> tokens;
    void CreateAutomata(); // Inside function for constructor.

public:
    Lexer();
    ~Lexer();
    void Run(string& input);
    string toString();
    vector<Token*> getTokenVector();

};

#endif // LEXER_H

