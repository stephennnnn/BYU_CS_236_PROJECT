#include <iostream>
#include <fstream>
#include <sstream>
#include "Lexer.h"
#include "Parser.h"
#include "DatalogProgram.h"
#include "Interpreter.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {

   //----------------------------------------------------------------------------------
   // ------------------------------------Project 1------------------------------------
   // 1. Reading the file in main:
   string fileName = argv[1];       // Reading argument
   ifstream filestream;             // Creating filestream
   filestream.open(fileName);       // Opening input into filestream

   // 2. Turn input file into string:
   stringstream ss;                 // Creating string stream
   ss << filestream.rdbuf();        // Reading filestream into string stream
   string inputString = ss.str();   // Creating string out of string stream

   // 3. Call run on lexer and pass above string:
   auto* lexer = new Lexer();
   lexer->Run(inputString);

   //----------------------------------------------------------------------------------
   // ------------------------------------Project 2------------------------------------

   // Create parser and call parse on lexer output (token vector)
   vector<Token*> tokenVectorCopy = lexer->getTokenVector();
   Parser *parser = new Parser(tokenVectorCopy);
   try {
      parser->parse();                            // Success
//      parser->getDlp().toString();
   }
   catch (Token* token) {
//      cout << "Failure!" << endl << "  ";       // Failure State
//      cout << token->toString() << endl;
   }


   //----------------------------------------------------------------------------------
   // ------------------------------------Project 3------------------------------------

//   The functions this code accesses have been changed:
//   Interpreter *interpreter = new Interpreter(parser->getDlp());
//   interpreter->run();

   //----------------------------------------------------------------------------------
   // ------------------------------------Project 4------------------------------------

   Interpreter *interpreter = new Interpreter(parser->getDlp());
   interpreter->run();

   //----------------------------------------------------------------------------------
   // ------------------------------------Project 5------------------------------------

   delete lexer;
//   delete parser;    // When implemented, process finished with exit code -1073741819 (0xC0000005)
//   delete interpreter;
   return 0;
}
