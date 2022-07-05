#include "printer/printer.hpp"

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

template <typename T>
ostream& operator<<(ostream& os, unordered_set<T> const& set_) {
    for (auto const& ele : set_) {
        os << ele << " ";
    }
    return os;
}

ostream& operator<<(ostream& os,
                    unordered_map<string, vector<string>> const& map_) {
    for (auto const& [key, vect] : map_) {
        cout << key << "---> ";
        for (auto const& ele : vect) {
            cout << ele << " ";
        }
        cout << "\n";
    }
    return os;
}

class Solution {
   public:
    // 主函数
    vector<vector<string>> findLadders(string beginWord,
                                       string endWord,
                                       vector<string>& wordList) {
        vector<vector<string>> ans;
        // 把wordList里面的所有词拷到 set里面
        unordered_set<string> dict(wordList.begin(), wordList.end());
        // 找不到endWord，说明无法结束
        if(!dict.count(endWord)) {
            return ans;
        }
        // 去掉beginWord和endWord，因为这两是边界值，查找的时候我们只查找中间值
        dict.erase(beginWord);
        dict.erase(endWord);
        // 设置起始队列和结束队列
        // 可以从两个方向查找
        // 加快速度
        unordered_set<string> q1{beginWord}, q2{endWord};
        unordered_map<string, vector<string>> next;
        // reversed，是否反向查找标记，reversed=true意味着从end找start,那么加到next的时候就得反着来
        // next[start] = end
        bool reversed{false}, found{false};
        // 广度优先遍历填充next映射，找出所有词组之间的关系
        while(!q1.empty()) {
            // 临时变量，存储当前词对应的中间词，它也是下次开始遍历的起始词
            unordered_set<string> q;
            for(auto const& w: q1) {
                // 拷贝w到s，便于修改
                string s = w;
                // 对整个单词遍历，看修改一个词之后，能否和之前的单词匹配
                for(size_t i=0; i<s.size(); ++i) {
                    char ch = s[i];
                    for(int j=0; j<26; ++j) {
                        s[i] = j + 'a';
                        // 说明遇到结束字符
                        if(q2.count(s)) {
                            // 如果当前是反向，则是修改后的s作为key，否则相反
                            reversed? next[s].push_back(w): next[w].push_back(s);
                            // 找到了一条路
                            found = true;
                        }
                        // 中间词，放入next map，放入q，用于下次广度优先遍历
                        if(dict.count(s)) {
                            reversed? next[s].push_back(w): next[w].push_back(s);  
                            q.insert(s);  
                        }
                    }
                    s[i] = ch; // 完事以后 回溯到上一状态
                }
            }
            // 找到匹配的了，退出
            if(found) {
                break;
            }

            // 所有已经用过的词，不要再用了
            for(auto const& w: q) {
                dict.erase(w);
            }

            // 如果q的大小比上次的大小要大，转换队列方向，否则保持原向
            // q2即是结束队列，也是缓存队列，缓存中间队列q的值
            if(q.size() <= q2.size()) {
                q1 = q;
            } else {
                reversed = !reversed;
                q1 = q2;
                q2 = q;
            }
        }


        // 说明BFS有解,通过dfs+回溯把next连起来
        if(found) {
            // 一条path代表一条可行的路径
            // path中先填入开始词
            vector<string> path {beginWord};
            backtracking(beginWord, endWord, next, path, ans);
        }
        return ans;
    }   

    // 回溯法把next映射拼成结果
    void backtracking(string const& src, string const& dst, unordered_map<string, vector<string>>& next, vector<string>& path, vector<vector<string>>& ans) {
        // 说明深度搜索到最后一个单词了
        if(src == dst) {
            // 找到了一个答案，放到答案列表里面
            ans.push_back(path);
            return;
        }

        for(auto const& s: next[src]) {
            path.push_back(s);
            backtracking(s, dst, next, path, ans);
            path.pop_back(); // 回溯，寻找其他的答案
        }
    }
};

auto main(int argc, char** argv) -> int {
    Solution s;
    auto beginWord{"hit"};
    auto endWord{"cog"};
    vector<string> wordList{"hot", "dot", "dog", "lot", "log", "cog"};
    auto ans = s.findLadders(beginWord, endWord, wordList);
    cout << "Answer: " << ans << "\n";
    return EXIT_SUCCESS;
}