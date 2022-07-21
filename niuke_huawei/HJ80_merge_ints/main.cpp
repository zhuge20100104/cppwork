#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>

using namespace std;

ostream& operator<<(ostream& os, vector<int> const& nums) {
    for (auto const& ele : nums) {
        os << ele;
    }
    return os;
}

vector<int> merge_ints(vector<int> const& nums1, vector<int> const& nums2) {
    set<int> s;
    for (auto ele : nums1) {
        s.insert(ele);
    }
    for (auto ele : nums2) {
        s.insert(ele);
    }

    vector<int> res{s.begin(), s.end()};
    return res;
}

int main(int argc, char* argv[]) {
    int m, n;

    vector<int> nums1, nums2;
    cin >> m;

    int tmp{0};
    getline()
    for (int i = 0; i < m; ++i) {
        cin >> tmp;
        nums1.emplace_back(tmp);
    }

    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> tmp;
        nums2.emplace_back(tmp);
    }

    auto res = merge_ints(nums1, nums2);
    cout << res << endl;

    return EXIT_SUCCESS;
}
