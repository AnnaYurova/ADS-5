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
    case ' ': return 5;
    default: return 4;
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
  std::string out;
  char space = ' ';
  for (int i = 0; i < inf.size(); i++) {
    if (prior(inf[i]) == 5) {
        out.push_back(inf[i]);
        out.push_back(space);
    } else {
      if (prior(inf[i]) == 0) {
      stack11.push(inf[i]);
    } else if (prior(inf[i]) > prior(stack11.get())) {
        stack11.push(inf[i]);
    } else if (stack11.isEmpty()) {
      stack11.push(inf[i]);
    } else if (prior(inf[i]) == 1) {
        while (prior(stack11.get()) != 0) {
          out.push_back(stack11.get());
          out.push_back(space);
          stack11.pop();
        }
        stack11.pop();
      } else {
        while (!stack11.isEmpty() && (prior(inf[i]) <= prior(stack11.get()))) {
          out.push_back(stack11.get());
          out.push_back(space);
          stack11.pop();
        }
        stack11.push(inf[i]);
      }
    }
  }
    while (!stack11.isEmpty()) {
      out.push_back(stack11.get());
      out.push_back(space);
      stack11.pop();
    }
    for (int i = 0; i < out.size(); i++) {
      if (out[out.size() - 1] == ' ')
        out.erase(out.size() - 1);
    }
    return out;
}

int eval(std::string pref) {
  int end = 0;
  for (int i = 0; i< pref.size(); i++) {
    if (prior(pref[i]) == 4) {
      stack22.push(pref[i] - '0');
    } else if (prior(pref[i]) < 4) {
        int x = stack22.get();
        stack22.pop();
        int y = stack22.get();
        stack22.pop();
        stack22.push(NCal(pref[i], x, y));
    }
  }
  end = stack22.get();
  return end;
}

