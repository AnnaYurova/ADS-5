// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int prior(char pr) {
  switch (pr) {
    case '(': return 0;
    case ')': return 1;
    case '+': return 2;
    case '-': return 2;
    case '*': return 3;
    case '/': return 3;
    case ' ': return 4;
    default: return 5;
  }
}

int NCal(char pr, int x, int y) {
  switch (pr) {
    case '+': return (x + y);
    case '-': return (x - y);
    case '*': return (x * y);
    case '/':
      if (y != 0)
        return x / y;
    default: return 0;
  }
}

std::string infx2pstfx(std::string inf) {
  TStack <char, 100> stack1;
  std::string out;
  for (size_t i = 0; i < inf.size(); ++i) {
    if (prior(inf[i]) == 5) {
        out.push_back(' ');
        out.push_back(inf[i]);
    } else if (prior(inf[i]) == 0) {
      stack1.push(inf[i]);
    } else if (prior(inf[i]) > prior(stack1.get())) {
        stack1.push(inf[i]);
    } else if (stack1.isEmpty()) {
      stack1.push(inf[i]);
    } else {
      if (prior(inf[i]) == 1) {
        while (prior(stack1.get()) != 0) {
          out.push_back(' ');
          out.push_back(stack1.get());
          stack1.pop();
        }
        stack1.pop();
      } else {
        while (!stack1.isEmpty() && prior(inf[i]) <= prior(stack1.get())) {
          out.push_back(' ');
          out.push_back(stack1.get());
          stack1.pop();
        }
        stack1.push(inf[i]);
      }
    }
  }
    while (!stack1.isEmpty()) {
      out.push_back(' ');
      out.push_back(stack1.get());
      stack1.pop();
    }
    for (int i = 0; i < out.size(); i++) {
      if (out[out.size() - 1] == ' ')
        out.erase(out.size() - 1);
    }
    return out;
    return std::string("");
}

int eval(std::string pref) {
  int end = 0;
  for (int i = 0; i< pref.size(); i++) {
    if (prior(pref[i]) == 5) {
      stack2.push(pref[i] - '0');
    } else if (prior(pref[i]) < 5) {
        int x = stack2.get();
        stack2.pop();
        int y = stack2.get();
        stack2.pop();
        stack2.push(NCal(pref[i], x, y));
    }
  }
  end = stack2.get();
  return end;
}

