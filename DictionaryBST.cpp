#include <iostream>
#include <string>
#include <math.h>
#include <memory>  // unique_ptr
#include <stdlib.h>
#include <cstddef>
#include <bits/stdc++.h>

using namespace std;

struct TreeNode
{
    // member vars
    string data;
    TreeNode* left;
    TreeNode* right;

    // constructor
    TreeNode(string data): data(data), left(NULL), right(NULL) {}
};

class BSTree
{
public:
    // constructors
    BSTree(): root(NULL) {}
    BSTree(TreeNode* rootNode): root(rootNode) {}

    // member functions
    void Print();
    void Insert(string val);
    void searchWord(string val);

    void printInorder(TreeNode* node, string val);
    TreeNode* deleteNode(TreeNode* root, string k);
    void printBT(const TreeNode* node);

    TreeNode* getRoot(){
      return root;
    }
private:
    TreeNode* root;
    std::string SubTreeAsString(TreeNode* node);  // Helper method for Print()
    void Insert(string val, TreeNode* node); // Helper method for Insert(int val)
    void printBT(const std::string& prefix, const TreeNode* node, bool isLeft); // Helper method for printBT()

    void searchWord(string val, TreeNode*node);
};

void BSTree::searchWord(string val){
  if(root == NULL){
    std::cout << "Tree is empty." << std::endl;
  }else{
    this->searchWord(val, this->root);
  }
}

void BSTree::searchWord(string val, TreeNode* node){
  std::string s = node->data;
  if(s.rfind(val,0) == 0){
    std::cout << "Data found. \n" << std::endl;
    std::cout << "Possible matches : " << std::endl;

    printInorder(node,val);
    return ;
  }else if(val < node->data){
      if(node->left == NULL){
        std::cout << "Data NOT found." << std::endl;
      } else{
          this->searchWord(val, node->left);
      }
  }else{
    if(node->right == NULL){
      std::cout << "Data NOT found." << std::endl;
    } else{
        this->searchWord(val, node->right);
    }
  }

}

// IN Order Traversal for sorted Search
/* Given a binary tree, print its nodes in inorder*/
void BSTree::printInorder(TreeNode* node, string val)
{
    if (node == NULL) return;

    std::string s = node->data;
    if(s.rfind(val,0) == 0){

      /* first recur on left child */
      printInorder(node->left, val);

      /* then print the data of node */
      cout << node->data << " \n";

      /* now recur on right child */
      printInorder(node->right,val);
    }else{
      return;
    }
}

/// Insert a new value into the tree
void BSTree::Insert(string val) {
    if(root == NULL){
        this->root = new TreeNode(val);
    } else{
        this->Insert(val, this->root);
    }
}

/// Insert a new value into the subtree starting at node
void BSTree::Insert(string val, TreeNode* node) {

    // Check if node's value equals val
    // If so, warn the user and then exit function
    if(val == node->data){
        std::cout << "Warning: Value already exists, so nothing will be done." << std::endl;
        return;
    }

    // Check if val is < or > this node's value
    if(val < node->data){
        if(node->left == NULL){
            // Make a new node as the left child of this node
            node->left = new TreeNode(val);
        } else{
            // Recursively call Insert() on this node's left child
            this->Insert(val, node->left);
        }
    } else{
        if(node->right == NULL){
            // Make a new node as the right child of this node
            node->right = new TreeNode(val);
        } else{
            // Recursively call Insert() on this node's right child
            this->Insert(val, node->right);
        }
    }
}
/* Given a binary search tree and a key, this function deletes the key
   and returns the new root */
