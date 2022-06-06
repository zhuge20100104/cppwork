#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        if(points.empty()) {
            return 0;
        }

        sort(points.begin(), points.end(), [](vector<int>& u, vector<int>& v){  
            return u[1] < v[1];
        });

        // 最小右值作为初始值
        int pos = points[0][1];
        // 默认第一个球要射一剑
        int ans = 1;
        for(int i=1; i<points.size(); ++i) {
            if(points[i][0] > pos) {
                // 没有交集，需要再射一剑
                ++ans; 
                // 更新pos
                pos = points[i][1];
            }
        }
        // 返回需要射几剑
        return ans;
    }
};

template<typename T>
ostream& operator<<(ostream& os, vector<vector<T>> const& points) {
    stringstream ss;
    for(auto v: points) {
        stringstream inner_ss;
        inner_ss << "[";
        for(auto ele: v) {
            inner_ss << ele << ",";
        }

        // 去掉最右边的逗号
        string inner_str = inner_ss.str();
        inner_str = inner_str.substr(0, inner_str.size()-1);
        ss << inner_str;
        ss << "],";
    }
    // 再次去掉最右边的逗号
    string out_str = ss.str();
    out_str = out_str.substr(0, out_str.size()-1); 
    return os << out_str;
}

auto main(int argc, char** argv) -> int {
    vector<vector<int>> points {{10, 16}, {2, 8}, {1, 6}, {7, 12}};
    Solution s;
    auto arrows = s.findMinArrowShots(points);
    cout << "ballons: " << points << " can be shoot out in: " << arrows << " arrows\n";
    return EXIT_SUCCESS;
}