/**
 * Binary tree class.
 *
 * Note that there is no treebin.cc file, because a template class must
 * be completely defined in its .h file.
 */
template <typename E>
class TreeBin {
  public:

    /* Public child class defines tree node. */
    class Node {
      public:
        /* Construct a node containing value. */
        Node(E value) : _value(value), _left(nullptr), _right(nullptr),
            _parent(nullptr) { };

        /* Destructor deletes this node and all its descendants. */
        ~Node() {
            if (_left != nullptr) { delete _left; }
            if (_right != nullptr) { delete _right; }
        }

        /* Big 3: don't allow default copy constructor or operator=.
         * In other terms, this is a non-copyable class.  See
         * https://google.github.io/styleguide/cppguide.html#Copyable_Movable_Types
         * for further explanation.
         */
        Node(const Node&) = delete;
        Node& operator=(const Node&) = delete;

        /* Accessors */
        E value() const { return _value; };
        void setValue(E value) { _value = value; };
        TreeBin<E>::Node* left() const {return _left; };
        TreeBin<E>::Node* right() const {return _right; };
        TreeBin<E>::Node* parent() const {return _parent; };

        // Return true iff the node is the root
        bool isRoot() const { return _parent == nullptr; };

        // Return truee iff the node is a leaf
        bool isLeaf() const {
            return _left == nullptr && _right == nullptr;
        };

        /* Create a new node with value E and add it as the left (right) child.
         * It is a fatal error to call this if there is already a left (right)
         * child.
         */
        void addLeft(E value) {
            if (_left != nullptr) {
                std::cerr << "Error: TreeBin::Node::addLeft() called with " <<
                    "left != nullptr (" << _left << ")\n";
                exit(-1);
            } else {
                _left = new Node(value);
                _left->_parent = this;
            }
        };

        void addRight(E value) {
            if (_right != nullptr) {
                std::cerr << "Error: TreeBin::Node::addRight() called with " <<
                    "right != nullptr (" << _right << ")\n";
                exit(-1);
            } else {
                _right = new Node(value);
                _right->_parent = this;
            }
        };


      private:
        E _value;
        Node *_left;
        Node *_right;
        Node *_parent;
    };

    /* Create an empty TreeBin */
    TreeBin() : _root(NULL) {};

    /* Delete the TreeBin and all its nodes. */
    ~TreeBin() { delete _root; };

    /* Big 3: don't allow default copy constructor or operator=.
     * In other terms, this is a non-copyable class.  See
     * https://google.github.io/styleguide/cppguide.html#Copyable_Movable_Types
     * for further explanation.
     */
    TreeBin(const TreeBin&) = delete;
    TreeBin& operator=(const TreeBin&) = delete;

    /* Return pointer to root node, or nullptr if there is no root. */
    TreeBin::Node * root() const { return _root; };

    /** Create a root node in an empty tree.  Fatal error if tree is
     * not empty.
     * @param value Value to put in new root node
     */
    void addRoot(E value) { _root = new Node(value); };

    bool empty() const { return _root == nullptr; };

    typedef void (*visitorFunction)(Node *);

    /* Traverse tree in "pre-order" order, meaning visit the root,
     * then its left subtree, then its right subtree.  Call the
     * "visitor" function on each node, with the node. as its
     * argument.
     */
    void preOrder(visitorFunction visitor) { preOrderNode(visitor, _root); };

    /* Traverse tree in "in-order" order, meaning visit the left
     * sub-tree, then the root, then the right subtree.  Call the
     * "visitor" function on each node, with the node. as its
     * argument.
     */
    void inOrder(visitorFunction visitor) { inOrderNode(visitor, _root); };

    /* Traverse tree in "post-order" order, meaning visit the left
     * subtree, then the right subtree, then the root.  Call the
     * "visitor" function on each node, with the node. as its
     * argument.
     */
    void postOrder(visitorFunction visitor) { postOrderNode(visitor, _root); };


  private:
    /* Do the work of preOrder/inOrder/postOrder for the subtree
     * rooted at node.
     */
    void preOrderNode(visitorFunction visitor, Node *node);
    void inOrderNode(visitorFunction visitor, Node *node);
    void postOrderNode(visitorFunction visitor, Node *node);

    Node *_root;
};

template <typename E>
void TreeBin<E>::preOrderNode(visitorFunction visitor, TreeBin<E>::Node *node) {
    if (node != nullptr) {
        visitor(node);
        preOrderNode(visitor, node->left());
        preOrderNode(visitor, node->right());
    }
}

template <typename E>
void TreeBin<E>::inOrderNode(visitorFunction visitor, TreeBin<E>::Node *node) {
    if (node != nullptr) {
        inOrderNode(visitor, node->left());
        visitor(node);
        inOrderNode(visitor, node->right());
    }
}

template <typename E>
void TreeBin<E>::postOrderNode(visitorFunction visitor, TreeBin<E>::Node *node) {
    if (node != nullptr) {
        postOrderNode(visitor, node->left());
        postOrderNode(visitor, node->right());
        visitor(node);
    }
}
