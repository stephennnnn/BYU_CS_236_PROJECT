#ifndef TOKEN_H
#define TOKEN_H
#include <string>
using namespace std;

enum class TokenType {
   COMMA,
   PERIOD,
   Q_MARK,
   LEFT_PAREN,
   RIGHT_PAREN,
   COLON,
   COLON_DASH,
   MULTIPLY,
   ADD,
   SCHEMES,
   FACTS,
   RULES,
   QUERIES,
   ID,
   STRING,
   COMMENT,
   UNDEFINED,
   END_OF_FILE
};

class Token
{
private:
    TokenType type;
    string description;
    int line;

public:
   Token(TokenType type, string description, int line);
   string toString();
   TokenType getTokenType();
   string getTokenDescription();
   int getTokenLine();
};

#endif // TOKEN_H


