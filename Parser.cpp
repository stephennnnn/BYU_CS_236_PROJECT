#include "Parser.h"

Parser::Parser(vector<Token*> v) {
   tokenVector = v;
}
Parser::~Parser() {
   for (auto & i : tokenVector) {
      delete i;
   }
   cout << "parser deconstruct successful" << endl;
}
void Parser::parse() {  // datalog program function. The other functions will closely resemble this.

    // datalogProgram	->	SCHEMES COLON scheme schemeList FACTS COLON factList RULES COLON ruleList QUERIES COLON query queryList EOF
    match(TokenType::SCHEMES);
    match(TokenType::COLON);
    scheme();
    schemeList();

    match(TokenType::FACTS);
    match(TokenType::COLON);
    factList();

    match(TokenType::RULES);
    match(TokenType::COLON);
    ruleList();

    match(TokenType::QUERIES);
    match(TokenType::COLON);
    query();
    queryList();

//    cout << "Success!" << endl;
}

void Parser::match(TokenType type) {
   if (tokenVector.at(index)->getTokenType() == type) {
      index++;
   }
   else {
      throw tokenVector.at(index);
   }
}
void Parser::schemeList(){         // schemeList	->	scheme schemeList | lambda
   if (tokenVector.at(index)->getTokenType() == TokenType::ID) {
      scheme();
      schemeList();
   }
   // else {lambda}
}
void Parser::factList(){           // factList	->	fact factList | lambda
   if (tokenVector.at(index)->getTokenType() == TokenType::ID) {
      fact();
      factList();
   }
   // lambda
}
void Parser::ruleList(){           // ruleList	->	rule ruleList | lambda
   if (tokenVector.at(index)->getTokenType() == TokenType::ID) {
      rule();
      ruleList();
   }
   // lambda
}
void Parser::queryList(){          // queryList	->	query queryList | lambda
   if (tokenVector.at(index)->getTokenType() == TokenType::ID) {
      query();
      queryList();
   }
   // lambda
}
void Parser::scheme(){             // scheme   	-> 	ID LEFT_PAREN ID idList RIGHT_PAREN
   match(TokenType::ID);
   string id = tokenVector.at(index - 1)->getTokenDescription();
   match(TokenType::LEFT_PAREN);
   match(TokenType::ID);
   vector<Parameter*> paramList;
   paramList.push_back(new Parameter(tokenVector.at(index - 1)->getTokenDescription()));
   idList(paramList);
   match(TokenType::RIGHT_PAREN);
   Predicate schemePredicate;
   schemePredicate.setID(id);
   schemePredicate.setParameterList(paramList);
   dlp.addScheme(schemePredicate);
}
void Parser::fact(){               // fact    	->	ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD
   match(TokenType::ID);
   string id = tokenVector.at(index - 1)->getTokenDescription();
   match(TokenType::LEFT_PAREN);
   match(TokenType::STRING);
   vector<Parameter*> paramList;
   paramList.push_back(new Parameter(tokenVector.at(index - 1)->getTokenDescription()));
   dlp.addDomain(tokenVector.at(index - 1)->getTokenDescription());     // Add to domain (also in stringList)
   stringList(paramList);
   match(TokenType::RIGHT_PAREN);
   match(TokenType::PERIOD);
   Predicate factPredicate;
   factPredicate.setID(id);
   factPredicate.setParameterList(paramList);
   dlp.addFact(factPredicate);
}
void Parser::rule(){               // rule    	->	headPredicate COLON_DASH predicate predicateList PERIOD
   Predicate headPred;
   headPredicate(headPred);
   match(TokenType::COLON_DASH);
   Predicate body1;
   predicate(body1);
   vector<Predicate> bodyPredicates;
   bodyPredicates.push_back(body1);
   predicateList(bodyPredicates);
   match(TokenType::PERIOD);
   Rule rule;
   rule.setHeadPredicate(headPred);
   rule.setBodyPredicates(bodyPredicates);
   dlp.addRule(rule);
}
void Parser::query(){              // query	        ->      predicate Q_MARK
   Predicate pred;
   predicate(pred);
   match(TokenType::Q_MARK);
   dlp.addQuery(pred);
}
void Parser::headPredicate(Predicate &headPred){      // headPredicate	->	ID LEFT_PAREN ID idList RIGHT_PAREN
   if (tokenVector.at(index)->getTokenType() == TokenType::ID) {
      match(TokenType::ID);
      string id = tokenVector.at(index - 1)->getTokenDescription();
      match(TokenType::LEFT_PAREN);
      match(TokenType::ID);
      vector<Parameter*> paramList;
      paramList.push_back(new Parameter(tokenVector.at(index - 1)->getTokenDescription()));
      idList(paramList);
      match(TokenType::RIGHT_PAREN);
      headPred.setID(id);
      headPred.setParameterList(paramList);
   }
}
void Parser::predicate(Predicate &pred){          // predicate	->	ID LEFT_PAREN parameter parameterList RIGHT_PAREN
   if (tokenVector.at(index)->getTokenType() == TokenType::ID) {
      match(TokenType::ID);
      string id = tokenVector.at(index - 1)->getTokenDescription();
      match(TokenType::LEFT_PAREN);
      vector<Parameter*> paramList;
      parameter();
      paramList.push_back(new Parameter(tokenVector.at(index - 1)->getTokenDescription()));
      parameterList(paramList);
      match(TokenType::RIGHT_PAREN);
      pred.setID(id);
      pred.setParameterList(paramList);
   }
}
void Parser::predicateList(vector<Predicate> &bodyPredicates){      // predicateList	->	COMMA predicate predicateList | lambda
   if (tokenVector.at(index)->getTokenType() == TokenType::COMMA) {
      match(TokenType::COMMA);
      Predicate pred;
      predicate(pred);
      bodyPredicates.push_back(pred);
      predicateList(bodyPredicates);
   }
}
void Parser::parameterList(vector<Parameter*> &paramList){      // parameterList	-> 	COMMA parameter parameterList | lambda
   if (tokenVector.at(index)->getTokenType() == TokenType::COMMA) {
      match(TokenType::COMMA);
      parameter();
      paramList.push_back(new Parameter(tokenVector.at(index - 1)->getTokenDescription()));
      parameterList(paramList);
   }
}
void Parser::stringList(vector<Parameter*> &paramList){         // stringList	-> 	COMMA STRING stringList | lambda
   if (tokenVector.at(index)->getTokenType() == TokenType::COMMA) {
      match(TokenType::COMMA);
      match(TokenType::STRING);
      paramList.push_back(new Parameter(tokenVector.at(index - 1)->getTokenDescription()));
      dlp.addDomain(tokenVector.at(index - 1)->getTokenDescription());     // Add to domain
      stringList(paramList);
   }
}
void Parser::idList(vector<Parameter*> &paramList){             // idList  	-> 	COMMA ID idList | lambda
  // vector
   if (tokenVector.at(index)->getTokenType() == TokenType::COMMA) {
      match(TokenType::COMMA);
      match(TokenType::ID);
      paramList.push_back(new Parameter(tokenVector.at(index - 1)->getTokenDescription()));
      idList(paramList);
   }
}
void Parser::parameter(){          // parameter	->	STRING | ID
    if (tokenVector.at(index)->getTokenType() == TokenType::STRING) {
       match(TokenType::STRING);
    }
    else {
       match(TokenType::ID);
    }
}
DatalogProgram Parser::getDlp() {
   return dlp;
}


