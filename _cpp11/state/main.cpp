#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

class CombinationLock
{
    size_t current_idx {0};
    vector<int> combination;
public:
    string status;

    CombinationLock(const vector<int> &combination) : combination(combination), status{"LOCKED"} {
      
    }

    void enter_digit(int digit)
    {
      if(status.compare("LOCKED") == 0) {
          status = "";
      }
      
      if(current_idx >= combination.size()) {
          status = "ERROR";
          return;
      }
      
      if(status == "ERROR") {
          return;
      }
      
      if(combination[current_idx] == digit) {
        ostringstream oss;  
        oss << digit;
        status += oss.str();
      }else {
          status = "ERROR";
          return;
      }

      if(current_idx == combination.size()-1) {
          status = "OPEN";
      }
      ++current_idx;
      
    }
};

int main(int argc, char* argv[]) {
    CombinationLock c1({1, 2, 3});
    cout << c1.status << endl;
    c1.enter_digit(1);
    c1.enter_digit(3);
    cout << c1.status << endl;
    c1.enter_digit(3);
    cout << c1.status << endl;
    return 0;
}