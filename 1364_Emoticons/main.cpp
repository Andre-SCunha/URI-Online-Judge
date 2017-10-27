#include <iostream>
#include <list>
#include <string>

    using namespace std;

struct TrieNode;
struct Trie;
typedef TrieNode* pTrieNode;

/////////////////////////
/* Data Structures */
////////////////////////

//TrieNode
struct TrieNode{
    char c;
    int size;
    bool inDic;
    list<pTrieNode> child;
    pTrieNode sufix, dicsuf;

    TrieNode(char _c, int _size): c(_c), size(_size), inDic(false), sufix(NULL), dicsuf(NULL) {};
    void addSufx(pTrieNode parent);
    void addDicSuf();
};

//Trie
struct Trie{
    pTrieNode root;
    list<pTrieNode> elements;

    Trie();
    void Clear();
    void Reset();
    void addNode(pTrieNode parent, char c, bool dic);
    void addWord(string s);
    void calcSufx();
    void calcDicSuf();
    int numChg(string s);
};

/////////////////////////////
/* Program Main Flow */
///////////////////////////
int main (){

    Trie T;
    int m, n;
    while(cin >> m >> n){
        if(m>0){
            string line;
            getline(cin, line);
            for (int i = 0; i < m; i++){
                getline(cin, line);
                T.addWord(line);
            }
            T.calcSufx();
            T.calcDicSuf();
            int ret = 0;
            for (int i = 0; i < n; i++){
                getline(cin, line);
                ret+=T.numChg(line);
            }
            cout << ret << endl;
            T.Reset();
        }
    }
    T.Clear();
    return 0;
}

//////////////////////
/* Trie Methods */
////////////////////

 //TRIE//******************

Trie::Trie(){

    Reset();

}

void Trie::Clear(){

    for(pTrieNode node : elements){
        delete node;
    }
    elements.clear();

}

void Trie::Reset(){

    Clear();
    root = new TrieNode('\0', 0);
    elements.push_back(root);
    root->sufix = NULL;
    root->dicsuf = NULL;

}

void Trie::addNode(pTrieNode parent, char c, bool dic){

    pTrieNode node = new TrieNode(c, parent->size+1);
    elements.push_back(node);
    parent->child.push_back(node);
    node->inDic = dic;

}

void Trie::addWord(string s){

    pTrieNode p = root;
    bool f = true;
    int i;
    for(i = 0; i < s.size()-1; i++){
        if (f){
            f = false;
            for (pTrieNode j : p->child){
                if (j->c == s[i]){
                    p = j; f=true; break;
                }
            }
        }
        if(!f){
            addNode(p, s[i], false);
            p = elements.back();
        }
    }
    if (f){
    f = false;
    for (pTrieNode j : p->child){
        if (j->c == s[i]){
            p = j; f=true; j->inDic=true; break;
        }
    }
    }
    if(!f){
        addNode(p, s[i], true);
        p = elements.back();
    }

}

void Trie::calcSufx(){

    list<pTrieNode> queue, d;
    for(pTrieNode i : root->child){
        queue.push_back(i);
        d.push_back(root);
    }

    while(queue.size()){
        queue.front()->addSufx(d.front());
        for(pTrieNode i : queue.front()->child){
            queue.push_back(i);
            d.push_back(queue.front());
        }
        queue.pop_front();
        d.pop_front();
    }

}

void Trie::calcDicSuf(){

    list<pTrieNode> queue;
    for(pTrieNode i : root->child){
        queue.push_back(i);
    }

    while(queue.size()){
        queue.front()->addDicSuf();
        for(pTrieNode i : queue.front()->child){
            queue.push_back(i);
        }
        queue.pop_front();
    }

}

int Trie::numChg(string s){

    int n = 0;
    list<int> sizes;
    list<int> endpos;
    pTrieNode aux, curr = root;
    aux = curr;
    //Making match list
    for (char &ch : s){
        //Finding next
        bool found = false;
        while(!found && aux != NULL){
            for(pTrieNode son : aux->child){
                if(ch == son->c){
                    found = true;
                    aux = son;
                    break;
                }
            }
            if(!found){
                aux = aux->sufix;
            }
        }
        curr = found?aux:root;
        //Finding shortest match
        aux = curr;
        while(aux->dicsuf !=NULL){
            aux = aux->dicsuf;
        }
        if(aux->inDic){
            endpos.push_back(n);
            sizes.push_back(aux->size);
        }
        n++;
    }
    

    //Calculating needed changes
    int del = -1;
    int ret = 0;
    while(endpos.size()){
        int ini = endpos.back() - sizes.back() + 1;
        del = (del>ini)?del:ini;
        if(del >= endpos.back()){
            ret++;
            del = (del > endpos.back())?ini:-1;
        }
        endpos.pop_back();
        sizes.pop_back();
    }
    if(del >= 0)
        ret++;
   return ret;
}

//TRIE NODE//*****************

void TrieNode::addSufx(pTrieNode parent){

    pTrieNode prev, aux = parent->sufix;
    prev = parent;
    while(aux != NULL){
        for(pTrieNode i : aux->child){
            if(i->c == c){
                sufix = i;
                return;
            }
        }
            prev = aux;
            aux = aux->sufix;
    }
    sufix = prev;

}

void TrieNode::addDicSuf(){

    if(sufix->inDic){
            dicsuf = sufix;
    } else{
            dicsuf = sufix->dicsuf;
    }

}