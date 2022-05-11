#ifndef _FREDRIC_BINARY_TREE_ITERATOR_COROUTINE_HPP_
#define _FREDRIC_BINARY_TREE_ITERATOR_COROUTINE_HPP_

#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include <generator/generator>
#include <coroutine>


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

    std::generator<Node<T>*> post_order() {
        return post_order_impl(root);
    }

private:
    std::generator<Node<T>*> post_order_impl(Node<T>* node) {
        // 递归yield 一个node，左右根，后续遍历
        if(node) {
            for(auto x: post_order_impl(node->left)) {
                co_yield x;
            }
            for(auto y: post_order_impl(node->right)) {
                co_yield y;
            }
            co_yield node;
        }
    }
};
#endif