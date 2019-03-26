/*
Name:                   Jin Jung
Student ID:             2329401
Email:                  jijung@chapman.edu
Course no. & Section:   CS350-02
Assignment:             3
*/

/*
  Driver file to test the Syntax Checker program
*/

#include "GenStack.h"
#include "SyntaxChecker.h"

using namespace std;

string toUpperCase(string someString); //FUNction to turn string toUpperCase

int main(int argc, char** argv) {
  if(argc > 1 && argc < 3) {  //check for valid number of terminial inputs
    string filelocation = argv[1];
    ifstream istream(filelocation);
    if(istream.is_open()) { //check if file exists
      istream.close();
      SyntaxChecker test(filelocation);
      test.runSyntaxCheck();
      bool repeat = false;
      string yesno = "";
      cout << "Syntax check finished with no errors found. Run again? (y/n) : ";
      cin >> yesno;
      if (cin.fail()) {
        cout << "Invalid input!\n";
        cin.clear();
        cin.ignore();
        exit(1);
      }
      if (toUpperCase(yesno) == "YES" || toUpperCase(yesno) == "Y") {
        repeat = true;
      }
      while (repeat) {
        string newFilePath = "";
        repeat = false;
        cout << "Please enter new file path: \n";
        cin >> newFilePath;
        if (cin.fail())
        {
          cout << "Invalid input!\n";
          cin.clear();
          cin.ignore();
          exit(1);
        }
        ifstream istream2(newFilePath);
        if(istream2.is_open()) { //check if file exists
          istream2.close();
          SyntaxChecker test(newFilePath);
          test.runSyntaxCheck();
        cout << "Syntax check finished with no errors found. Run again? (y/n) : ";
        cin >> yesno;
        if (cin.fail())
        {
          cout << "Invalid input!\n";
          cin.clear();
          cin.ignore();
          exit(1);
        }
        if (toUpperCase(yesno) == "YES" || toUpperCase(yesno) == "Y") {
          repeat = true;
        }
      }
      else {
        cout << "Invalid filePath!\nExiting..\n";
        return 0;
      }
    }
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

string toUpperCase(string someString)
{
  for(int i = 0; i < someString.length(); ++i)
  {
    if (static_cast<int>(someString[i]) > 96 && static_cast<int>(someString[i]) < 123)
    {
      someString[i] = static_cast<char>(static_cast<int>(someString[i])-32);
    }
  }
  return someString;
}
