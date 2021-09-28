#include "MatcherAutomaton.h"

void MatcherAutomaton::S0(const std::string& input) { // Change function type from int to void (to match inheritance from Automaton).?
    bool isMatch = true;
    inputRead = 0;  // member variable inherited from Automaton class
    for (int i = 0; i < (int)toMatch.size() && isMatch; i++) {
        if (input.at(i) != toMatch[i]) {
            isMatch = false;
        } }
    if (isMatch) {
        inputRead = toMatch.size();
    }
    //Added my own code here:
    else {
       Serr(); // inputRead = 0;
    }
}

MatcherAutomaton::MatcherAutomaton(std::string toMatch, TokenType tokenType) : Automaton(tokenType){
   this->toMatch = toMatch;
}
