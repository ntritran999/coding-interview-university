#include <iostream>

using namespace std;

struct BSTNode
{
    int data;
    BSTNode *left;
    BSTNode *right;
};

BSTNode* createNode(int v) {
    BSTNode *p = new BSTNode;
    p->data = v;
    p->left = p->right = nullptr;
    return p;
}

BSTNode* insert(BSTNode *root, int v) {
    if (root == nullptr)
        return createNode(v);
    if (root->data > v)
        root->left = insert(root->left, v);
    else if (root->data < v)
        root->right = insert(root->right, v);
    return root;
}

int get_node_count(BSTNode *root) {
    if (root == nullptr)
        return 0;
    return get_node_count(root->left) + get_node_count(root->right) + 1;
}

void print_values(BSTNode *root) {
    if (root == nullptr)
        return;
    print_values(root->left);
    cout << root->data << " ";
    print_values(root->right);
}

BSTNode* delete_tree(BSTNode *root) {
    if (root == nullptr)
        return nullptr;

    root->left = delete_tree(root->left);
    root->right = delete_tree(root->right);
    delete root;
    return nullptr;
}

bool is_in_tree(BSTNode *root, int v) {
    if (root == nullptr)
        return false;

    if (root->data > v)
        return is_in_tree(root->left, v);
    else if (root->data < v)
        return is_in_tree(root->right, v);
    return true;
}

int get_height(BSTNode *root) {
    if (root == nullptr)
        return 0;
    return max(get_height(root->left), get_height(root->right)) + 1;
}

int get_min(BSTNode *root) {
    if (root == nullptr)
        return -1;
    
    while (root->left != nullptr)
        root = root->left;
    return root->data;
}

int get_max(BSTNode *root) {
    if (root == nullptr)
        return -1;

    while (root->right != nullptr)  
        root = root->right;
    return root->data;
}

bool is_bst(BSTNode* root, int min_value, int max_value) {
    if (root == nullptr)
        return true;

    if (root->data > min_value && root->data < max_value
        && is_bst(root->left, min_value, root->data)
        && is_bst(root->right, root->data, max_value))
        return true;

    return false;
}

BSTNode *findReplacement(BSTNode *target, BSTNode *&cur) {
    while (cur->right != nullptr)
        return findReplacement(target, cur->right);

    BSTNode *tmp = cur;
    target->data = cur->data;
    cur = cur->left;
    return tmp;
}

BSTNode* delete_value(BSTNode *root, int val) {
    if (root == nullptr)
        return root;

    if (root->data > val)
        root->left = delete_value(root->left, val);
    else if (root->data < val) 
        root->right = delete_value(root->right, val);
    else {
        BSTNode *tmp = root;
        if (root->left == nullptr)
            root = root->right;
        else if (root->right == nullptr)
            root = root->left;
        else {
            tmp = findReplacement(root, root->left);
        }
        delete tmp;
    }
    return root;
}

BSTNode* findNode(BSTNode *root, int val) {
    if (root == nullptr)
        return root;
    
    if (root->data > val)
        return findNode(root->left, val);
    else if (root->data < val)
        return findNode(root->right, val);
    return root;
}

int get_successor(BSTNode *root, int val) {
    if (root == nullptr)
        return -1;

    BSTNode *p = findNode(root, val);
    if (p == nullptr)
        return -1;

    if (p->right != nullptr)
        return get_min(p->right);
    else {
        BSTNode *successor = nullptr;
        BSTNode *parent = root;
        while (parent != p) {
            if (parent->data > val) {
                successor = parent;
                parent = parent->left;
            }
            else if (parent->data < val)
                parent = parent->right;
        }
        return successor ? successor->data : -1;
    }
}

int main() {
    BSTNode *root = nullptr;
    root = insert(root, 5);
    root = insert(root, 4);
    root = insert(root, 6);
    root = insert(root, 2);
    root = insert(root, 1);
    root = insert(root, 3);
    root = insert(root, 8);

    cout << "Total nodes: " << get_node_count(root) << "\n";
    cout << "Height: " << get_height(root) << "\n";
    cout << "Max value: " << get_max(root) << "\n";
    cout << "Min value: " << get_min(root) << "\n";
    print_values(root);
    cout << "\n";

    cout << "Is 4 in tree: " << ((is_in_tree(root, 4)) ? "Yes" : "No") << "\n";
    cout << "Is 100 in tree: " << ((is_in_tree(root, 100)) ? "Yes" : "No") << "\n";
    cout << "Is this bst: " << ((is_bst(root, INT_MIN, INT_MAX)) ? "Yes" : "No") << "\n";

    cout << "Successor of 3 is: " << get_successor(root, 3) << "\n";
    delete_value(root, 1);
    delete_value(root, 2);
    delete_value(root, 5);
    print_values(root);
    delete_tree(root);
    return 0;
}