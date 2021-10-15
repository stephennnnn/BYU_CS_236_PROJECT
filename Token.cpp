#include "Token.h"

Token::Token(TokenType type, string description, int line) {
    this->type = type;
    this->description = description;
    this->line = line;
}

string Token::toString() {
   // Convert to string representation of type:
   string typeString = "";
   switch (type) {
      case TokenType::COMMA:
         typeString = "COMMA";
         break;
      case TokenType::PERIOD:
         typeString = "PERIOD";
         break;
      case TokenType::Q_MARK:
         typeString = "Q_MARK";
         break;
      case TokenType::LEFT_PAREN:
         typeString = "LEFT_PAREN";
         break;
      case TokenType::RIGHT_PAREN:
         typeString = "RIGHT_PAREN";
         break;
      case TokenType::COLON:
         typeString = "COLON";
         break;
      case TokenType::COLON_DASH:
         typeString = "COLON_DASH";
         break;
      case TokenType::MULTIPLY:
         typeString = "MULTIPLY";
         break;
      case TokenType::ADD:
         typeString = "ADD";
         break;
      case TokenType::SCHEMES:
         typeString = "SCHEMES";
         break;
      case TokenType::FACTS:
         typeString = "FACTS";
         break;
      case TokenType::RULES:
         typeString = "RULES";
         break;
      case TokenType::QUERIES:
         typeString = "QUERIES";
         break;
      case TokenType::ID:
         typeString = "ID";
         break;
      case TokenType::STRING:
         typeString = "STRING";
         break;
      case TokenType::COMMENT:
         typeString = "COMMENT";
         break;
      case TokenType::UNDEFINED:
         typeString = "UNDEFINED";
         break;
      case TokenType::END_OF_FILE:
         typeString = "EOF";
         break;
      default:
         break;   // If nothing, just break.
   }
   // Return formatted string:
   return "(" + typeString + ",\"" + this->description + "\"," + to_string(this->line) + ")";
}

TokenType Token::getTokenType() {
   return type;
}

string Token::getTokenDescription() {
   return description;
}
int Token::getTokenLine(){
   return line;
}