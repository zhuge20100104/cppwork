#ifndef _FREDRIC_BOOST_ITERATOR_FACADE_HPP_
#define _FREDRIC_BOOST_ITERATOR_FACADE_HPP_

#include <boost/iterator/iterator_facade.hpp>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

// 单链表及其迭代器类实现
struct Node {
    std::string value;
    Node* next{nullptr};
    Node(std::string const& value_): value(value_) {}
    Node(std::string const& value_, Node* parent): value(value_) {
        parent->next = this;
    }
};

struct ListIterator: boost::iterator_facade<ListIterator, Node, boost::forward_traversal_tag> {
    Node* current {nullptr};
    ListIterator() {}
    ListIterator(Node* current_): current(current_) {}

private:
    friend class boost::iterator_core_access;

    void increment() {
        current = current->next;
    }

    bool equal(ListIterator const& other) const {
        return current == other.current;
    }

    Node& dereference() const {
        return *current;
    }
};
#endif