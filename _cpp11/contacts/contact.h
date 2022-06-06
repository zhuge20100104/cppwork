#ifndef _FREDRIC_CONTACT_H_
#define _FREDRIC_CONTACT_H_
#include <iostream>
#include <string>

enum class Group {
    Friends,
    Family,
    Coworker,
    Acquaintance
};

struct Contact {
    std::string firstName{};
    std::string lastName{};
    std::string primaryPhoneNumber{};
    std::string secondaryPhoneNumber{};
    std::string emailID{};
    std::string address{};
    std::string company;
    Group group{Group::Friends};
};

std::ostream& operator<<(std::ostream& out, const Contact& contact);

#endif