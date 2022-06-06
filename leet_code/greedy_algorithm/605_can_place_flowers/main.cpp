#include <iostream>
#include <vector>
#include <numeric>
#include <sstream>

using namespace std;

class Solution {
public:   
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        int count = 0;
        int m = flowerbed.size();
        // 假设最左边没有种花，当作标记
        int prev = -1;
        for(int i=0; i<m; ++i) {
            // 这个地方种花了
            if(flowerbed[i] == 1) {
                // 说明是在第一次种花的左边，也就是l侧
                // 可以从 l-2处之前开始种
                // 可以种的位置数为 l-1
                // 可以种 (l-1 + 1)/2 朵花
                if(prev < 0) {
                    count += i/2;
                } else {
                    // 说明前面已经种过花了，处于中间位置
                    // l -> j
                    // 可以种 l-j- 3 个位置，具体看图，自己推理
                    // 可以种 (l-j-3+1)/2朵花
                    count += (i-prev-2)/2;
                }
                if(count >= n) {
                    return true;
                }
                prev = i;
            }
        }

        // 最后的 j 到完个位置怎么种
        if(prev < 0) {
            // 如果遍历完全都没种，那就是 m个位置可以种
            // 可以种 (m+1)/2朵花
            count += (m+1)/2;
        }else {
            // 否则就是前面有种过的，
            // 那有m-prev-2个位置可以种，
            // 总共可以种 （m-prev-2+1）/2朵花
            count += (m-prev-1)/2;
        }

        return count >= n;
    }
};

template <typename T>
ostream& operator<<(ostream& os, vector<T> const& eles) {
    stringstream ss;
    for(auto&& ele: eles) {
        ss << ele << ",";
    }
    string res_str = ss.str();
    res_str = res_str.substr(0, res_str.size()-1);
    return os << res_str;
}

auto main(int argc, char** argv) -> int {
    vector<int> flowerbed {1, 0, 0, 0, 1};
    int n {1};
    Solution s;
    auto can_place = s.canPlaceFlowers(flowerbed, n);
    cout << "Flowerbed: " << flowerbed;
    
    if(can_place) {
        cout << " can place ";
    } else {
        cout << " can't place ";
    } 
    cout << n << " flowers\n";

    return EXIT_SUCCESS;
}