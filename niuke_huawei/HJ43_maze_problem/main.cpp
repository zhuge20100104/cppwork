#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;
int m, n;
vector<vector<int>> maze;
vector<vector<int>> temp_path;
vector<vector<int>> best_path;

void dfs(int i, int j) {
    // 遇到边界，或者碰墙/已走过
    if(i<0 ||i>=m || j<0 || j>=n || maze[i][j] == 1) {
        return;
    }
    maze[i][j] = 1;
    temp_path.push_back({i, j});
    // 到右下角了，找到一个解，因为是唯一解，直接赋值就可以了
    if(i==m-1 && j==n-1) {
        best_path = temp_path;
        return;
    }

    dfs(i-1, j);
    dfs(i+1, j);
    dfs(i, j-1);
    dfs(i, j+1);
    maze[i][j] = 0; // 回溯
    temp_path.pop_back(); // 还原，回溯
}

// 题目: https://www.nowcoder.com/practice/cf24906056f4488c9ddb132f317e03bc?tpId=37&rp=1&ru=%2Fexam%2Foj%2Fta&qru=%2Fexam%2Foj%2Fta&sourceUrl=%2Fexam%2Foj%2Fta%3Fpage%3D2%26tpId%3D37%26type%3D37&difficulty=&judgeStatus=&tags=&title=&gioEnter=menu
int main(int argc, char* argv[]) {
    
    while(cin >> m >> n) {
        maze = vector<vector<int>>(m, vector<int>(n, 0));
        for(int i=0; i<m; ++i) {
            for(int j=0; j<n; ++j) {
                cin >> maze[i][j];
            }
        }
        dfs(0, 0);
        for(auto ele: best_path) {
            cout << '(' << ele[0] << ',' << ele[1] << ')' << endl;
        }

        vector<vector<int>> tmp1;
        vector<vector<int>> tmp2;
        temp_path.swap(tmp1);
        best_path.swap(tmp2);
    }
    return EXIT_SUCCESS;
}