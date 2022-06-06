#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int findContentChildren(vector<int>& children, vector<int>& cookies) {
        sort(children.begin(), children.end());
        sort(cookies.begin(), cookies.end());
        int child = 0, cookie = 0;
        while(child < children.size() && cookie < cookies.size()) {
            if(children[child] <= cookies[cookie]) {
                ++child;
            }
            ++cookie;
        }
        return child;
    }
};

auto main(int argc, char** argv) -> int {
    Solution s;
    vector<int> children {1, 2};
    vector<int> cookies {1, 2, 3};

    auto child_count = s.findContentChildren(children, cookies);
    std::cout << "Content children count is: " << child_count << "\n";
    
    return EXIT_SUCCESS;
}