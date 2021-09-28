cmake_minimum_required(VERSION 3.16)
project(Project1_Starter_Code)

set(CMAKE_CXX_STANDARD 14)

add_executable(Project2 Token.h Token.cpp Lexer.h Lexer.cpp MatcherAutomaton.h MatcherAutomaton.cpp ColonAutomaton.h ColonAutomaton.cpp ColonDashAutomaton.h ColonDashAutomaton.cpp IDAutomaton.h IDAutomaton.cpp StringAutomaton.h StringAutomaton.cpp LineCommentAutomaton.h LineCommentAutomaton.cpp BlockCommentAutomaton.h BlockCommentAutomaton.cpp UndefinedStringAutomaton.h UndefinedStringAutomaton.cpp UndefinedBlockCommentAutomaton.h UndefinedBlockCommentAutomaton.cpp main.cpp)