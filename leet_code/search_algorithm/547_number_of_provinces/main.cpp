#include "printer/printer.hpp"

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;


class Solution {
public:
    void dfs(vector<vector<int>>& isConnected, vector<int>& visited, int size, int i) {
        for(int j=0; j<size; ++j) {
            if(isConnected[i][j] == 1 && visited[j] == 0) {
                // 表示已经找到相邻的元素了
                visited[j] = 1;
                dfs(isConnected, visited, size, j);
            }
        }
    }
    int findCircleNum(vector<vector<int>>& isConnected) {
        int size = isConnected.size();
        vector<int> visited(size);
        int provinces {0};
        for(int i=0; i<size; ++i) {
            // 说明前面的行横向扫描过后，没有和下面的行有交集，需要扫描当前行，并增加省份数
            if(!visited[i]) {
                dfs(isConnected, visited, size, i);
                ++provinces;
            }
        }
        return provinces;
    }
};

auto main(int argc, char** argv) -> int {
    Solution s;
    
    return EXIT_SUCCESS;
}