TreeNode* BSTree::deleteNode(TreeNode* root, string k)
{
    // Base case
    if (root == NULL)
        return root;

    // Recursive calls for ancestors of
    // node to be deleted
    if (root->data > k) {
        root->left = deleteNode(root->left, k);
        return root;
    }
    else if (root->data < k) {
        root->right = deleteNode(root->right, k);
        return root;
    }

    // We reach here when root is the node
    // to be deleted.

    // If one of the children is empty
    if (root->left == NULL) {
        TreeNode* temp = root->right;
        delete root;
        return temp;
    }
    else if (root->right == NULL) {
        TreeNode* temp = root->left;
        delete root;
        return temp;
    }

    // If both children exist
    else {

        TreeNode* succParent = root->right;

        // Find successor
        TreeNode *succ = root->right;
        while (succ->left != NULL) {
            succParent = succ;
            succ = succ->left;
        }

        // Delete successor.  Since successor
        // is always left child of its parent
        // we can safely make successor's right
        // right child as left of its parent.
        succParent->left = succ->right;

        // Copy Successor Data to root
        root->data = succ->data;

        // Delete Successor and return root
        delete succ;
        return root;
    }
}
void BSTree::Print(){
    if(this->root == NULL){
        std::cout << "{}" << std::endl;
    } else{
        std::cout << this->SubTreeAsString(this->root) << std::endl;
    }
}

std::string BSTree::SubTreeAsString(TreeNode* node){
    std::string leftStr = (node->left == NULL) ? "{}" : SubTreeAsString(node->left);
    std::string rightStr = (node->right == NULL) ? "{}" : SubTreeAsString(node->right);
    std::string result = "{" + (node->data) + ", " + leftStr + ", " + rightStr + "}";
    return result;
}
void BSTree::printBT(const std::string& prefix, const TreeNode* node, bool isLeft)
{
    if( node != nullptr )
    {
        std::cout << prefix;

        std::cout << (isLeft ? "├──" : "└──" );

        // print the value of the node
        std::cout << node->data << std::endl;

        // enter the next tree level - left and right branch
        printBT( prefix + (isLeft ? "│   " : "    "), node->left, true);
        printBT( prefix + (isLeft ? "│   " : "    "), node->right, false);
    }
}

void BSTree::printBT(const TreeNode* node)
{
    printBT("", node, false);
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/


int main() {

  BSTree myTree;

  string input;

  myTree.Insert("a");
  myTree.Insert("abandon");
  myTree.Insert("ability");
  myTree.Insert("able");
  myTree.Insert("about");
  myTree.Insert("above");
  myTree.Insert("above");
  myTree.Insert("abroad");
  myTree.Insert("absence");
  myTree.Insert("absent");
  myTree.Insert("absolute");
  myTree.Insert("abstract");
  myTree.Insert("abuse");
  myTree.Insert("abusive");
  myTree.Insert("academic");
  myTree.Insert("accept");
  myTree.Insert("acceptable");
  myTree.Insert("acceptance");
  myTree.Insert("access");
  myTree.Insert("accident");
  myTree.Insert("accompany");
  myTree.Insert("according");
  myTree.Insert("account");
  myTree.Insert("accountant");
  myTree.Insert("accurate");

  do {


    cout <<"\n"<< "MENU" << ".\n";
    cout << "0. Exit." << "\n";
    cout << "1. Insert a Word" << ".\n";
    cout << "2. Search a Word" << ".\n";
    cout << "3. Delete a Word" << ".\n";

    cout << "Enter the number of your choise: ";
    cin >> input;


    string word;

    if (input == "1") {
      cout << "Submit the word: " << "\n";
      cin >> word;
      myTree.Insert(word);
    } else if (input == "2") {
      cout << "Search the word: " << "\n";
      cin >> word;
      myTree.searchWord(word);
      cout << "\n";
    } else if (input == "3") {
      cout << "Delete the word: " << "\n";
      cin >> word;
      myTree.deleteNode(myTree.getRoot(),word);
    }else if (input != "0"){

      cout << "Wrong input, try again. " << "\n";
    }

    myTree.printBT(myTree.getRoot());

  } while (input != "0");

  return 0;
}
