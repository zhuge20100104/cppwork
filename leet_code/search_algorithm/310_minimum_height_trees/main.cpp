#include "printer/printer.hpp"

#include <string>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;


class Solution {
    vector<int> result;

public:

    // n个顶点和对应的边的集合
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        if(n==1) {
            return {0};
        }

        // 建立每个节点对应的度[相连节点的个数]
        vector<int> digital(n, 0);
        // 建立邻接表，与其相连的节点的集合
        unordered_map<int, vector<int>>  map_;
        for(int i=0; i<edges.size(); ++i) {
            // 每个节点对应的度加1
            ++digital[edges[i][0]];
            ++digital[edges[i][1]];
            // 建立每个节点相连的节点组成的表
            map_[edges[i][0]].push_back(edges[i][1]);
            map_[edges[i][1]].push_back(edges[i][0]);
        }

        // 队列中存放外层的叶子节点，就是度为1的节点
        queue<int> que;
        for(int i=0; i<n; ++i) {
            // 叶子节点
            if(digital[i] == 1) {
                que.push(i);
            }
        }

        // 广度优先遍历找出最短路径的根集合
        while(!que.empty()) {
            // 更新result，如果不是根节点，就会被抛弃
            result.clear();
            int size = que.size();
            // 让外层叶子节点出队，剪除最外层的叶子节点，露出新的叶子节点
            while(size--) {
                int leaft = que.front();
                que.pop();
                // 将叶子节点加入result，后续如果不是根节点，会被清空
                result.push_back(leaft);
                // 更新与被剪去的叶子节点相连的节点，如果相连的节点剪完之后是叶子节点，需要入队，接着剪，直到找到根节点
                for(auto lef: map_[leaft]) {
                    --digital[lef];
                    if(digital[lef] == 1) {
                        que.push(lef);
                    }
                }
            }
        }

        return result;
    }
};

auto main(int argc, char** argv) -> int {
    Solution s;

    return EXIT_SUCCESS;
}