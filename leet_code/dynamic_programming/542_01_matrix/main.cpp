#include "printer/printer.hpp"

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;


class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        int rows = mat.size();
        if(!rows) return mat;
        int cols = mat[0].size();
        // 因为题目说矩阵数据个数不超过10万，所以这里减去10万
        vector<vector<int>> dist{rows, vector<int>(cols, __INT_MAX__- 100000)};
        // 从左上角往右下角遍历，更新一遍数据
        for(int i=0; i<rows; ++i) {
            for(int j=0; j<cols; ++j) {
                // 说明当前行列本来就是0，说明距离就是0
                if(mat[i][j] == 0) {
                    dist[i][j] = 0;
                } else {
                    // 
                    if(i>0) {
                        // 比较当前数 和上方的数+1
                        dist[i][j] = min(dist[i][j], dist[i-1][j]+1);
                    }
                    if(j>0) {
                        // 比较当前数 和左方的数+1
                        dist[i][j] = min(dist[i][j], dist[i][j-1]+1);
                    }
                }
            }
        }

        for(int i=rows-1; i>=0; --i) {
            for(int j=cols-1; j>=0; --j) {
                if(i<rows-1) {
                    dist[i][j] = min(dist[i][j], dist[i+1][j]+1);
                }

                if(j<cols-1) {
                    dist[i][j] = min(dist[i][j], dist[i][j+1]+1);
                }
            }
        }

        return dist;
    }
};

auto main(int argc, char** argv) -> int {
    Solution s;

    return EXIT_SUCCESS;
}