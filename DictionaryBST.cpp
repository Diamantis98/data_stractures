#include <iostream>
#include <string>
#include <math.h>
#include <memory>  // unique_ptr
#include <stdlib.h>
#include <cstddef>
#include <bits/stdc++.h>
#include <queue>

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
    void printLevelOrder(TreeNode *root);

    TreeNode* getRoot(){
      return root;
    }
    /* Compute the "maxDepth" of a tree -- the number of
    nodes along the longest path from the root node
    down to the farthest leaf node.*/
    int maxDepth(TreeNode* node)
    {
        if (node == NULL)
            return 0;
        else
        {
            /* compute the depth of each subtree */
            int lDepth = maxDepth(node->left);
            int rDepth = maxDepth(node->right);

            /* use the larger one */
            if (lDepth > rDepth)
                return(lDepth + 1);
            else return(rDepth + 1);
        }
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
  if(s.rfind(val,0)==0){
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

    /* first recur on left child */
    printInorder(node->left, val);

    /* now recur on right child */
    printInorder(node->right,val);
      /* then print the data of node */
    if(s.rfind(val,0)==0){
      cout << node->data << " \n";

    }
}
// Iterative method to find height of Bianry Tree
void BSTree::printLevelOrder(TreeNode *root)
{
    // Base Case
    if (root == NULL) return;

    // Create an empty queue for level order tarversal
    queue<TreeNode *> q;

    // Enqueue Root and initialize height
    q.push(root);

    while (q.empty() == false)
    {
        // nodeCount (queue size) indicates number
        // of nodes at current lelvel.
        int nodeCount = q.size();
        char space = '*';
        // Dequeue all nodes of current level and
        // Enqueue all nodes of next level
        while (nodeCount > 0)
        {
            TreeNode *node = q.front();
            std::cout << std::string((pow(2,maxDepth(node)-1))-1,space) << node->data[0] <<std::string((pow(2,maxDepth(node)-1))-1,space) ;
            q.pop();
            if (node->left != NULL)
                q.push(node->left);
            else
                std::cout << std::string(((pow(2,maxDepth(node)-1))-1)*2,space);
            if (node->right != NULL)
                q.push(node->right);
            else
                std::cout << std::string(((pow(2,maxDepth(node)-1))-1)*2,space);
            nodeCount--;
        }
        cout << endl;
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

        std::cout << (isLeft ? "├l-" : "└r-" );

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



  myTree.Insert("hospitable");
  myTree.Insert("ship");
  myTree.Insert("early");
  myTree.Insert("admit");
  myTree.Insert("weight");
  myTree.Insert("tacky");
  myTree.Insert("pricey");
  myTree.Insert("describe");
  /*
  myTree.Insert("time");
  myTree.Insert("envious");
  myTree.Insert("mammoth");
  myTree.Insert("zippy");
  myTree.Insert("feigned");
  myTree.Insert("earthy");
  myTree.Insert("uninterested");
  myTree.Insert("ability");
  myTree.Insert("account");
  myTree.Insert("abandon");
  myTree.Insert("a");
  myTree.Insert("above");
  myTree.Insert("above");
  myTree.Insert("absence");
  myTree.Insert("able");
  myTree.Insert("abroad");
  myTree.Insert("accurate");
  myTree.Insert("abuse");
  myTree.Insert("abstract");
  myTree.Insert("academic");
  myTree.Insert("absolute");
  myTree.Insert("accept");
  myTree.Insert("abusive");
  myTree.Insert("access");
  myTree.Insert("acceptance");
  myTree.Insert("accompany");
  myTree.Insert("acceptable");
  myTree.Insert("accident");
  myTree.Insert("according");
  myTree.Insert("about");
  myTree.Insert("absent");
  myTree.Insert("accountant");
  */
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
    myTree.printLevelOrder(myTree.getRoot());

  } while (input != "0");

  return 0;
}
