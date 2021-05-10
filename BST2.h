#ifndef POKEMON_BST2_H
#define POKEMON_BST2_H
#include "BST2Interface.h"
#include "sstream"
#include <string>
using namespace std;


template<typename T>

class BinaryTree : public BSTInterface<T> {

private:


    struct BTNode {

        BTNode(const T &inputData, BTNode *leftValue = NULL, BTNode *rightValue = NULL) {
            data = inputData;
            left = leftValue;
            right = rightValue;
        }

        ~BTNode() {
        };

        T data;
        BTNode *left;
        BTNode *right;
    };

    BTNode* root;
public:

    BinaryTree() {
        root = NULL;    // sets the data value to 3 and default parameters of node constructor point to Null
    }
    ~BinaryTree() {
        clearTree();
    }

    BinaryTree& operator=(const BTNode &rhs) {
        if(this->root != rhs.root) {

        }
    }


    /** Return true if node added to BST, else false */
    bool addNode(const T& item) {
        return addNode(this->root, item);
    }

    bool addNode(BTNode*& regionalRoot, const T& item) {     // I need to be able to pass in parameter of type BtNODE pointer
        if(regionalRoot == NULL) {
            regionalRoot = new BTNode(item);
            return true;
        }
        else {
            if(item < regionalRoot->data) {
                return addNode(regionalRoot->left, item);
            }
            else if(regionalRoot->data < item) {
                return addNode(regionalRoot->right, item);
            }
            else {
                return false;
            }
        }
    }

    /** Return true if node removed from BST, else false */
    bool removeNode(const T& item) {

        return removeNode(root, item);
    }

    bool removeNode(BTNode*& regionRoot, const T& item) {
        if(regionRoot == NULL) {
            return false;
        }
        else {
            if(item < regionRoot->data) {
                return removeNode(regionRoot->left, item);
            }
            else if(regionRoot->data < item) {
                return removeNode(regionRoot->right, item);
            }
            else {
                BTNode* oldRoot = regionRoot;
                if(regionRoot->left == NULL) {
                    regionRoot = regionRoot->right;
                }
                else if(regionRoot->right == NULL) {
                    regionRoot = regionRoot->left;
                }
                else {
                    Replace(oldRoot, oldRoot->left);

                }
                delete oldRoot;
                return true;
            }
        }
    }


    /** Return true if BST cleared of all nodes, else false */
    bool clearTree() {
        clearTree(root);
        root = NULL;
        if(root == NULL) {
            return true;
        }
        return false;
    }

    void clearTree(BTNode*& r) {
        if(r == NULL) {
            return;
        }
        clearTree(r->left);
        clearTree(r->right);
        cout << r->data << endl;
        delete r;
        r = NULL;
    }

    void Replace(BTNode*& oldRoot, BTNode*& regionalRoot) {
        if(regionalRoot->right != NULL) {
            Replace(oldRoot, regionalRoot->right);
        }
        else  {
            oldRoot->data = regionalRoot->data;
            oldRoot = regionalRoot;
            regionalRoot = regionalRoot->left;
        }
    }

    string toString() const {
        stringstream out;
        toString(root, out);
        string temp = out.str();
        if (temp == "") {
            return temp;
        } else {
            temp.erase(temp.size() - 1, 1);
            return temp;
        }
    }

    /** Return a level order traversal of a BST as a string */
    void toString(BTNode* local_root, stringstream& out) const {
        // In order traversal
        // left child
        // visit the node
            // append its value to "out"
        // right child

        if (local_root == nullptr)
            return;

        toString(local_root->left, out);

        out << local_root->data << ",";

        toString(local_root->right, out);
    }

    /** Output nodes at a given level */
    bool outLevel(BTNode* root, int level, stringstream& out) const {
        if (root == NULL) {
            return false;
        }
        if (level == 1)
        {
            out << " " << root->data;
            if ((root->left != NULL) || (root->right != NULL)) {
                return true;
            }

            else  {
                return false;
            }
        }
        if ((level == 2) && root->left == NULL && root->right != NULL) {
            out << " _";
        }
        bool left = outLevel(root->left, level - 1, out);
        bool right = outLevel(root->right, level - 1, out);
        if ((level == 2) && root->left != NULL && !root->right) {
            out << " _";
        }
        return left || right;
    } // end outLevel()

    int Size(BTNode *r) const {
        if(r == NULL) {
            return 0;
        }
        else {
            return(Size(r->left) + 1 + Size(r->right));
        }
    }

    int Size() const {
        return Size(root);
    }

    bool Find(const T& value, BTNode* r) {
        if(r == NULL) {
            return false;
        }
        else if(value == r->data) {
            return true;
        }
        else if(value < r->data) {
            return Find(value, r->left);
        }
        else if(value > r->data) {
            return Find(value, r->right);
        }
    }

    bool Find(const T& value) {
        return Find(value, root);
    }






};


#endif //POKEMON_BST2_H
