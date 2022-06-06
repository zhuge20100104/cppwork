#include "obj_creates.hpp"

#include <iostream>
#include <string>

struct Employee {

    Employee(const std::string& name_, int id_, int salary_):
        name{name_},
        id{id_},
        salary{salary_}
     {}
    std::string name{};
    int id{};
    int salary{};
};

struct Contact {
    Contact(const std::string& name_, std::size_t phoneNumber_, const std::string& address_, const std::string& email_):
        name{name_},
        phoneNumber{phoneNumber_},
        address{address_},
        email{email_}
     {}
    std::string name{};
    std::size_t phoneNumber{};
    std::string address{};
    std::string email{};
};

int main(int argc, char* argv[]) {
    auto p1 = CreateObject<int>(5);
    std::cout << "Int object value: " << *p1 << std::endl;
    auto s = CreateObject<std::string>();
    std::cout << "Empty string: " << *s << std::endl;

    auto emp = CreateObject<Employee>("Bob", 101, 1000);
    std::cout << "Employee: " << emp->name << ", " << emp->id << ", " << emp->salary << std::endl;

    auto contact = CreateObject<Contact>("Joey", 987654321, "Chenghua JingYuan, Wuhan", "fzhu@appannie.com");
    std::cout << "Contact: " << contact->name << ", " << contact->phoneNumber << ", " << contact->address << ", " << contact->email << std::endl;

    return 0;
}