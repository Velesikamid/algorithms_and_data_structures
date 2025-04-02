#include <iostream>

template <class T>
class BinarySearchTree
{
private:
    struct Node
    {
        T _key;
        int _height;
        Node *_left;
        Node *_right;

        Node(T key) : _key(key), _height(1), _left(nullptr), _right(nullptr) {}
    };

    Node *_root;

    int getHeight(Node* node) {
        if (!node) return 0;
        return node->_height;
    }

    int getBalance(Node* node) {
        if (!node) return 0;
        return getHeight(node->_left) - getHeight(node->_right);
    }

    void updateHeight(Node* node) {
        node->_height = std::max(getHeight(node->_left), getHeight(node->_right)) + 1;
    }

    Node* rotateLeft(Node* node) {
        Node* pivot = node->_right;
        node->_right = pivot->_left;
        pivot->_left = node;
        updateHeight(node);
        updateHeight(pivot);
        return pivot;
    }

    Node* rotateRight(Node* node) {
        Node* pivot = node->_left;
        node->_left = pivot->_right;
        pivot->_right = node;
        updateHeight(node);
        updateHeight(pivot);
        return pivot;
    }

    Node* rebalance(Node* node) {
        int balance = getBalance(node);
        if(balance > 1) {
            if (getBalance(node->_left) >= 0) return rotateRight(node);
            else {
                node->_left = rotateLeft(node->_left);
                return rotateRight(node);
            }
        }
        if (balance < -1) {
            if (getBalance(node->_right) <= 0) return rotateLeft(node);
            else {
                node->_right = rotateRight(node->_right);
                return rotateLeft(node);
            }
        }
        return node;
    }

    Node *copyTree(Node *node) const
    {
        if (!node)
            return nullptr;
        Node *newNode = new Node(node->_key);
        newNode->_left = copyTree(node->_left);
        newNode->_right = copyTree(node->_right);
        return newNode;
    }
    void deleteTree(Node *node)
    {
        if (node)
        {
            deleteTree(node->_left);
            deleteTree(node->_right);
            delete node;
        }
    }

    void printHelper(Node *node) const
    {
        if (node)
        {
            printHelper(node->_left);
            std::cout << node->_key << " ";
            printHelper(node->_right);
        }
    }
    bool insertHelper(Node *node, T key)
    {
        if (!node)
            return true;
        if (node->_key == key)
            return false;
        if (key < node->_key)
        {
            if (!node->_left)
            {
                node->_left = new Node(key);
                updateHeight(node);
                node = rebalance(node);
                return true;
            }
            return insertHelper(node->_left, key);
        }
        else
        {
            if (!node->_right)
            {
                node->_right = new Node(key);
                updateHeight(node);
                node = rebalance(node);
                return true;
            }
            return insertHelper(node->_right, key);
        }
    }
    bool containsHelper(Node *node, T key) const
    {
        if (!node)
            return false;
        if (node->_key == key)
            return true;
        if (key < node->_key)
            return containsHelper(node->_left, key);
        return containsHelper(node->_right, key);
    }
    bool eraseHelper(Node *&node, T key)
    {
        if (!node)
            return false;
        if (key < node->_key)
            return eraseHelper(node->_left, key);
        else if (key > node->_key)
            return eraseHelper(node->_right, key);
        else
        {
            if (!node->_left && !node->_right)
            {
                delete node;
                node = nullptr;
            }
            else if (!node->_left)
            {
                Node *temp = node;
                node = node->_right;
                delete temp;
            }
            else if (!node->_right)
            {
                Node *temp = node;
                node = node->_left;
                delete temp;
            }
            else
            {
                Node *minNode = findMin(node->_right);
                node->_key = minNode->_key;
                eraseHelper(node->_right, minNode->_key);
            }
            return true;
        }
    }
    Node *findMin(Node *node)
    {
        while (node->_left)
            node = node->_left;
        return node;
    }

public:
    BinarySearchTree() : _root(nullptr) {}
    BinarySearchTree(const BinarySearchTree &other) : _root(copyTree(other._root)) {}
    BinarySearchTree &operator=(const BinarySearchTree &other)
    {
        if (this != &other)
        {
            deleteTree(_root);
            _root = copyTree(other._root);
        }
        return *this;
    }
    ~BinarySearchTree()
    {
        deleteTree(_root);
    }

    void print() const
    {
        printHelper(_root);
        std::cout << "\n";
    }
    bool insert(T key)
    {
        if (!_root)
        {
            _root = new Node(key);
            updateHeight(_root);
            _root = rebalance(_root);
            return true;
        }
        return insertHelper(_root, key);
    }
    bool contains(T key) const
    {
        return containsHelper(_root, key);
    }
    bool erase(T key)
    {
        return eraseHelper(_root, key);
    }

    class Iterator {
    private:
        Node* _current;
        Node* _root;

