#include "person.h"
#include "chatroom.h"

Person::Person(std::string const& name_): name{name_} {

}

void Person::receive(std::string const& origin, std::string const& message) {
    std::string s {origin + ": \"" + message +"\""};
    std::cout << "[" << name << "'s chat session]" << s << "\n";
    chat_log.emplace_back(s);
}

void Person::say(std::string const& message) const {
    room->broadcast(name, message);
}

void Person::pm(std::string const& who, std::string const& message) const {
    room->message(name, who, message);
}
