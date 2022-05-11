#ifndef _CONTACT_MANAGER_H_
#define _CONTACT_MANAGER_H_
#include "contact.h"

#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>
#include <unordered_map>

enum class Option {
    FirstName,
    LastName
};

class ContactManager {
    std::vector<Contact> contacts_;

    public:
        ContactManager(const std::vector<Contact>& contacts);
        ContactManager(std::vector<Contact>&& contacts);
        void displaySortedContact(Option option=Option::FirstName);
        void displayFirstNameWithPrimaryNumber() const;
        void displayContactsFromACompany(const std::string& company) const;
        void displayContactsOnGroupType();
        void searchContact(const std::string& name, Option option=Option::FirstName) const;
        void displayCountOfContacts();
};

#endif