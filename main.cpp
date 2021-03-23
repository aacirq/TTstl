#include <iostream>
#include <vector>
#include <list>

#include <gtest/gtest.h>

// #include "unittest/bst_unittest.hpp"
#include "binary_search_tree/bst.hpp"

// class BstTest : ::testing::Test {

// }

using namespace tt;
// using namespace std;

// TODO 将测试代码单独放在一个文件内，每个hpp包的测试代码单独放起来

TEST(BstBasicTest, EmptyTree) {
    BST<int> tree;
    ASSERT_EQ(tree.get_root(), nullptr);
}

TEST(BstBasicTest, InsertOneValueToEmptyTree) {
    BST<int> tree;
    tree.insert(1);
    ASSERT_NE(tree.get_root(), nullptr);
    ASSERT_EQ(tree.get_root()->left, nullptr);
    ASSERT_EQ(tree.get_root()->right, nullptr);
}

class BstTreeTest : public ::testing::Test {
    //                            5
    //                          /   \\
    //                        3      8
    //                       / \    / \\
    //                      1  4   7  9
    //                       \    /
    //                        2  6
    protected:
    void SetUp() override {
        for (auto i : { 5, 3, 1, 2, 4, 8, 7, 6, 9 })
            tree.insert(i);
    }

    BST<int> tree;
};

TEST_F(BstTreeTest, CheckAllNodesInThisTree) {
    BstNode<int> *node = tree.get_root();
    ASSERT_NE(node, nullptr);
    // left subtree
    EXPECT_EQ(node->key, 5);
    ASSERT_NE(node->left, nullptr);
    EXPECT_EQ(node->left->key, 3);
    ASSERT_NE(node->left->left, nullptr);
    EXPECT_EQ(node->left->left->key, 1);
    ASSERT_EQ(node->left->left->left, nullptr);
    ASSERT_NE(node->left->left->right, nullptr);
    EXPECT_EQ(node->left->left->right->key, 2);
    ASSERT_EQ(node->left->left->right->left, nullptr);
    ASSERT_EQ(node->left->left->right->right, nullptr);
    ASSERT_NE(node->left->right, nullptr);
    EXPECT_EQ(node->left->right->key, 4);
    ASSERT_EQ(node->left->right->left, nullptr);
    ASSERT_EQ(node->left->right->right, nullptr);

    // right subtree
    ASSERT_NE(node->right, nullptr);
    EXPECT_EQ(node->right->key, 8);
    ASSERT_NE(node->right->left, nullptr);
    EXPECT_EQ(node->right->left->key, 7);
    ASSERT_NE(node->right->left->left, nullptr);
    EXPECT_EQ(node->right->left->left->key, 6);
    ASSERT_EQ(node->right->left->left->left, nullptr);
    ASSERT_EQ(node->right->left->left->right, nullptr);
    ASSERT_NE(node->right->right, nullptr);
    EXPECT_EQ(node->right->right->key, 9);
    ASSERT_EQ(node->right->right->left, nullptr);
    ASSERT_EQ(node->right->right->right, nullptr);
}

TEST_F(BstTreeTest, Minimum) {
    BST<int> tmp_tree;
    EXPECT_EQ(tmp_tree.minimum(), nullptr);
    EXPECT_EQ(tree.minimum(nullptr), nullptr);
    EXPECT_EQ(tree.minimum()->key, 1);
    EXPECT_EQ(tree.minimum(tree.get_root()->right)->key, 6);
    EXPECT_EQ(tree.minimum(tree.get_root()->right->right)->key, 9);
}

TEST_F(BstTreeTest, Maximum) {
    BST<int> tmp_tree;
    EXPECT_EQ(tmp_tree.maximum(), nullptr);
    EXPECT_EQ(tree.maximum(nullptr), nullptr);
    EXPECT_EQ(tree.maximum()->key, 9);
    EXPECT_EQ(tree.maximum(tree.get_root()->left)->key, 4);
    EXPECT_EQ(tree.maximum(tree.get_root()->left->right)->key, 4);
}

TEST_F(BstTreeTest, Search) {
    for (auto i : { 1, 2, 3, 4, 5, 6, 7, 8, 9 }) {
        auto node = tree.search(i);
        ASSERT_NE(node, nullptr) << "i = " << i;
        EXPECT_EQ(node->key, i);
    }
}

TEST_F(BstTreeTest, Predecessor) {
    EXPECT_EQ(tree.predecessor(nullptr), nullptr);
    for (auto i : {2, 3, 4, 5, 6, 7, 8, 9})
        EXPECT_EQ(tree.predecessor(tree.search(i)), tree.search(i - 1)) \
            << "i =  " << i;
    EXPECT_EQ(tree.predecessor(tree.search(1)), nullptr);
}

TEST_F(BstTreeTest, Successor) {
    EXPECT_EQ(tree.successor(nullptr), nullptr);
    for (auto i : { 1, 2, 3, 4, 5, 6, 7, 8 })
        EXPECT_EQ(tree.successor(tree.search(i)), tree.search(i + 1)) \
            << "i = " << i;
    EXPECT_EQ(tree.successor(tree.search(9)), nullptr);
}

TEST_F(BstTreeTest, InorderWalk) {
    int i = 1;
    tree.inorder_walk([&i](int &v) { EXPECT_EQ(i, v); ++i ; });
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
