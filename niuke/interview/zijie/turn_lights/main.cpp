#include <iostream>
#include <vector>
#include <sstream>

using namespace std;


class Solution {
public:
    vector<int> turn_lights(int lights, int clicks) {
        vector<int> lights_arr(lights, 0);

        int odd_flag {0};
        int even_flag {0};

        for(int click=0; click<clicks; ++ click) {
            if(click % 2 == 0) {
                ++ odd_flag;
                for(int i=0; i<lights; i+=2) {
                    lights_arr[i] = (odd_flag%2==0? 0:1);
                }
            } else {
                ++ even_flag;
                for(int i=1; i<lights; i+=2) {
                    lights_arr[i] = (even_flag%2==0? 0:1);
                }
            }
        }

        return lights_arr;
    }
}; 

int main(int argc, char* argv[]) {
    int lights, clicks;
    string clicks_str;

    Solution sol;
    while(getline(cin, clicks_str)) {
        stringstream ss{clicks_str};
        string temp;
        getline(ss, temp, ',');
        lights = stoi(temp);
        getline(ss, temp, ',');
        clicks = stoi(temp);
        auto res = sol.turn_lights(lights, clicks);
        for(auto const& ele: res) {
            cout << ele << " ";
        }
        cout << endl;
    }
    return EXIT_SUCCESS;    
}