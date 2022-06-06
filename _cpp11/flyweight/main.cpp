#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>
#include <iostream>
using namespace std;

struct Sentence
{

  struct WordToken
  {
    WordToken() {}  
    WordToken(size_t index_, bool capitalize_): index{index_}, capitalize{capitalize_} {}
    size_t index{0};
    bool capitalize{false};
  };
   
  string text_;
  
  map<size_t,WordToken> tokens_;
  
  vector<string> substrs_;

  vector<string> get_sub_strs(const string& source, const string& delim) {
    string s {source};
    vector<string> res;
    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delim)) != std::string::npos) {
        token = s.substr(0, pos);
        res.push_back(token);
        s.erase(0, pos + delim.length());
    }
    res.push_back(s);
    return res;
  }
  
  Sentence(const string& text): text_{text}, substrs_ {get_sub_strs(text_, " ")}
  {
  }

  WordToken& operator[](size_t index)
  {
      std::cout << index << std::endl;   
      WordToken token(index, false);
      tokens_[index] = token;
      return tokens_[index];
  }

  string str() const
  {
      ostringstream oss;
      for(size_t i=0; i<substrs_.size(); ++i) {
          
        string cur = substrs_[i];
        if(tokens_.find(i) != tokens_.end()) {
            auto token = tokens_.find(i);
            if(token->second.capitalize) {
                transform(cur.begin(), cur.end(), cur.begin(), ::toupper);
            } else {
                transform(cur.begin(), cur.end(), cur.begin(), ::tolower);   
            }
        }
          oss << cur << " ";
      }
      string res = oss.str();
      res = res.substr(0, res.size() - 1);
      return res;
  }
};

int main(int argc, char* argv[]) {
    Sentence setence {"alpha beta gamma"};
    setence[1].capitalize = true;
    cout << setence.str() <<endl;
    setence[1].capitalize = false;
    setence[0].capitalize = true;
    setence[0].capitalize = false;
    setence[0].capitalize = true;
    cout << setence.str() <<endl;
}