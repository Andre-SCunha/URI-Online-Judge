#include <iostream>
#include <list>

    using namespace std;

struct TrieNode;
struct Trie;
typedef TrieNode* pTrieNode;

struct TrieNode{
    char c;
    int size, fill;
    list<pTrieNode> child;
    pTrieNode sufix, dicsuf;

    TrieNode(char _c, int _size): c(_c), size(_size), fill(0), sufix(NULL), dicsuf(NULL) {};
};

struct Trie{
    pTrieNode root;
    list<pTrieNode> elements;

    Trie();
    void Clear();
    void addNode(pTrieNode parent, char c);
    void Reset();
};

int main (){

    Trie T;
    T.Reset();
    T.Clear();
    return 0;
}

Trie::Trie(){

    root = new TrieNode('\0', 0);
    elements.push_back(root);

}

void Trie::Clear(){

    for(pTrieNode node : elements){
        delete node;
    }
    elements.clear();

}

void Trie::addNode(pTrieNode parent, char c){

    pTrieNode node = new TrieNode(c, parent->size+1);
    elements.push_back(node);
    parent->child.push_back(node);

}

void Trie::Reset(){

    Clear();
    root = new TrieNode('\0', 0);
    elements.push_back(root);

}