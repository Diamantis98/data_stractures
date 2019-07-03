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
private:
    TreeNode* root;
    std::string SubTreeAsString(TreeNode* node);  // Helper method for Print()
    void Insert(string val, TreeNode* node); // Helper method for Insert(int val)

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

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/

void searchWord(string word);
void deleteWord(string word);

int main() {

  BSTree myTree;

  int numOfChoice = 10;
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
    cout << "0. Exit." << ".\n";
    cout << "1. Insert a Word" << ".\n";
    cout << "2. Search a Word" << ".\n";
    cout << "3. Delete a Word" << ".\n";

    cout << "Enter the number of your choise: ";
    cin >> numOfChoice;


    string word;

    if (numOfChoice == 1) {
      cout << "Submit the word: " << "\n";
      cin >> word;
      myTree.Insert(word);
    } else if (numOfChoice == 2) {
      cout << "Search the word: " << "\n";
      cin >> word;
      myTree.searchWord(word);
    } else if (numOfChoice == 3) {
      cout << "Delete the word: " << "\n";
      cin >> word;
      deleteWord(word);
    }else{
      cout << "Wrong inpu, try again. " << "\n";

    }

    myTree.Print();

} while (numOfChoice != 0);

}

void searchWord(string word) {

}

void deleteWord(string word) {

}
