#ifndef _FREDRIC_PERSON_HPP_
#define _FREDRIC_PERSON_HPP_

#include <string>
#include <vector>
#include <concepts>
#include <iostream>
#include <utility>
#include <tuple>

enum class Relationship {
    parent,
    child,
    sibling
};

struct Person {
    std::string name;
};

struct Relationships {
    std::vector<std::tuple<Person, Relationship, Person>> relations;
    void add_parent_and_child(Person const& parent, Person const& child) {
        relations.push_back({parent, Relationship::parent, child});
        relations.push_back({child, Relationship::child, parent});
    }

    std::vector<Person> find_all_children_of(std::string const& name) {
        std::vector<Person> result;
        // std C++17 tuple 遍历新特性
        for(auto&& [first, rel, second]: relations) {
            if(first.name == name && rel == Relationship::parent) {
                result.push_back(second);
            }
        }
        return result;
    }
};

template <typename T>
concept RelationBrowserType = requires (T value) {
    {value.find_all_children_of(std::declval<std::string const&>())} -> std::convertible_to<std::vector<Person>>;
};


// High level usage & analysis
template <RelationBrowserType RelationBrowserT>
struct Research {
    Research(RelationBrowserT& browser){
        for(auto& child: browser.find_all_children_of("John")) {
            std::cout << "John has a child called " << child.name << std::endl;
        }
    }
};

#endif