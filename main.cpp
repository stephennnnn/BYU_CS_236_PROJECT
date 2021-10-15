#include <iostream>     // cout
#include <fstream>      // ifstream
#include <sstream>      // ss
#include "Lexer.h"
#include "Parser.h"
#include "DatalogProgram.h"
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
   // End of project 1 (minus printing output)

   //----------------------------------------------------------------------------------
   // ------------------------------------Project 2------------------------------------

   // Create parser and call parse on lexer output (token vector)
   auto* parser = new Parser();
   try {
      parser->parse(lexer->getTokenVector());   // Success
      parser->getDlp().toString();
   }
   catch (Token* token) {
      cout << "Failure!" << endl << "  ";       // Failure
      cout << token->toString() << endl;
   }


   //----------------------------------------------------------------------------------
   // ------------------------------------Project 3------------------------------------

   delete lexer;
//   delete parser;    // Process finished with exit code -1073741819 (0xC0000005)

   return 0;
}
