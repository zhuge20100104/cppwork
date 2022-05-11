#ifndef _MANAGER_H_
#define _MANAGER_H_

#include <iostream>
using std::cout;
using std::endl;
#include <vector>
using std::vector;
#include <memory>
using std::shared_ptr;
#include "person.h"
#include <algorithm>
using std::for_each;
#include <deque>
#include <numeric>
using std::deque;

using PersonPtr = shared_ptr<Person>;
using PersonArr = vector<shared_ptr<Person> >;
using PersonIt = PersonArr::iterator;

class Manager {
    public:
        Manager() {
            initPerson();
        }

        // 评委打分
        void setScores() {
            for_each(begin(m_Persons), end(m_Persons), [](PersonPtr& personP) {
                deque<int> d;
                // 模拟10个评委打分
                for(int i=0; i<10; ++i) {
                    int score = rand() % 41 + 60;
                    d.push_back(score);
                }
                // 排序
                sort(begin(d), end(d));
                // 去除最低分
                d.pop_front();
                // 去除最高分
                d.pop_back();

                // 求和
                int sum = accumulate(begin(d), end(d), 0);
                
                int avg = sum / d.size();
                personP->m_Score = avg; 
            });
        }

        // 显示分数 
        void showScores() {
            for_each(begin(m_Persons), end(m_Persons), [](const PersonPtr& personP){
                cout << "姓名: " << personP->m_Name << " 分数: " << personP->m_Score << endl;
            });
        }
    

    private:
        // 初始化选手和分数
        void initPerson() {
            string nameSeed = "ABCDEFGHIJ";
            int len = nameSeed.size();
            for(int i=0; i<len; ++i) {
                string name = "选手";
                name += nameSeed[i];
                int score = 0;
                m_Persons.emplace_back(PersonPtr(new Person(name, score)));
            }
        }

        PersonArr m_Persons;
};

#endif