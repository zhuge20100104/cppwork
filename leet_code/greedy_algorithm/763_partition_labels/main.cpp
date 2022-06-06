#include <iostream>
#include <vector>
#include <algorithm>
#include <array>

using namespace std;

class Solution {
public:
    vector<int> partitionLabels(string s) {
        array<int, 26> last;
        // 记录所有字符最后出现的位置
        for(int i=0; i<s.size(); ++i) {
            last[s[i] - 'a'] = i;
        }
        vector<int> partition;
        int start = 0;
        int end = 0;
        for(int i=0; i<s.size(); ++i) {
            end = max(end, last[s[i]-'a']);
            // 出现一个最大match
            if(end == i) {
                // 保存最大match长度用于输出
                partition.emplace_back(end-start+1);
                // 接着寻找下一个子串的最大值
                start = end + 1;
            }
        }
        return partition;
    }
};

auto main(int argc, char** argv) -> int {
    Solution s;
    string str = "ababcbacadefegdehijhklij";
    auto partition = s.partitionLabels(str);
    cout << str << " can be paritioned to the below parts: ";
    for_each(partition.begin(), partition.end(), [](int const ele) {
        cout << ele << " ";
    });

    cout << "\n";
    return EXIT_SUCCESS;
}