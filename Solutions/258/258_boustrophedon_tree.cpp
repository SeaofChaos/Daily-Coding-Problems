#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <stack>

using namespace std;

struct node {
    int data;
    struct node* left;
    struct node* right;

    node(int info){
        data = info;
        left = NULL;
        right = NULL;
    }
};

class bsTree {
    public:
    bsTree(){
        root = NULL;
    }
    bsTree(int val){
        root = new node(val);
    }

    void insertNode(int val, node* leaf);
    void destroyTree(node* leaf);
    void printBoustrophedon(node* leaf);

    node* root;
};

void bsTree::insertNode(int val, node* leaf){
    if (this->root == NULL){
        this->root = new node(val);
        return;
    }
    
    queue<node*> nodes;
    nodes.push(leaf);
    while (true){
        node* current = nodes.front();
        nodes.pop();
        
        if (current->left == NULL){
            node* toInsert = new node(val);
            current->left = toInsert;
            return;
        }
        else {
            nodes.push(current->left);
        }
        if (current->right == NULL){
            node* toInsert = new node(val);
            current->right = toInsert;
            return;
        }
        else {
            nodes.push(current->right);
        }
    }

    //ordered binary search tree insert
    /*if (val < leaf->data){
        if (leaf->left != NULL)
            insertNode(val, leaf->left);
        else {
            node* toInsert = new node(val);
            leaf->left = toInsert;
        }
    }
    else if (val > leaf->data){
        if (leaf->right != NULL)
            insertNode(val, leaf->right);
        else {
            node* toInsert = new node(val);
            leaf->right = toInsert;
        }
    }*/
}

void bsTree::destroyTree(node *leaf){
    if (leaf != NULL){
        destroyTree(leaf->left);
        destroyTree(leaf->right);
        delete leaf;
    }
}

void printHelper(queue<int> toPrint, bool printLR){
    if (!printLR){
        stack<int> reverse;
        while (!toPrint.empty()){
            reverse.push(toPrint.front());
            toPrint.pop();
        }
        while (!reverse.empty()){
            cout << reverse.top() << ' ';
            reverse.pop();
        }
    }
    else {
        while (!toPrint.empty()){
            cout << toPrint.front() << ' ';
            toPrint.pop();
        }
    }
}

void bsTree::printBoustrophedon(node *leaf){
    node *newLevel = NULL;
    bool printLR = true;
    queue<node*> nodes;
    queue<int> toPrint;
    nodes.push(leaf);
    nodes.push(newLevel);
    
    while (true){
        node* current = nodes.front();
        nodes.pop();
        
        if (current != newLevel){
            toPrint.push(current->data);
            if (current->left != NULL)
                nodes.push(current->left);
            if (current->right != NULL)
                nodes.push(current->right);
        }
        else {
            printHelper(toPrint, printLR);
            while (!toPrint.empty())
                toPrint.pop();
            printLR = !printLR;
            if (nodes.empty())
                break;
            nodes.push(newLevel);
        }
    }
}


int main(){
    ifstream ifs;
    ifs.open("treeInput.txt", fstream::in);

    int insertNum;
    bsTree tree;
    while(!ifs.eof()){
        ifs >> insertNum;
        tree.insertNode(insertNum, tree.root);
    }
    cout << endl;
    tree.printBoustrophedon(tree.root);

    tree.destroyTree(tree.root);
    ifs.close();
    return 0;
}