#include "contact_manager.h"


int main(int argc, char* argv[]) {
    std::vector<Contact> contacts {
        Contact {"San", "Zhang", "17316289999", "17316288888", "zhangsan@gmail.com", "ShenzhenFutian", "ST", Group::Friends},
        Contact {"Si", "Li", "13928276666", "13828275555", "lisi@gmail.com", "BeijingChaoyang", "KS", Group::Coworker},
        Contact {"Liu", "Zhao", "17316277779", "17516285688", "zhaoliu@gmail.com", "SanyaYalongwan", "ST", Group::Friends},
        Contact {"Liu", "Wang", "13828272222", "13628275567", "wangwu@gmail.com", "BeijingHaidian", "KS", Group::Coworker},
    };

    ContactManager cm {std::move(contacts)};
    std::cout << "Display sorted by firstName.." << std::endl;
    cm.displaySortedContact();
    std::cout << std::endl;
    
    std::cout << "Display sorted by lastName.." << std::endl;
    cm.displaySortedContact(Option::LastName);
    std::cout << std::endl;

    std::cout << "Display only firstName with primary Number.." << std::endl;
    cm.displayFirstNameWithPrimaryNumber();
    std::cout << std::endl;

    std::cout << "Display contacts from a company.." << std::endl;
    cm.displayContactsFromACompany("ST");
    std::cout << std::endl;

    std::cout << "Display contacts based on group type.." << std::endl;
    cm.displayContactsOnGroupType();
    std::cout << std::endl;
    
    std::cout << "Search contacts by first name.." << std::endl;
    cm.searchContact("Liu", Option::FirstName);
    std::cout << std::endl;

    std::cout << "Search contacts by last name.." << std::endl;
    cm.searchContact("Zhang", Option::LastName);
    std::cout << std::endl;

    std::cout << "Display count of contacts by company and group..." << std::endl;
    cm.displayCountOfContacts();
    std::cout << std::endl;
    return 0;
}