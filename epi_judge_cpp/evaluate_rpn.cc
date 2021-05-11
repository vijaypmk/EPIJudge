#include <functional>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>

#include "test_framework/generic_test.h"
using std::function;
using std::stack;
using std::string;
using std::stringstream;
using std::unordered_map;

int Evaluate(const string& expression) {
  stack<int> m;
  stringstream ss(expression);
  const unordered_map<string, function<int(int, int)>> c = {
    {"+", [](int x, int y) {return x + y;}},
    {"*", [](int x, int y) {return x * y;}},
    {"-", [](int x, int y) {return x - y;}},
    {"/", [](int x, int y) {return x / y;}}
  };

  string token;
  const char d = ',';
  while(getline(ss, token, d)) {
    if(c.count(token)) {
      int a = m.top();
      m.pop();
      int b = m.top();
      m.pop();
      m.emplace(c.at(token)(b, a));
    }
    else {
      m.emplace(stoi(token));
    }
  }
  
  return m.top();
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"expression"};
  return GenericTestMain(args, "evaluate_rpn.cc", "evaluate_rpn.tsv", &Evaluate,
                         DefaultComparator{}, param_names);
}
