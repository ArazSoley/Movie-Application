#include <iostream>
#include <string>
#include <vector>
#include <utility>
using namespace std;


template <class T>
class Trie {    
private:
    // Define TrieNode for the first phase (Trie)
    /* DO NOT CHANGE */
    struct TrieNode {
        static const int ALPHABET_SIZE = 128;
        TrieNode* children[ALPHABET_SIZE];
        char keyChar;
        bool isEndOfKey;
        T* data;

        TrieNode(char c) : keyChar(c), isEndOfKey(false), data(NULL) {

                for (int i = 0; i< ALPHABET_SIZE; i++) {
                children[i] = NULL;
                
            }
            
            }
    };

    TrieNode* root;

public: // Do not change.

    Trie(); 
    ~Trie();
    
    Trie& insert(const string& username); 
    void remove(std::string username);
    T* search(std::string username); 
    void findStartingWith(std::string prefix, std::vector<T*> &results); 
    void wildcardSearch(const std::string &wildcardKey, std::vector<T*> &results); 
    void print(); 

private: // you may add your own utility member functions here.
    void print(const std::string& primaryKey); // Do not change this line.
    void printTrie(TrieNode* node, const std::string& currentKey); // Do not change this line.
    void deleteTrieNode(TrieNode *node);
    void wildcardSearch(const std::string &wildcardKey, std::vector<TrieNode*> &results, TrieNode *node);
    void insert(const string& key, TrieNode *node, const string& fullKey);
    
};
/* DO NOT CHANGE */
template <class T>
Trie<T>::Trie() : root(new TrieNode('\0')) {}

template <class T>
Trie<T>::~Trie() {
    deleteTrieNode(root);
}

template <class T>
void Trie<T>::deleteTrieNode(TrieNode *node)
{
    int i = 0, size;
    TrieNode **temp;
    for (i = 0, size = node -> ALPHABET_SIZE, temp = node -> children; i < size; i++, temp++)
        if (*temp)
            deleteTrieNode(*temp);
    delete node -> data;
    delete node;
}

template <class T>
void Trie<T>::insert(const string& key, TrieNode *node, const string& fullKey)
{
    if (key.empty())
    {
        if (!(node -> isEndOfKey))
        {
            node -> isEndOfKey = true;
            node -> data = new T(fullKey);
        }
        return;
    }
    if (!((node -> children)[key[0]]))
        (node -> children)[key[0]] = new TrieNode(key[0]);
    insert(key.substr(1, key.size() - 1), (node -> children)[key[0]], fullKey);
}

template <class T>
Trie<T>& Trie<T>::insert(const string& key) {
    insert(key, root, key);
    return *this;
}

template <class T>
T* Trie<T>::search(std::string username) {
    vector<TrieNode*> result;
    wildcardSearch(username, result, root);
    if (!result.empty())
        return result[0] -> data;
    return NULL;
}

template <class T>
void Trie<T>::remove(std::string username)
{
    vector<TrieNode*> result;
    wildcardSearch(username, result, root);
    if (!result.empty())
    {
        result[0] -> isEndOfKey = false;
        delete result[0] -> data;
        result[0] -> data = NULL;
    }
}

template <class T>
void Trie<T>::findStartingWith(string prefix,vector<T*> &results)
{
    vector<TrieNode*> tempVec;
    wildcardSearch(prefix + string("*"), tempVec, root);
    for (int i = 0, size = tempVec.size(); i < size; i++)
        results.push_back(tempVec[i] -> data);
}

template <class T>
void Trie<T>::wildcardSearch(const std::string &wildcardKey, std::vector<TrieNode*> &results, TrieNode *node)
{
    if (wildcardKey.empty())
    {
        if (node -> isEndOfKey)
        {
            for (size_t i = 0, size = results.size(); i < size; i++)
                if (results[i] == node)
                    return;
            results.push_back(node);
        }
        return;
    }

    if (wildcardKey[0] == '*')
        wildcardSearch(wildcardKey.substr(1, wildcardKey.size() - 1), results, node);
        
    if (wildcardKey[0] == '*')
    {
        int i = 0, size;
        TrieNode **temp;
        for (i = 0, size = node -> ALPHABET_SIZE, temp = node -> children; i < size; i++, temp++)
            if (*temp)
                wildcardSearch(wildcardKey, results, *temp);
    }
    if ((wildcardKey[0] == '*') || (wildcardKey[0] == '?'))
    {
        int i = 0, size;
        TrieNode **temp;
        for (i = 0, size = node -> ALPHABET_SIZE, temp = node -> children; i < size; i++, temp++)
            if (*temp)
                wildcardSearch(wildcardKey.substr(1, wildcardKey.size() - 1), results, *temp);
    }
    
    if ((wildcardKey[0] != '*') && (wildcardKey[0] != '?') &&  (node -> children)[wildcardKey[0]])
        wildcardSearch(wildcardKey.substr(1, wildcardKey.size() - 1), results, (node -> children)[wildcardKey[0]]);

}


template <class T>
void Trie<T>::wildcardSearch(const std::string &wildcardKey, std::vector<T*> &results) 
{
    vector<TrieNode*> tempVec;
    wildcardSearch(wildcardKey, tempVec, root);
    for (int i = 0, size = tempVec.size(); i < size; i++)
        results.push_back(tempVec[i] -> data);
}

/* DO NOT CHANGE */
template<class T>
void Trie<T>::print() {
    print("");
}

/* DO NOT CHANGE */
template <class T>
void Trie<T>::print(const std::string& primaryKey) {
    if (primaryKey.empty()) {
        // Print the entire tree.
        printTrie(root, "");
    } else {
        // Print specific keys.
        TrieNode* primaryNode = root;
        for (int i = 0; i < primaryKey.length(); i++) {
            
            int index = primaryKey[i];
            if (!primaryNode->children[index]) {
                std::cout << "{}" << std::endl; // Primary key not found, nothing to print.
                return ;
            }
            primaryNode = primaryNode->children[index];
        }

        }
    }

/* DO NOT CHANGE */
template <class T>
void Trie<T>::printTrie(TrieNode* node, const std::string& currentKey) {
    if (!node) {
        return;
    }
    if (node->isEndOfKey) {
        std::cout << currentKey <<std::endl;
        std::cout << "Watched Movies:" << std::endl;
        if(node->data) {
            node->data->printMovies();
        }
    }
    for (int i = 0; i < 128; ++i) {
        if (node->children[i]) {
            printTrie(node->children[i], currentKey + static_cast<char>(i));
        }
    }
}
