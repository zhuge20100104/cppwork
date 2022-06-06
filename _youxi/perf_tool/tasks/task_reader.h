#ifndef _FREDRIC_TASK_HANDLER_H_
#define _FREDRIC_TASK_HANDLER_H_

#include "tasks/task.h"

#include <string>

struct task_reader {
    task_reader(task t_);
    std::string parse_tasks(const std::string& task_file_path);

    private:
        task task_;
};

#endif