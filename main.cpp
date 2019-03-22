/*
Name:                   Jin Jung
Student ID:             2329401
Email:                  jijung@chapman.edu
Course no. & Section:   CS350-02
Assignment:             1
*/

/*
  Driver file
*/

#include "GenStack.h"

class SyntaxException {
private:
  string errorMsg;
public:
  SyntaxException(const string& err) { errorMsg = err; }
  string getMessage() const { return errorMsg; }
};

void runSyntaxCheck(string filelocation);

int main(int argc, char** argv) {
  /*
    automatically call runSyntaxCheck(string filePath) to check for '(' ')' '{' '}' '[' ']'
    within runSyntaxCheck(string filePath) {
    verify existence of filePath, fnf message and exit
    open file stream, readin each line, increment line#, iterate through each index of string and push opening delimiters into stack
    after each closing delimiter, pop() and  If stack is empty and no matching delimiter,
    reach end of file: missing }. else syntax error in line#.

    //only push delimiters when bool isComment is false (check for comment delimiters) ' " '

  }

    To do:
    update readme
    add comments

  */

  if(argc > 1 && argc < 3) {  //check for valid number of terminial inputs
    string filelocation = argv[1];
    ifstream istream(filelocation);
    if(istream.is_open()) { //check if file exists
      istream.close();
      runSyntaxCheck(filelocation);
    }
    else {
      cout << "Invalid filePath!\nExiting..\n";
      return 0;
    }
  }
  else {
    cout << "Invalid terminal arguments\nPlease use format: ./[executable] [filelocation]\n";
    return 0;
  }
}

void runSyntaxCheck(string filelocation) {
  ifstream istream(filelocation);
  //if int apostroph % 2 != 0 || int quotation % 2 != 0, disregard
  GenStack<char> delimitersGoHere(100);
  string temp = "";
  int linenumber = 1;
  try {
    while (!istream.eof()) { //while end of file has not been reached
      getline(istream,temp);
      if (temp.back() == '\r') {  //remove return carriage character from string temp
      temp.pop_back();
      }
      if(temp.length() <= 0) {  //skip empty line
        linenumber++;
        continue;
      }

      for (int i = 0; i < temp.length(); ++i) { //otherwise read each line and search for delimiters
        if(temp[i] == '{' || temp[i] == '[' || temp[i] == '(') {
          delimitersGoHere.push(temp[i]);
        }
        else if(temp[i] == '}') {
          if(delimitersGoHere.empty()) {
            string message = "Line " + to_string(linenumber) + ": missing matching { ";
            throw SyntaxException(message);
          }
          char temp2 = delimitersGoHere.pop();
          if(temp2 != '{') {
            string message = "Line " + to_string(linenumber) + ": expected { and found " + temp2;
            throw SyntaxException(message);
          }
        }
        else if(temp[i] == ']') {
          if(delimitersGoHere.empty()) {
            string message = "Line " + to_string(linenumber) + ": missing matching [ ";
            throw SyntaxException(message);
          }
          char temp2 = delimitersGoHere.pop();
          if(temp2 != '[') {
            string message = "Line " + to_string(linenumber) + ": expected [ and found " + temp2;
            throw SyntaxException(message);
          }
        }
        else if(temp[i] == ')') {
          if(delimitersGoHere.empty()) {
            string message = "Line " + to_string(linenumber) + ": missing matching ( ";
            throw SyntaxException(message);
          }
          char temp2 = delimitersGoHere.pop();
          if(temp2 != '(') {
            string message = "Line " + to_string(linenumber) + ": expected ( and found " + temp2;
            throw SyntaxException(message);
          }
        }
      }
      linenumber++;
    }
    istream.close();
    if (delimitersGoHere.size() > 0) {
      throw SyntaxException("Reached end of file: missing }");
    }
    cout << "Delimiter Syntax is correct. Analyze another file? (Y/N): ";
  }
  catch(SyntaxException e) {
    cout << e.getMessage();
    exit(1);
  }
}
