#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>

using namespace std;

vector<double> nums(4, 0);
// 标志当前节点是否访问过
vector<bool> vis(4, false);

bool flag {false};

void dfs(int step, double sum) {
    if(step == 3) {
        // 凑到24点了
        if(sum == 24) {
            flag = true;
            return;
        }
    } else {
        ++step;
        for(int i=0; i<nums.size(); ++i) {
            if(!vis[i]) {
                vis[i] = true;
                dfs(step, sum+nums[i]);
                dfs(step, sum-nums[i]);
                dfs(step, sum*nums[i]);
                dfs(step, sum/nums[i]);
                vis[i] = false;  // 回溯，标识当前位没有访问过，重新访问当前位
            }
        } 
    }
}

// 题目: https://www.nowcoder.com/practice/fbc417f314f745b1978fc751a54ac8cb?tpId=37&tqId=21290&rp=1&ru=/exam/oj/ta&qru=/exam/oj/ta&sourceUrl=%2Fexam%2Foj%2Fta%3Fpage%3D2%26tpId%3D37%26type%3D37&difficulty=undefined&judgeStatus=undefined&tags=&title=
int main(int argc, char* argv[]) {
    stringstream ss;
    string nums_str;
    while (getline(cin, nums_str)) {
        ss << nums_str;
        string tmp_str;
        auto i{0};
        while(ss >> tmp_str) {
            nums[i++] = atof(tmp_str.data());
        }

        dfs(-1, 0);
        if(flag) {
            cout << "true" << endl;
        } else {
            cout << "false" << endl;
        }

        flag = false;
        vector<bool> tmp_vis(4, false);
        vis.swap(tmp_vis);
        ss.clear();
    }
    
    return EXIT_SUCCESS;
}