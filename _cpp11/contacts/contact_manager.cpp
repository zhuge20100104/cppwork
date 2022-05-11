#include "contact_manager.h"

ContactManager::ContactManager(const std::vector<Contact>& contacts)
    : contacts_{contacts} {}

ContactManager::ContactManager(std::vector<Contact>&& contacts)
    : contacts_{contacts} {}

void ContactManager::displaySortedContact(Option option) {
    if (option == Option::FirstName) {
        std::sort(contacts_.begin(), contacts_.end(),
                  [](const Contact& c1, const Contact& c2) {
                      return c1.firstName.compare(c2.firstName) > 0 ? false
                                                                    : true;
                  });
    } else {
        std::sort(contacts_.begin(), contacts_.end(),
                  [](const Contact& c1, const Contact& c2) {
                      return c1.lastName.compare(c2.lastName) > 0 ? false
                                                                  : true;
                  });
    }

    for (const auto& contact : contacts_) {
        std::cout << contact;
        std::cout << std::endl;
    }
}

void ContactManager::displayFirstNameWithPrimaryNumber() const {
    std::for_each(contacts_.begin(), contacts_.end(),
                  [](const Contact& contact) {
                      std::cout << contact.firstName << " "
                                << contact.primaryPhoneNumber << std::endl;
                  });
}

void ContactManager::displayContactsFromACompany(
    const std::string& company) const {
    std::for_each(contacts_.begin(), contacts_.end(),
                  [&company](const Contact& contact) {
                      if (contact.company.compare(company) == 0) {
                          std::cout << contact << std::endl;
                      }
                  });
}

void ContactManager::displayContactsOnGroupType() {
    std::unordered_multimap<Group, Contact> cMap;
    for (const auto& c : contacts_) {
        cMap.emplace(c.group, c);
    }

    for (auto ele : cMap) {
        std::string groupName{};
        switch (ele.first) {
            case Group::Friends:
                groupName = "Friends";
                break;
            case Group::Family:
                groupName = "Family";
                break;
            case Group::Coworker:
                groupName = "Coworker";
                break;
            case Group::Acquaintance:
                groupName = "Acquaintance";
                break;
            default:
                break;
        }
        std::cout << "Group: " << groupName << " Contact: " << ele.second
                  << std::endl;
    }
}

void ContactManager::searchContact(const std::string& name,
                                   Option option) const {
    std::vector<Contact>::const_iterator resBegin = contacts_.begin();
    std::vector<Contact>::const_iterator resEnd{contacts_.end()};

    while (resBegin != resEnd) {
        resBegin =
            std::find_if(resBegin, contacts_.end(),
                         [&option, &name](const Contact& contact) {
                             if (option == Option::FirstName) {
                                 if (contact.firstName.compare(name) == 0) {
                                     return true;
                                 } else {
                                     return false;
                                 }
                             } else {
                                 if (contact.lastName.compare(name) == 0) {
                                     return true;
                                 } else {
                                     return false;
                                 }
                             }
                         });

        if (resBegin != resEnd) {
            std::cout << *resBegin << std::endl;
            ++resBegin;
        }
    }
}

struct ContactHashFunc {
    std::size_t operator()(const Contact& c) const {
        return std::hash<std::string>()(c.company) ^
               std::hash<Group>()(c.group);
    }
};

struct ContactEqualFunc {
    std::size_t operator()(const Contact& c1, const Contact& c2) const {
        return (c1.company == c2.company) && (c1.group == c2.group);
    }
};

void ContactManager::displayCountOfContacts() {
    std::unordered_map<Contact, int, ContactHashFunc, ContactEqualFunc> countMap{};
    std::for_each(contacts_.begin(), contacts_.end(),
                  [&countMap](const Contact& contact) {
                      if (countMap.find(contact) != countMap.end()) {
                          countMap[contact]++;
                      } else {
                          countMap[contact] = 1;
                      }
                  });

    std::string groupInfo{};
    for (const auto& eleInfo : countMap) {
        switch (eleInfo.first.group) {
            case Group::Friends:
                groupInfo = "Friends";
                break;
            case Group::Family:
                groupInfo = "Family";
                break;
            case Group::Coworker:
                groupInfo = "Coworker";
                break;
            case Group::Acquaintance:
                groupInfo = "Acquaintance";
                break;
            default:
                groupInfo = "Err Wrong group";
                break;
        }

        std::cout << eleInfo.first.company << " " << groupInfo << " "
                  << "has " << eleInfo.second << " person.." << std::endl;
    }
}