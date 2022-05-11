#ifndef _PACKAGE_DATA_H_
#define _PACKAGE_DATA_H_
#include "../utils/sync_queue.hpp"
#include <boost/atomic.hpp>

#include <vector>
#include <algorithm>
#include <iostream>

class PackageData
{
private:
    std::vector<int> input_;
    SyncQueue<int> &data_queue_;

public:
    PackageData(std::vector<int> input, SyncQueue<int> &data_queue) : input_(input), data_queue_(data_queue)
    {
    }

    void package_data() const
    {
        for (int i = 0; i < input_.size(); ++i)
        {
            data_queue_.Put(input_[i]);
        }
    }
};

#endif