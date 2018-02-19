// Tests for TreeBin template class
//
// Copyright 2018, Russ Tuck, Gordon College

#include "gtest/gtest.h"
#include <iostream>
using std::cout;
using std::endl;

#include "tree_bin.h"

TEST(tree_bin, empty) {
    TreeBin<int> t;

    EXPECT_TRUE(t.empty());
    EXPECT_EQ(t.root(), nullptr);
}

TEST(tree_bin, oneNode) {
    TreeBin<int> t;
    t.addRoot(1);
    EXPECT_FALSE(t.empty());
    EXPECT_NE(t.root(), nullptr);
    EXPECT_TRUE(t.root()->isRoot());
    EXPECT_EQ(t.root()->value(), 1);
    EXPECT_EQ(t.root()->left(), nullptr);
    EXPECT_EQ(t.root()->right(), nullptr);
    EXPECT_EQ(t.root()->parent(), nullptr);
}

TEST(tree_bin, twoNodeLeft) {
    TreeBin<int> t;
    t.addRoot(1);
    TreeBin<int>::Node *root = t.root();
    root->addLeft(2);
    TreeBin<int>::Node *left = root->left();
    EXPECT_FALSE(root->isLeaf());
    EXPECT_TRUE(left->isLeaf());
    EXPECT_FALSE(left->isRoot());
    EXPECT_EQ(left->value(), 2);
    EXPECT_EQ(left->left(), nullptr);
    EXPECT_EQ(left->right(), nullptr);
    EXPECT_EQ(left->parent(), root);
}

TEST(tree_bin, twoNodeRight) {
    TreeBin<int> t;
    t.addRoot(1);
    TreeBin<int>::Node *root = t.root();
    root->addRight(3);
    TreeBin<int>::Node *right = root->right();
    EXPECT_FALSE(root->isLeaf());
    EXPECT_TRUE(right->isLeaf());
    EXPECT_FALSE(right->isRoot());
    EXPECT_EQ(right->value(), 3);
    EXPECT_EQ(right->left(), nullptr);
    EXPECT_EQ(right->right(), nullptr);
    EXPECT_EQ(right->parent(), root);
}

TEST(tree_bin, sevenNode) {
    /* Create this tree
     *         1
     *       /  \
     *      2    3
     *     /    / \
     *    4    6   7
     *              \
     *               8
     */
    TreeBin<int> t;
    t.addRoot(1);
    TreeBin<int>::Node *root = t.root();
    root->addLeft(2);
    root->addRight(3);
    TreeBin<int>::Node *left = root->left();
    TreeBin<int>::Node *right = root->right();
    left->addLeft(4);
    right->addLeft(6);
    right->addRight(7);
    right->right()->addRight(8);

    EXPECT_TRUE(root->isRoot());
    EXPECT_EQ(root->value(), 1);
    EXPECT_EQ(root->left(), left);
    EXPECT_EQ(left->value(), 2);
    EXPECT_EQ(root->right(), right);
    EXPECT_EQ(right->value(), 3);
    EXPECT_EQ(left->left()->value(), 4);
    EXPECT_EQ(left->right(), nullptr);
    EXPECT_EQ(right->left()->value(), 6);
    EXPECT_EQ(right->left()->left(), nullptr);
    EXPECT_EQ(right->left()->right(), nullptr);
    EXPECT_EQ(right->right()->value(), 7);
    EXPECT_EQ(right->right()->left(), nullptr);
    EXPECT_EQ(right->right()->right()->value(), 8);
    EXPECT_EQ(right->right()->right()->left(), nullptr);
    EXPECT_EQ(right->right()->right()->right(), nullptr);
}

/* TODO: create visitor to enable unit testing of traversals.
 */
