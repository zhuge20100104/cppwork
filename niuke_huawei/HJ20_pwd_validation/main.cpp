#include <iostream>
#include <queue>
#include <stack>
#include <algorithm>
#include <string>
#include <sstream>

using namespace std;


enum CharType {
    Upper,
    Lower,
    Num,
    Other,
    Len
};


bool validate_pwd(string const& pwd) {
    if(pwd.size() <= 8) {
        return false;
    }

    int state[CharType::Len] = {0};
    for(int i=0; i<pwd.size(); ++i) {
        if(pwd[i] >= 'a' && pwd[i] <= 'z') {
            ++state[CharType::Lower];
        } else if(pwd[i] >= 'A' && pwd[i] <= 'Z') {
            ++state[CharType::Upper];
        } else if(pwd[i] >= '0' && pwd[i] <= '9') {
            ++state[CharType::Num]; 
        } else {
            ++state[CharType::Other];
        }
    }

    int char_type_count{0};
    for(int i=0; i<CharType::Len; ++i) {
        if(state[i] > 0) {
            ++char_type_count;
        }
    }

    if(char_type_count<3) {
        return false;
    }

    int max_substr_len{3};
    for(int i=0; i<pwd.size()-max_substr_len; ++i) {
        for(int j=i+max_substr_len; j<pwd.size()-max_substr_len; ++j) {
            if(!pwd.compare(i, max_substr_len, pwd, j, max_substr_len)) {
                return false;
            }
        }
    }

    return true;
}

int main(int argc, char* argv[]) {
    string str;

    while(cin >> str) {
        if(validate_pwd(str)) {
            cout << "OK" << endl;
        } else {
            cout << "NG" << endl;
        }
    }
    return EXIT_SUCCESS;
}