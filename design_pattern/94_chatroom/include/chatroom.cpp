#include "person.h"
#include "chatroom.h"
#include <algorithm>

void ChatRoom::broadcast(std::string const& origin, std::string const& message) {
    // 给除去自己以外的人广播这条消息
    for(auto&& p: people) {
        if(p->name != origin) {
            p->receive(origin, message);
        }
    }
}

void ChatRoom::join(Person* p) {
    std::string join_msg = p->name + " joins the chat";
    broadcast("room", join_msg);

    p->room = this;
    people.push_back(p);
}

// 从origin 给who发message
void ChatRoom::message(std::string const& origin, std::string const& who, std::string const& message) {
    auto target = std::find_if(people.begin(), people.end(), [&](Person const* p){
        return p->name == who;
    });

    if(target != people.end()) {
        (*target)->receive(origin, message);
    }
}