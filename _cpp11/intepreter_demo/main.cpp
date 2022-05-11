#include <map>
#include <sstream>
#include <iostream>

using namespace std;

struct Cal {
    enum Op {Add, Sub} op;
    bool caled {false};
    int left_val{-1};
    int right_val{-1};
    int result = 0;
    Cal() {};
    Cal(int left, int right, Cal::Op op_): left_val{left}, right_val{right}, op{op_} {}
    
    int eval() {
        int result {0};
        switch(op) {
            case Cal::Op::Add:
                cout << "left_val: " << left_val << " ";
                cout << "right_val: " << right_val << " ";
                cout << "old result: " << result << endl;

                result = left_val + right_val;
                cout << "new result: " << result << endl;
                break;
            case Cal::Op::Sub:
                cout << "left_val: " << left_val << " ";
                cout << "right_val: " << right_val << " ";
                cout << "old result: " << result << endl;
                result = left_val - right_val;
                cout << "new result: " << result << endl;
                break;
        }
        return result;
    }
    
};

struct ExpressionProcessor
{
  map<char,int> variables;

  int calculate(const string& expression)
  {
      Cal cal{};
      for(int i=0; i<expression.size(); ++i) {
          if(expression[i]>='0' && expression[i]<='9') {
              ostringstream oss;
              oss << expression[i];
              int j = i+1;
              for(;j<expression.size(); ++j) {
                  if(expression[j]>='0' && expression[j]<='9') {
                      oss << expression[j];
                  }else {
                      break;
                  }
              }
              i = j-1;
              
              int val{};
              istringstream iss{oss.str()};
              iss >> val;
              
             
              if(!cal.caled) {
                  cal.left_val = val;
                  cal.result = val;
                  cal.caled = true;
              } else {
                  
                 cal.right_val = val;
                 cal.result = cal.eval();
                 cal.left_val = cal.result;
              }
              
              
          } else if(expression[i] == '+') {
              cal.op = Cal::Op::Add;
          } else if(expression[i] == '-') {
              cal.op = Cal::Op::Sub;
          } else {
              // 字母
              // 多一个字母
              if(i+1 < expression.size()) {
                if((expression[i+1] <'0' || expression[i+1] >'9') && (expression[i+1] != '+') && (expression[i+1] != '-') ) {
                      return 0;
                 }
              }
              
              if(variables.find(expression[i])!=variables.end()) {
                 if(!cal.caled) {
                    cal.left_val = variables.find(expression[i])->second;
                    cal.caled = true;
                 } else {
                    cal.right_val = variables.find(expression[i])->second;
                    cal.result = cal.eval();
                    cal.left_val = cal.result;
                 }
              }else {
                  return 0;
              }
              
          }
      }

      return cal.result;
  }
};

int main(int argc, char* argv[]) {
    ExpressionProcessor ep{};
    ep.variables['x'] = 1;
    int res = ep.calculate("5-3-x");
    cout << res << endl;

}