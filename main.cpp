#include <iostream>     // cout
#include <fstream>      // ifstream
#include <sstream>      // ss
#include "Lexer.h"
using namespace std;

int main(int argc, char* argv[]) {

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
   cout << lexer->toString();

   delete lexer;

   return 0;
}
