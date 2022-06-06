#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
using namespace std;

struct Token
{
  int value;

  Token(int value) : value(value) {}
};

struct Memento
{   
    Memento(vector<shared_ptr<Token>>&& tokens_): tokens{std::move(tokens_)} {
        cout << "Move version of vector constructor is invoked..." << endl;    
    }
    
    Memento(const vector<shared_ptr<Token>>& tokens_): tokens{tokens_} {}
    vector<shared_ptr<Token>> tokens;
};

struct TokenMachine
{

  vector<shared_ptr<Token>> tokens;

  Memento add_token(int value)
  {
    return add_token(make_shared<Token>(value));
  }

  // adds the token to the set of tokens and returns the
  // snapshot of the entire system
  Memento add_token(const shared_ptr<Token>& token)
  {
      // Add Token to the set of tokens
      tokens.push_back(token);
      
      // Return snapshot of the entire system
      vector<shared_ptr<Token>> ret_tokens;
      for(auto&& tmp_token: tokens) {   
          ret_tokens.push_back(make_shared<Token>(tmp_token->value));
      }
    
      return {std::move(ret_tokens)};
  }

  // reverts the system to a state represented by the token
  void revert(const Memento& m)
  {
      tokens = m.tokens;
  }
};

int main(int argc, char* argv[]) {
    TokenMachine tm;
    tm.add_token(1);
    return 0;
}