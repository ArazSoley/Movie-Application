#include <string>
#include <vector>
#include <iostream>
#include <utility>
#include <algorithm>
using namespace std;

// do not add any other library.

template <class T>
class BST {
private:
    // Define TreeNode for the second phase (Binary Search Tree)
    /* DO NOT CHANGE */
    struct TreeNode {
        std::string key;
        T data;
        TreeNode* left;
        TreeNode* right;
        TreeNode(const std::string &k, const T& value) : key(k), data(value), left(NULL), right(NULL) {}
        
    };

    TreeNode* root;


public: // Do not change.

    BST();
    ~BST();
    TreeNode* getRoot() { return root; }
    bool isEmpty() { return root == NULL; }

    BST& insert(const std::string key, const T& value);
    bool search(std::string value) const;
    void remove(std::string value);
    BST<T>* merge(BST<T>* bst);
    BST<T>* intersection(BST<T>* bst);
    std::vector<TreeNode> tree2vector(TreeNode* root);
    void print();
    
private:// you may add your own utility member functions here.

    void print(TreeNode* node, std::string indent, bool last, bool isLeftChild); // Do not change.
    void deleteNode(TreeNode *node);
    void insert(const std::string key, const T &value, TreeNode *node);
    bool search(std::string key, TreeNode *node) const;
    void remove(std::string key, TreeNode *&node);
    void tree2vector(TreeNode *node, std::vector<TreeNode> &result);
};

// Constructor
template <class T>
BST<T>::BST() : root(NULL) {}

// Destructor
template <class T>
BST<T>::~BST() 
{
    deleteNode(root);
}

template<class T>
void BST<T>::deleteNode(TreeNode *node)
{
    if (!node)
        return;
    deleteNode(node -> left);
    deleteNode(node -> right);
    delete node;
}

// Insert function for BST.    
template <class T>
BST<T>& BST<T>::insert(const string key, const T& value)
{
    if (!root)
        root = new TreeNode(key, value);
    else
        insert(key, value, root);
    return *this;
}

template<class T>
void BST<T>::insert(const string key, const T &value, TreeNode *node)
{

    if (key >= (node -> key))
    {
        if (node -> right)
            insert(key, value, node -> right);
        else
            node -> right = new TreeNode(key, value);
    }
    else
    {
        if (node -> left)
            insert(key, value, node -> left);
        else
            node -> left = new TreeNode(key, value);
    }
}

// Search function for BST.
template <class T>
bool BST<T>::search(std::string value) const 
{
    return search(value, root);
}

template<class T>
bool BST<T>::search(std::string key, TreeNode *node) const
{
    if (!node)
        return false;
    if (node -> key == key)
        return true;
    if (key > node -> key)
        return search(key, node -> right);
    return search(key, node -> left);
}

// Remove a node from BST for given key. If key not found, do not change anything.
template <class T>
void BST<T>::remove(std::string key)
{
    remove(key, root);
}

template<class T>
void BST<T>::remove(std::string key, TreeNode *&node)
{
    if (!(node))
        return;
    if (key > node -> key)
        remove(key, node -> right);
    else if (key < node -> key)
        remove(key, node -> left);
    else
    {
        if (!(node -> left) && !(node -> right))
        {
            delete node;
            node = NULL;
        }
        else if (!(node -> left))
        {
            TreeNode *temp = node -> right;
            delete node;
            node = temp;
        }
        else if (!(node -> right))
        {
            TreeNode *temp = node -> left;
            delete node;
            node = temp;
        }
        else
        {
            TreeNode **rMin, *temp;
            for (rMin = &(node -> right); (*rMin) -> left; rMin = &((*rMin) -> left));
            node -> key = (*rMin) -> key;
            node -> data = (*rMin) -> data;
            temp = (*rMin) -> right;
            delete *rMin;
            *rMin = temp;
        }
    }
}

// A helper function for converting a BST into vector.
template <class T>
vector<typename BST<T>::TreeNode> BST<T>::tree2vector(TreeNode* root)
{
    vector<TreeNode> result;
    tree2vector(root, result);
    return result;
}

template<class T>
void BST<T>::tree2vector(TreeNode *node, vector<TreeNode> &result)
{
    if (!node)
        return;
    tree2vector(node -> left, result);
    result.push_back(*node);
    tree2vector(node -> right, result);
}

// Merge two BST's and return merged BST.
template <class T>
BST<T>* BST<T>::merge(BST<T>* bst)
{
    vector<TreeNode> v1 = tree2vector(root);
    vector<TreeNode> v2 = tree2vector(bst -> root);
    size_t size1 = v1.size(), size2 = v2.size(), i1, i2;

    for (i1 = 0, i2 = 0; i1 < size1 && i2 < size2;)
    {
        if (v2[i2].key < v1[i1].key)
        {
            v1.insert(v1.begin() + i1, v2[i2]);
            i2++;
            i1++;
            size1++;
        }
        else if (v2[i2].key == v1[i1].key)
            i2++;
        else
            i1++;
    }
    for (; i2 < size2; i2++)
        v1.push_back(v2[i2]);
    BST<T> *resBST = new BST<T>;
    for (i1 = 0, size1 = v1.size(); i1 < size1; i1++)
        (*resBST).insert(v1[i1].key, v1[i1].data);
    return resBST;
}
    
// Intersect two BST's and return new BST.
template <class T>
BST<T>* BST<T>::intersection(BST<T>* bst)
{
    vector<TreeNode> v1 = tree2vector(root);
    vector<TreeNode> v2 = tree2vector(bst -> root);
    vector<TreeNode> res;
    size_t size1 = v1.size(), size2 = v2.size(), i1, i2;

    for (i1 = 0, i2 = 0; i1 < size1 && i2 < size2;)
    {
        if (v2[i2].key < v1[i1].key)
            i2++;
        else if (v2[i2].key > v1[i1].key)
            i1++;
        else
        {
            res.push_back(v1[i1]);
            i1++;
            i2++;
        }
    }

    BST<T> *resBST = new BST<T>;
    for (size_t i = 0, size = res.size(); i < size; i++)
        (*resBST).insert(res[i].key, res[i].data);
    return resBST;
}

/* DO NOT CHANGE */
template <class T>
void BST<T>::print() {
    print(root, "", true, false);

}

/* DO NOT CHANGE */
template <class T>
void BST<T>::print(TreeNode* node, string indent, bool last, bool isLeftChild) {
    if (node != NULL) {
        cout << node->key << endl;
        print(node->left, indent, false, true);
        print(node->right, indent, true, false);
    }

}


