/*
Name:                   Jin Jung
Student ID:             2329401
Email:                  jijung@chapman.edu
Course no. & Section:   CS350-02
Assignment:             3
*/
#ifndef SYNTAXCHECKER_H
#define SYNTAXCHECKER_H

#include "GenStack.h"
#include <iostream>
#include <stdexcept>
#include <exception>
#include <algorithm> //copy(InputIterator first, InputIterator last, OutputIterator result)
#include <fstream>
#include <string>

using namespace std;

class SyntaxChecker {
public:
  SyntaxChecker();
  SyntaxChecker(string filePath);
  ~SyntaxChecker();
  bool isValid();
  void runSyntaxCheck();

private:
  string temp;
  bool beginMultilineComment;
  string filePath;
  int lineNumber;
  int quotationMarkCount;
  int multilineCommentCount;
  int apostropheCount;

};


#endif /*SYNTAXCHECKER_H*/
