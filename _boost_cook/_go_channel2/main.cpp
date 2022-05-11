#include "utils/tasks_processor_multithread.hpp"
#include "utils/sync_queue.hpp"
#include "send_data/consts.h"
#include "send_data/send_data.h"
#include "send_data/package_data.h"

#include <boost/lexical_cast.hpp>

using namespace tp_multithread;

int main(int argc, char *argv[])
{

    SyncQueue<int> d_queue(TASK_SIZE * DATA_SIZE);

    for (std::size_t i = 0; i < TASK_SIZE; ++i)
    {
        std::vector<int> a;
        for (int j = 0; j < DATA_SIZE; ++j)
        {
            int ele = 1 + i * DATA_SIZE + j;
            a.emplace_back(ele);
        }

        tasks_processor::get().push_task([a, &d_queue]() {
            PackageData pack_data(a, d_queue);
            pack_data.package_data();
        });

        tasks_processor::get().push_task([&d_queue]() {
            SendData send_data(d_queue);
            send_data.send_data();
        });
    }

    tasks_processor::get().start_multiple();
}