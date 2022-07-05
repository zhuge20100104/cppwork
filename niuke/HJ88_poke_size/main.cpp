#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#include <map>

using namespace std;


vector<string> pokes{"3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A", "2", "joker", "JOKER"};
map<string, int> priorities;

ostream& operator<<(ostream& os, vector<string> const& res) {
    for(auto const& ele: res) {
        os << ele << " ";
    }
    return os;
}

int compare(vector<string> const& poker1, vector<string> const& poker2) {
    // 有王炸
    if(poker1.size()==2 && poker1[0] == "joker" && poker1[1] == "JOKER") return 0;
    if(poker2.size()==2 && poker2[0] == "joker" && poker2[1] == "JOKER") return 1;
    // 数目一致，检查第一张的大小
    if(poker1.size() == poker2.size()) return priorities[poker1[0]] > priorities[poker2[0]] ? 0: 1;
    // 数目不一致，是否有炸弹
    if(poker1.size() == 4) return 0;
    if(poker2.size() == 4) return 1;

    // 牌数不一致，且没有炸弹，没法比较
    return 2;   
}

// 题目: https://www.nowcoder.com/practice/d290db02bacc4c40965ac31d16b1c3eb?tpId=37&tqId=21311&rp=1&ru=/exam/oj/ta&qru=/exam/oj/ta&sourceUrl=%2Fexam%2Foj%2Fta%3Fpage%3D2%26tpId%3D37%26type%3D37&difficulty=undefined&judgeStatus=undefined&tags=&title=
int main(int argc, char* argv[]) {
    string poke_str;
    // 有空格的时候不能用cin, 要用getline
    while(getline(cin, poke_str)) {
        auto pos = poke_str.find('-');
        auto first_poke_str = poke_str.substr(0, pos);
        auto second_poke_str = poke_str.substr(pos+1);

        vector<string> first_poke;
        vector<string> second_poke;
        stringstream ss{first_poke_str};
        string temp;
        while(ss >> temp) {
            first_poke.emplace_back(move(temp));
        }

        stringstream ss_sec{second_poke_str};
        while(ss_sec >> temp) {
            second_poke.emplace_back(move(temp));
        }

        // 越往后面优先级越高
        for(int i=0; i<pokes.size(); ++i) {
            priorities[pokes[i]] = i;
        }

        auto res = compare(first_poke, second_poke);
        if(res == 0) {
            cout << first_poke << "\n";
        } else if(res == 1) {
            cout << second_poke << "\n";
        } else {
            cout << "ERROR" << "\n";
        }

    }
    return EXIT_SUCCESS;
}