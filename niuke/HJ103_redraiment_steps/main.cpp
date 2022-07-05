#include <iostream>
#include <string>
#include <algorithm>
#include<vector>
using namespace std;

// TODO: 在线写DP代码。
ostream& operator<<(ostream& os, vector<int> const& result) {
    for(auto const& ele: result) {
        os << ele << " ";
    }
    return os;
}

int lis(vector<int>& arr) {
    vector<int> dp(arr.size(), 1); //设置数组长度大小的动态规划辅助数组
    int max = 1;
    for(int i = 1; i < arr.size(); i++){
         for(int j = 0; j < i; j++){
            if(arr[i] > arr[j] && dp[i] < dp[j] + 1) {
                dp[i] = dp[j] + 1; //i点比j点大，理论上dp要加1
                //但是可能j不是所需要的最大的，因此需要dp[i] < dp[j] + 1
                max = max > dp[i] ? max : dp[i]; //找到最大长度
            }
        }
    }

    cout << "DP Final: " << dp << endl;
    return max;
}


// 题目: https://www.nowcoder.com/practice/d3d8e23870584782b3dd48f26cb39c8f?tpId=37&tqId=21253&rp=1&ru=/exam/oj/ta&qru=/exam/oj/ta&sourceUrl=%2Fexam%2Foj%2Fta%3Fpage%3D1%26tpId%3D37%26type%3D37&difficulty=undefined&judgeStatus=undefined&tags=&title=
int main(int argc, char* argv[]) {
    int n;
    while(cin >> n){
        vector<int> arr(n);
        for(int i = 0; i < n; i++) //输入
            cin >> arr[i];
        cout << lis(arr) << endl; //计算最长递增子序列长度
    }
    return EXIT_SUCCESS;
}