#ifndef _FREDRIC_BINARY_TREE_ITERATOR_HPP_
#define _FREDRIC_BINARY_TREE_ITERATOR_HPP_

#include <boost/config/warning_disable.hpp>
#include <boost/foreach.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/variant/recursive_variant.hpp>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

template <typename T>
struct BinaryTree;

template <typename T>
struct Node {
    T value{};

    Node<T>* left{nullptr}, *right{nullptr}, *parent{nullptr};

    BinaryTree<T>* tree{nullptr};

    Node(T value_) : value{value_} {}
    Node(T value_, Node<T>* left_, Node<T>* right_)
        : value(value_), left(left_), right{right_} {
        // 初始化左子节点和右子节点的树为同一颗树
        this->left->tree = this->right->tree = tree;
        // 初始化左子节点和右子节点的父节点为当前节点
        this->left->parent = this->right->parent = this;
    }

    void set_tree(BinaryTree<T>* t) {
        tree = t;
        if (left) left->set_tree(t);
        if (right) right->set_tree(t);
    }

    ~Node() {
        if(left) delete left;
        if(right) delete right;
    } 
};

template <typename T>
struct BinaryTree {
    Node<T>* root{nullptr};
    BinaryTree(Node<T>* root_) : root(root_) {
        root->set_tree(this);
    }

    ~BinaryTree() {
        if(root) {
            delete root;
        }
    }

    // 中序遍历迭代器
    template <typename U>
    struct MidOrderIterator {
        Node<U>* current;

        MidOrderIterator(Node<U>* current_)
            : current{current_} {}

        bool operator!=(MidOrderIterator<U> const& other) {
            return current != other.current;
        }

        // ++ 操作符重载
        MidOrderIterator<U>& operator++() {
            // 如果有右子树，就先转到右子树，然后一直寻找他的左子树
            if (current->right) {
                current = current->right;
                while (current->left) {
                    current = current->left;
                }
            } else {
                // 如果往上走，发现当前节点是右子树，
                // 则一直往上走，直到发现当前节点是p的左子树或根节点为止
                // 最终把p赋值给current，说明当前节点被赋值为根节点
                auto p = current->parent;
                while (p && current == p->right) {
                    current = p;
                    p = p->parent;
                }
                current = p;
            }
            return *this;
        }

        Node<U>& operator*() { return *current; }
    };

    using iterator = MidOrderIterator<T>;
    
    iterator begin() {
        Node<T>* n = root;
        if(n) {
            while(n->left) {
                n = n->left;
            }
        }
        return iterator{n};
    }
    
    iterator end() {
        return iterator{nullptr};
    }
};
#endif