#include <iostream>
#include "tree_bin.h"
using std::cout;
using std::endl;

void visitor(TreeBin<int>::Node *node) {
    cout << node->value() << " ";
}

int main(int argc, char *argv[]) {
    TreeBin<int> t;

    /* Create this tree
     *         1
     *       /  \
     *      2    3
     *     /    / \
     *    4    6   7
     *              \
     *               8
     */
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

    cout << t.root()->right()->left()->value() << endl; // 6

    cout << "Pre-order: " << endl;
    t.preOrder(visitor);               // 1 2 4 3 6 7 8
    cout << endl;
    cout << "In-order: " << endl;
    t.inOrder(visitor);                // 4 2 1 6 3 7 8
    cout << endl;
    cout << "Post-order: " << endl;
    t.postOrder(visitor);              // 4 2 6 8 7 3 1
    cout << endl;
}
