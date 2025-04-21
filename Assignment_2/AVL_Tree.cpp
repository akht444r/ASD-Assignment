#include <iostream>
using namespace std;

class Node {
public:
    int key;
    Node *left, *right;
    int height;
    Node(int val) {
        key = val;
        left = right = nullptr;
        height = 1;
    }
};

int height(Node *n) {
    return (n == nullptr) ? 0 : n->height;
}

int balance(Node *n) {
    return (n == nullptr) ? 0 : height(n->left) - height(n->right);
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

Node* rotateToRight(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));
    return x;
}

Node* rotateToLeft(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));
    return y;
}

Node* insert(Node *node, int key) {
    if (node == nullptr) return new Node(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));

    int bal = balance(node);

    if (bal > 1 && key < node->left->key)
        return rotateToRight(node);
    if (bal < -1 && key > node->right->key)
        return rotateToLeft(node);
    if (bal > 1 && key > node->left->key) {
        node->left = rotateToLeft(node->left);
        return rotateToRight(node);
    }
    if (bal < -1 && key < node->right->key) {
        node->right = rotateToRight(node->right);
        return rotateToLeft(node);
    }

    return node;
}

Node* minNode(Node* node) {
    Node* current = node;
    while (current && current->left)
        current = current->left;
    return current;
}

Node* deleteNode(Node* root, int key) {
    if (root == nullptr) return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        Node* temp = minNode(root->right);
        root->key = temp->key;
        root->right = deleteNode(root->right, temp->key);
    }

    root->height = 1 + max(height(root->left), height(root->right));

    int bal = balance(root);

    if (bal > 1 && balance(root->left) >= 0)
        return rotateToRight(root);

    if (bal > 1 && balance(root->left) < 0) {
        root->left = rotateToLeft(root->left);
        return rotateToRight(root);
    }

    if (bal < -1 && balance(root->right) <= 0)
        return rotateToLeft(root);

    if (bal < -1 && balance(root->right) > 0) {
        root->right = rotateToRight(root->right);
        return rotateToLeft(root);
    }

    return root;
}

void printTree(Node *root, string indent = "", bool last = true) {
    if (root != nullptr) {
        cout << indent;
        if (last) {
            cout << "R----";
            indent += "     ";
        } else {
            cout << "L----";
            indent += "|    ";
        }
        cout << root->key << endl;
        printTree(root->left, indent, false);
        printTree(root->right, indent, true);
    }
}

int main() {
    Node *root = nullptr;
    int values[] = {9, 7, 19, 29, 64, 38, 52, 91, 20};

    for (int key : values) {
        root = insert(root, key);
        cout << "After inserting " << key << ":\n";
        printTree(root);
        cout << "------------------------\n";
    }

    cout << "After deleting 91:\n";
    root = deleteNode(root, 91);
    printTree(root);
    cout << "------------------------\n";

    root = insert(root, 77);
    cout << "After inserting 77:\n";
    printTree(root);
    cout << "------------------------\n";

    return 0;
}
