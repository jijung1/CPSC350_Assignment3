/*
Name:                   Jin Jung
Student ID:             2329401
Email:                  jijung@chapman.edu
Course no. & Section:   CS350-02
Assignment:             3
*/

#ifndef GENSTACK_H
#define GENSTACK_H

/*
  Array based Generic Stack implementation 
*/

#include <iostream>
#include <stdexcept>
#include <exception>
#include <algorithm> //copy(InputIterator first, InputIterator last, OutputIterator result)
#include <fstream>
#include <string>

using namespace std;

template <typename E>
class GenStack {
private:
  E* stack;
  int top;
  int capacity;

public:
  GenStack();
  GenStack(int capacity);
  ~GenStack();
  void push(const E& e);
  E pop();// throws StackEmpty();
  const E& peek();  //return value at top without modifying element
  bool empty();
  bool full();
  int size();
};
class StackEmpty : public runtime_error {
public:
  StackEmpty(const string& err) : runtime_error(err) {};
};

template <typename E>
int GenStack<E>::size() {
  return top+1;
}

template <typename E>
bool GenStack<E>::full() {  //not used any longer since capacity of stack is automatically increased
  return (top == capacity-1);
}

template <typename E>
bool GenStack<E>::empty() {
  return top == -1;
}

template <typename E>
GenStack<E>::GenStack() : stack(new E[100]), top(-1), capacity(100) {}
template <typename E>
GenStack<E>::GenStack(int capacity) : stack(new E[capacity]), top(-1), capacity(capacity) {}
template <typename E>
void GenStack<E>::push(const E& e) {
  //if not full
  if (top == capacity-1) {  //check if capacity needs to be increased
    capacity *= 2;
    E* newStack = new E[capacity];
    copy(stack, stack+(capacity/2), newStack);
    stack = newStack;
  }
  stack[++top] = e;
}

template <typename E>
GenStack<E>::~GenStack() {
  delete[] stack;
}

template <typename E>
E GenStack<E>::pop() {
if (top == -1) {
  throw StackEmpty("pop() from empty stack!\n");
}
return (stack[top--]);

}
template <typename E>
const E& GenStack<E>::peek() {
  //if not empty
  return (stack[top]);
}

#endif /*GENSTACK_H*/
