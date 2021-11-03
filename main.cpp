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
      parser->parse();                          // Success
//      parser->getDlp().toString();
   }
   catch (Token* token) {
//      cout << "Failure!" << endl << "  ";       // Failure State
//      cout << token->toString() << endl;
   }

//   // Test:
//   cout << "========== End of project 2 ==========" << endl << endl << endl << endl;

   //----------------------------------------------------------------------------------
   // ------------------------------------Project 3------------------------------------

   // DatalogProgram created as "dlp"
   // Read schemes, facts, queries from dlp into interpreter.
   // Create the Database with schemes (headers) and facts (tuples) --> relations, then run queries/operations (interpreter) on relations


   Interpreter *interpreter = new Interpreter(parser->getDlp());
   interpreter->run();

   // interpreter->getDb().toString();

   // Something.toString();   // is this my Database that is going toString? Query results?

   //----------------------------------------------------------------------------------
   delete lexer;
//   delete parser;    // When implemented, process finished with exit code -1073741819 (0xC0000005)
   return 0;
}
