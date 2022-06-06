#ifndef _FREDRIC_CHAT_ROOM_H_
#define _FREDRIC_CHAT_ROOM_H_

#include <vector>

struct ChatRoom {
    std::vector<Person*> people;
    void join(Person* p);
    void broadcast(std::string const& origin, std::string const& message);
    void message(std::string const& origin, std::string const& who, std::string const& message);
};
#endif