        Node* nextInOrder(Node* node) {
            if (node->_right) {
                Node* temp = node->_right;
                while (temp->_left) temp = temp->_left;
                return temp;
            }
            Node* parent = getParent(node);
            while (parent && node == parent->_right) {
                node = parent;
                parent = getParent(node);
            }
            return parent;
        }

        Node* getParent(Node* node) {
            if (node == _root) return nullptr;
            Node* parent = _root;
            while (parent->_left != node && parent->_right != node) {
                if (node->_key < parent->_key) parent = parent->_left;
                else parent = parent->_right;
            }
            return parent;
        }
    
    public:
        Iterator(Node* node, Node* root) : _current(node), _root(root) {}

        int operator*() const {
            return _current->_key;
        }

        Iterator& operator++() {
            _current = nextInOrder(_current);
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return _current != other._current;
        }
    };

    Iterator begin() {
        return Iterator(findMin(_root), _root);
    }

    Iterator end() {
        return Iterator(nullptr, _root);
    }
};

template <class T>
class BinarySearchTreeWithDuplicates
{
private:
    struct Node
    {
        T _key;
        int _count;
        Node *_left;
        Node *_right;

        Node(T key) : _key(key), _count(1), _left(nullptr), _right(nullptr) {}
    };

    Node *_root;

    Node *copyTree(Node *node) const
    {
        if (!node)
            return nullptr;
        Node *newNode = new Node(node->_key);
        newNode->_left = copyTree(node->_left);
        newNode->_right = copyTree(node->_right);
        return newNode;
    }
    void deleteTree(Node *node)
    {
        if (node)
        {
            deleteTree(node->_left);
            deleteTree(node->_right);
            delete node;
        }
    }

    void printHelper(Node *node) const
    {
        if (node)
        {
            printHelper(node->_left);
            for (int i = 0; i < node->_count; ++i)
                std::cout << node->_key << " ";
            printHelper(node->_right);
        }
    }
    bool insertHelper(Node *node, T key)
    {
        if (!node)
            return true;
        if (node->_key == key) {
            ++node->_count;
            return false;
        }
        if (key < node->_key)
        {
            if (!node->_left)
            {
                node->_left = new Node(key);
                return true;
            }
            return insertHelper(node->_left, key);
        }
        else
        {
            if (!node->_right)
            {
                node->_right = new Node(key);
                return true;
            }
            return insertHelper(node->_right, key);
        }
    }
    bool containsHelper(Node *node, T key) const
    {
        if (!node)
            return false;
        if (node->_key == key)
            return true;
        if (key < node->_key)
            return containsHelper(node->_left, key);
        return containsHelper(node->_right, key);
    }
    bool eraseHelper(Node *&node, T key)
    {
        if (!node)
            return false;
        if (key < node->_key)
            return eraseHelper(node->_left, key);
        else if (key > node->_key)
            return eraseHelper(node->_right, key);
        else
        {
            if (!node->_left && !node->_right)
            {
                delete node;
                node = nullptr;
            }
            else if (!node->_left)
            {
                Node *temp = node;
                node = node->_right;
                delete temp;
            }
            else if (!node->_right)
            {
                Node *temp = node;
                node = node->_left;
                delete temp;
            }
            else
            {
                Node *minNode = findMin(node->_right);
                node->_key = minNode->_key;
                eraseHelper(node->_right, minNode->_key);
            }
            return true;
        }
    }
    Node *findMin(Node *node)
    {
        while (node->_left)
            node = node->_left;
        return node;
    }

public:
    BinarySearchTreeWithDuplicates() : _root(nullptr) {}
    BinarySearchTreeWithDuplicates(const BinarySearchTreeWithDuplicates &other) : _root(copyTree(other._root)) {}
    BinarySearchTreeWithDuplicates &operator=(const BinarySearchTreeWithDuplicates &other)
    {
        if (this != &other)
        {
            deleteTree(_root);
            _root = copyTree(other._root);
        }
        return *this;
    }
    ~BinarySearchTreeWithDuplicates()
    {
        deleteTree(_root);
    }

    void print() const
    {
        printHelper(_root);
        std::cout << "\n";
    }
    bool insert(T key)
    {
        if (!_root)
        {
            _root = new Node(key);
            return true;
        }
        return insertHelper(_root, key);
    }
    bool contains(T key) const
    {
        return containsHelper(_root, key);
    }
    bool erase(T key)
    {
        return eraseHelper(_root, key);
    }
};

template <class T>
bool is_include(BinarySearchTree<T>& tree1, BinarySearchTree<T>& tree2) {
    bool result = true;
    int count1 = 0, count2 = 0;
    for (auto key : tree1) ++count1;
    for (auto key : tree2) ++count2;
    if (count1 <= count2) {
        for (auto key : tree1) {
            if (!tree2.contains(key)) result = false;
        }
    } else {
        for (auto key : tree2) {
            if (!tree1.contains(key)) result = false;
        }
    }
    return result;
}