#include <iostream>
#include <queue>
#include <stack>
#include <algorithm>
#include <string>
#include <sstream>

using namespace std;

vector<string> v;

void print_queue(queue<int> r) {
    stringstream ss;
    while(!r.empty()) {
        ss << r.front() << " ";
        r.pop();
    }

    v.emplace_back(move(ss.str()));
}


void solution(queue<int> in, stack<int> st, queue<int> r, bool do_push) {
    if(in.empty()) { // 当前输入队列为空
        if(do_push) { // 无法从输入栈加入元素到st
            return;
        }

        // 那就是弹出了。
        // 输入队列为空，说明已经加完了一次了，把输出栈中剩余元素弹出到 队列
        // 然后输出结果到vector
        while(!st.empty()) {
            r.push(st.top());
            st.pop();
        }
        // 将当前结果打印到vector
        print_queue(r);
        // 这一把完事儿，当前递归退出，别忘了
        return;
    } else { // 说明输入队列不为空
        if(do_push) { // 如果是 从输入队列压入元素到st
            // 因为输入队列有值，是可以压入元素到栈的
            st.push(in.front());
            in.pop();
        } else { // 如果是从st栈中弹出元素到输出队列r
            if(st.empty()) return;  // 如果栈为空，无法弹出元素到 r
            r.push(st.top());
            st.pop(); 
        }

        // 外面 push了一次，这里要pop一次
        solution(in, st, r, false);
        // 再push一次，连起递归链
        solution(in, st, r, true);
    }
}

int main(int argc, char* argv[]) {
    int n, num;
    while(cin >> n) {
        queue<int> in;
        for(int i=0; i<n; ++i) {
            cin >> num;
            in.push(num);
        }

        queue<int> r;
        stack<int> st;

        solution(in, st, r, true);

        sort(v.begin(), v.end());

        for(auto const& res: v) {
            cout << res << endl;
        }
    }
    return EXIT_SUCCESS;
}

