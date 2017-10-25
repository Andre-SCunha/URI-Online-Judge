#include <iostream>
#include <list>

    using namespace std;

struct TrieNode;
struct Trie;
typedef TrieNode* pTrieNode;

struct TrieNode{
    char c;
    int size;
    list<pTrieNode> child;

    TrieNode(char _c, int _size): c(_c), size(_size) {};
};

struct Trie{
    pTrieNode root;
};

int main (){


    return 0;
}