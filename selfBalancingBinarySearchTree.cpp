#include <iostream>

#define SPACE 10

using namespace std;

class Node {
public:
    int value;
    Node *left;
    Node *right;

    Node() {
        value = 0;
        left = NULL;
        right = NULL;
    }
    Node(int v) {
        value = v;
        left = NULL;
        right = NULL;
    }
};

class AVLTree {
public:
    Node *root;

    AVLTree() {
        root = NULL;
    }

    bool isTreeEmpty() {
        return root == NULL;
    }

    int height(Node *r) {
        if (r == NULL)
            return -1;
        int lheight = height(r->left);
        int rheight = height(r->right);
        return (lheight > rheight) ? (lheight + 1) : (rheight + 1);
    }

    int getBalanceFactor(Node *n) {
        if (n == NULL)
            return -1;
        return height(n->left) - height(n->right);
    }

    Node *rightRotate(Node *y) {
        Node *x = y->left;
        Node *T2 = x->right;
        x->right = y;
        y->left = T2;
        return x;
    }

    Node *leftRotate(Node *x) {
        Node *y = x->right;
        Node *T2 = y->left;
        y->left = x;
        x->right = T2;
        return y;
    }

    Node *insert(Node *r, Node *new_node) {
        if (r == NULL) {
            r = new_node;
            cout << "Value inserted successfully" << endl;
            return r;
        }

        if (new_node->value < r->value) {
            r->left = insert(r->left, new_node);
        } else if (new_node->value > r->value) {
            r->right = insert(r->right, new_node);
        } else {
            cout << "No duplicate values allowed!" << endl;
            return r;
        }

        int bf = getBalanceFactor(r);
        if (bf > 1 && new_node->value < r->left->value)
            return rightRotate(r);
        if (bf < -1 && new_node->value > r->right->value)
            return leftRotate(r);
        if (bf > 1 && new_node->value > r->left->value) {
            r->left = leftRotate(r->left);
            return rightRotate(r);
        }
        if (bf < -1 && new_node->value < r->right->value) {
            r->right = rightRotate(r->right);
            return leftRotate(r);
        }
        return r;
    }

    Node *minValueNode(Node *node) {
        Node *current = node;
        while (current->left != NULL) {
            current = current->left;
        }
        return current;
    }

    Node *deleteNode(Node *r, int v) {
        if (r == NULL) {
            return NULL;
        }
        if (v < r->value) {
            r->left = deleteNode(r->left, v);
        } else if (v > r->value) {
            r->right = deleteNode(r->right, v);
        } else {
            if (r->left == NULL) {
                Node *temp = r->right;
                delete r;
                return temp;
            } else if (r->right == NULL) {
                Node *temp = r->left;
                delete r;
                return temp;
            } else {
                Node *temp = minValueNode(r->right);
                r->value = temp->value;
                r->right = deleteNode(r->right, temp->value);
            }
        }

        int bf = getBalanceFactor(r);
        if (bf == 2 && getBalanceFactor(r->left) >= 0)
            return rightRotate(r);
        if (bf == 2 && getBalanceFactor(r->left) == -1) {
            r->left = leftRotate(r->left);
            return rightRotate(r);
        }
        if (bf == -2 && getBalanceFactor(r->right) <= -0)
            return leftRotate(r);
        if (bf == -2 && getBalanceFactor(r->right) == 1) {
            r->right = rightRotate(r->right);
            return leftRotate(r);
        }
        return r;
    }

    void print2D(Node *r, int space) {
        if (r == NULL)
            return;
        space += SPACE;
        print2D(r->right, space);
        cout << endl;
        for (int i = SPACE; i < space; i++)
            cout << " ";
        cout << r->value << "\n";
        print2D(r->left, space);
    }

    void printPreorder(Node *r) {
        if (r == NULL)
            return;
        cout << r->value << " ";
        printPreorder(r->left);
        printPreorder(r->right);
    }

    void printInorder(Node *r) {
        if (r == NULL)
            return;
        printInorder(r->left);
        cout << r->value << " ";
        printInorder(r->right);
    }

    void printPostorder(Node *r) {
        if (r == NULL)
            return;
        printPostorder(r->left);
        printPostorder(r->right);
        cout << r->value << " ";
    }

    void printGivenLevel(Node *r, int level) {
        if (r == NULL)
            return;
        else if (level == 0)
            cout << r->value << " ";
        else {
            printGivenLevel(r->left, level - 1);
            printGivenLevel(r->right, level - 1);
        }
    }

    void printLevelOrderBFS(Node *r) {
        int h = height(r);
        for (int i = 0; i <= h; i++)
            printGivenLevel(r, i);
    }

    Node *iterativeSearch(int v) {
        if (root == NULL) {
            return root;
        } else {
            Node *temp = root;
            while (temp != NULL) {
                if (v == temp->value) {
                    return temp;
                } else if (v < temp->value) {
                    temp = temp->left;
                } else {
                    temp = temp->right;
                }
            }
            return NULL;
        }
    }

    Node *recursiveSearch(Node *r, int val) {
        if (r == NULL || r->value == val)
            return r;
        else if (val < r->value)
            return recursiveSearch(r->left, val);
        else
            return recursiveSearch(r->right, val);
    }
};

int main() {
    AVLTree obj;
    int option, val;

    do {
        cout << "What operation do you want to perform? " <<
            " Select Option number. Enter 0 to exit." << endl;
        cout << "1. Insert Node" << endl;
        cout << "2. Search Node" << endl;
        cout << "3. Delete Node" << endl;
        cout << "4. Print/Traversal AVL Tree values" << endl;
        cout << "5. Height of Tree" << endl;
        cout << "6. Clear Screen" << endl;
        cout << "0. Exit Program" << endl;

        cin >> option;
        Node *new_node = new Node();

        switch (option) {
        case 0:
            break;
        case 1:
            cout << "AVL INSERT" << endl;
            cout << "Enter VALUE of TREE NODE to INSERT in AVL Tree: ";
            cin >> val;
            new_node->value = val;
            obj.root = obj.insert(obj.root, new_node);
            cout << endl;
            break;
        case 2:
            cout << "SEARCH" << endl;
            cout << "Enter VALUE of TREE NODE to SEARCH in AVL Tree: ";
            cin >> val;
            new_node = obj.recursiveSearch(obj.root, val);
            if (new_node != NULL) {
                cout << "Value found" << endl;
            } else {
                cout << "Value NOT found" << endl;
            }
            break;
        case 3:
            cout << "DELETE" << endl;
            cout << "Enter VALUE of TREE NODE to DELETE in AVL: ";
            cin >> val;
            new_node = obj.recursiveSearch(obj.root, val);
            if (new_node != NULL) {
                obj.root = obj.deleteNode(obj.root, val);
                cout << "Value Deleted" << endl;
            } else {
                cout << "Value NOT found" << endl;
            }
            break;
        case 4:
            cout << "PRINT 2D: " << endl;
            obj.print2D(obj.root, 5);
            cout << endl;
            break;
        case 5:
            cout << "TREE HEIGHT" << endl;
            cout << "Height : " << obj.height(obj.root) << endl;
            break;
        case 6:
            system("cls");
            break;
        default:
            cout << "Enter Proper Option number " << endl;
        }

    } while (option != 0);

    return 0;
}
