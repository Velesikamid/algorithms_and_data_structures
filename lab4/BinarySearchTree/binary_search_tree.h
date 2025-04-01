#include <iostream>

template <class T>
class BinarySearchTree
{
private:
    struct Node
    {
        T _key;
        Node *_left;
        Node *_right;

        Node(T key) : _key(key), _left(nullptr), _right(nullptr) {}
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
        if (node->_key == key)
            ++node->_count;
        return false;
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