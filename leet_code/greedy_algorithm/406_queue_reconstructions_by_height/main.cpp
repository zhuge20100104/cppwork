#include "printer/printer.hpp"

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        // 排序规则，身高较高的放在后面，
        // 当身高相同的时候，排序较大的放在前面
        sort(people.begin(), people.end(), [](vector<int> const& u, vector<int> const& v){
            return u[0] < v[0] || (u[0] == v[0] && u[1] > v[1]);
        });

        int n = people.size();
        vector<vector<int>> ans(n);
        for(auto const& person: people) {
            // 计算当前元素的space位置数，+1是为了防止减出负数来
            int spaces = person[1] + 1;
            // 在链表中的空位中插值，按照 spaces所在的位置插
            for(int i=0; i<n; ++i) {
                if(ans[i].empty()) {
                    --spaces;
                    // 说明当前已经循环到spaces位置了
                    if(!spaces) {
                        // 插值，退出
                        ans[i] = person;
                        break;
                    }
                }
            }
        }
        return ans;
    }
};

auto main(int argc, char** argv) -> int {
    Solution s;
    vector<vector<int>> people {{7,0},{4,4},{7,1},{5,0},{6,1},{5,2}};
    auto ans = s.reconstructQueue(people);

    cout << people << "\n is reconstructed to the below queue: \n";
    cout << ans << "\n"; 
    return EXIT_SUCCESS;
}