#include "contact.h"

std::ostream& operator<<(std::ostream& out, const Contact& contact) {
    out << contact.firstName << " " << contact.lastName << " " << contact.address << " "
        << contact.emailID << " " << contact.company << " " << contact.primaryPhoneNumber << " "
        << contact.secondaryPhoneNumber << " ";
    
    switch (contact.group)
    {
    case Group::Friends:
        out << "Friends";
        break;
    case Group::Family:
        out << "Family";
        break;
    case Group::Coworker:
        out << "Coworker";
        break;
    case Group::Acquaintance:
        out << "Acquaintance";
        break;
    default:
        out << "Err, Wrong group";
        break;
    }
    return out;
}