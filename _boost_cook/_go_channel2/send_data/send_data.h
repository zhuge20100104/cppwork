#ifndef _SEND_DATA_H_
#define _SEND_DATA_H_

#include "consts.h"
#include "../utils/sync_queue.hpp"

class SendData
{
private:
    SyncQueue<int> &data_queue_;

public:
    SendData(SyncQueue<int> &data_queue) : data_queue_(data_queue) {}

    void send_data()
    {
        int ele;
        for (int i = 0; i < DATA_SIZE; ++i)
        {
            data_queue_.Take(ele);
            std::cerr << "data: " << ele << " is been sent!" << std::endl;
        }
    }
};

#endif