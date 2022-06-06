#ifndef _FREDRIC_PERSON_H_
#define _FREDRIC_PERSON_H_

#include <string>
#include <iostream>
#include <vector>

struct ChatRoom;

struct Person {
    std::string name;
    ChatRoom* room {nullptr};

    Person(std::string const& name_);
    void receive(std::string const& origin, std::string const& message);
    void say(std::string const& message) const;
    // Private message from this person to "who"
    void pm(std::string const& who, std::string const& message) const;

    std::vector<std::string> chat_log;

   
    friend bool operator==(Person const& lhs, Person const& rhs) {
        return lhs.name == rhs.name;
    }

    friend bool operator!=(Person const& lhs, Person const& rhs) {
        return !(lhs == rhs);
    }
};

#endif