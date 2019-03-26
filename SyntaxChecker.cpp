/*
Name:                   Jin Jung
Student ID:             2329401
Email:                  jijung@chapman.edu
Course no. & Section:   CS350-02
Assignment:             3
*/

/*
  .cpp file implementation of SyntaxChecker program. Program takes in user supplied file path from terminal and performs syntax check.
*/
#include "SyntaxChecker.h"

using namespace std;

class SyntaxException { //custom exception for Syntax error and graceful exit of program.
private:
  string errorMsg;
public:
  SyntaxException(const string& err) { errorMsg = err; }
  string getMessage() const { return errorMsg; }
};

SyntaxChecker::SyntaxChecker() {  //default constructor
  temp = "";
  beginMultilineComment = false;
  filePath = "";
  lineNumber = 1;
  quotationMarkCount = 0;
  multilineCommentCount = 0;
  apostropheCount = 0;
}
SyntaxChecker::SyntaxChecker(string filePath) { //main constructor
  temp = "";
  beginMultilineComment = false;
  this->filePath = filePath;
  lineNumber = 1;
  quotationMarkCount = 0;
  multilineCommentCount = 0;
  apostropheCount = 0;
}
SyntaxChecker::~SyntaxChecker() {}  //destructor

bool SyntaxChecker::isValid() { //check for valid part of file to be read
  if (quotationMarkCount % 2 != 0 || apostropheCount % 2 != 0 || multilineCommentCount % 2 != 0) {
    return false;
  }
  return (!beginMultilineComment);
}


void SyntaxChecker::runSyntaxCheck() {  //main function that reads file for syntax errors
  GenStack<char> delimitersGoHere(100); //instantiate a stack of size 100
  ifstream istream(filePath);
  try {
    while (!istream.eof()) { //while end of file has not been reached
      getline(istream,temp);
      if (temp.back() == '\r') {  //remove return carriage character from string temp
      temp.pop_back();
      }
      if(temp.length() <= 0) {  //skip empty line
        lineNumber++;
        continue;
      }
      for (int i = 0; i < temp.length(); ++i) { //otherwise read each line and search for delimiters
        if(temp[i] == static_cast<char>(39) && quotationMarkCount%2 == 0 && beginMultilineComment == false) { //if temp[i] is an apostrophe and is valid part of file to be read
          apostropheCount++;
        }
        if(temp[i] == '"' && apostropheCount % 2 == 0 && beginMultilineComment == false) { //if temp[i] is a quotation mark and is valid part of file to be read
          quotationMarkCount++;
        }
        if(temp[i]=='/' && temp[i+1] == '*') {  //check for begin of multiline comment
          beginMultilineComment = true;
        }
        if(temp[i] == '*' && temp[i+1] == '/') { //check for end of multiline comment
          beginMultilineComment = false;
        }
        if(temp[i] == '/' && temp[i+1] == '/') {  //if single line comment, skip rest of line
          break;
        }
        if (isValid()) {
          if(temp[i] == '{' || temp[i] == '[' || temp[i] == '(') {  //push opening delimiters into stack
            delimitersGoHere.push(temp[i]);
          }
          else if(temp[i] == '}') {
            if(delimitersGoHere.empty()) {
              string message = "Line " + to_string(lineNumber) + ": missing matching { ";
              throw SyntaxException(message);
            }
            char temp2 = delimitersGoHere.pop();
            if(temp2 != '{') {
              string message = "Line " + to_string(lineNumber) + ": expected { and found " + temp2;
              throw SyntaxException(message);
            }
          }
          else if(temp[i] == ']') {
            if(delimitersGoHere.empty()) {
              string message = "Line " + to_string(lineNumber) + ": missing matching [ ";
              throw SyntaxException(message);
            }
            char temp2 = delimitersGoHere.pop();
            if(temp2 != '[') {
              string message = "Line " + to_string(lineNumber) + ": expected [ and found " + temp2;
              throw SyntaxException(message);
            }
          }
          else if(temp[i] == ')') {
            if(delimitersGoHere.empty()) {
              string message = "Line " + to_string(lineNumber) + ": missing matching ( ";
              throw SyntaxException(message);
            }
            char temp2 = delimitersGoHere.pop();
            if(temp2 != '(') {
              string message = "Line " + to_string(lineNumber) + ": expected ( and found " + temp2;
              throw SyntaxException(message);
            }
          }
        }
      }
      lineNumber++;
    }
    if (delimitersGoHere.size() > 0) {  //if stack is not empty after reaching eof, there is an extra opening delimiter
      char what = delimitersGoHere.pop();
      string msg = "Reached end of file: missing complement of ";
      msg += what;
      msg += "\n";
      throw SyntaxException(msg);
    }
    istream.close();  //close file stream
  }
  catch(SyntaxException e) {  //catch exception with specific message and exit program
    cout << e.getMessage();
    exit(1);
  }
}
