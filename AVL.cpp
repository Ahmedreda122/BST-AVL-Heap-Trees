#include <algorithm>
#include <iostream>

using namespace std;

struct node
{
  node* left = nullptr;
  node* right = nullptr;
  int value = 0;
  node(int val) : value(val){}
};

class AVL
{
private:
  node* root;
public: 

  AVL(): root(nullptr) {}

  node* insertion(int value, node* current)
  {
    if (current == nullptr)
    {
      node* newNode = new node(value);
      current = newNode;
      return current;
    }
    else if (value > current->value)
    { 
      current->right = insertion(value, current->right);
    }
    else if (value < current->value)
    {
      current->left = insertion(value, current->left);
    }
    else
    {
      // NO DUPLICATES ALLOWED
      return current;
    }
    
    int BF = getBalanceFactor(current);
    
    // Imbalance comes from Left of Left child
    if (BF > 1 && current->value < current->left->value)
    {
      return LL_Rotation(current);
    }
    // Imbalance comes from Right of Right child
    else if (BF < -1 && current->value > current->right->value)
    {
      return RR_Rotation(current);
    } 
    // Imbalance comes from Right of Left Child (Left Right Grand Child)
    else if (BF > 1 && current->value > current->left->value)
    {
      return LR_Rotation(current);
    }
    // Imbalance comes from left Right Child (Right Left Grand Child)
    else if (BF < -1 && current->value < current->right->value)
    {
      return RL_Rotation(current);
    }
    return current;
  }

  int getHeight(node* current)
  {
    if (current == nullptr)
      // Return -1 because the leaf node will have 0 as a height
      return -1;
    else
      // 1 + the maximum height of the children of that node 
      return 1 + max(getHeight(current->left), getHeight(current->right));
  } 

  int getBalanceFactor(node* current)
  {
    if (current == NULL)
    {
      return -1;
    }
    else 
    {
      return (getHeight(current->left) - getHeight(current->right));
    }  
  }

  // + for root, +(0) child 
  node* LL_Rotation(node* current)// Single Right Rotation
  {
    node* child = current->left;

    current->left = child->right;
    child->right = current;

    return child;
  }

  node* RR_Rotation(node* current) { // Single Left Rotation
    node* child = current->right;
    
    current->right = child->left;
    child->left = current;

    return child;
  }

  node* LR_Rotation(node* current) { // Double Rotition (Left then Right)
    node* child = current->left;
    node* GrChild = child->right;

    current->left = GrChild->left;
    child->right = GrChild->right;

    GrChild->left = child;
    GrChild->right = current; 

    return GrChild;
    // RR_Rotation(child);
    // LL_Rotation(current);
  }
  
  node* RL_Rotation(node* current) { // Double Rotition (Right then Left)
    node* child = current->right;
    node* GrChild = child->left;

    current->right = GrChild->left;
    child->left = GrChild->right;

    GrChild->right = child;
    GrChild->left = current;

    return GrChild;
    //LL_Rotation(child);
    //RR_Rotation(current);
  }

  void insert(int value)
  {
    root = insertion(value, this->root);
  }

  void preOrder(node* current)
  {
    if (current == nullptr)
    {
      return;
    }
    
    cout << current->value << '\t';
    preOrder(current->left);
    preOrder(current->right);
  }

  void inOrder(node* current)
  {
    if (current == nullptr)
    {
      return;
    }
    
    inOrder(current->left);
    cout << current->value << '\t';
    inOrder(current->right);
  }

  void postOrder(node* current)
  {
    if (current == nullptr)
    {
      return;
    }
    
    postOrder(current->left);
    postOrder(current->right);
    cout << current->value << '\t';
  }

  void print(string traversalType = "preorder")
  {
    for(int i = 0; i < traversalType.length(); ++i)
    {
      traversalType[i] = tolower(traversalType[i]);
    }

    if (traversalType == "preorder")
    {
      preOrder(this->root);
    }
    else if (traversalType == "inorder")
    {
      inOrder(this->root);
    }
    else if (traversalType == "postorder")
    {
      postOrder(this->root);
    }
    else
    {
      cout << "Unknown traversal type";
    }
  }

  bool search(node* current, int key)
  {
    while(true)
    {
      if (current == nullptr)
      {
        cout << "Item Does not Exist In The Tree" << endl;
        return false;
      }
      else if (current->value == key)
      {
        cout << "Item is Found\n";
        return true;
      }
      else if (key > current->value)
      {
        current = current->right;
      }
      else
      {
        current = current->left;
      }
    }
  }

  bool search(int key)
  {
    return search(root, key);
  }

  node* findMin(node* current)
  {
    if (current == nullptr)
    {
      return 0;
    }
    else if (current->left == nullptr)
    {
      return current;
    }
    else
    {
      return findMin(current->left);
    }
  }

  node* findMin()
  {
    return findMin(root);
  }

  node* findMax(node* current)
  {
    if (current == nullptr)
    { 
      return 0;
    }
    else if (current->right == nullptr)
    {
      return current;
    }
    else
    {
      return findMax(current->right);
    }
  }

  node* findMax()
  {
    return findMax(root);
  }


  node* deleteNode(node* current, int key)
  {
    if (current == nullptr)
    {
      return 0;
    }

    if (key > current->value) // Item exists in right subtree
    {
      // Make the right of the current node be the updated subtree (After deletion)
      current->right = deleteNode(current->right, key);
    }
    else if (key < current->value) // Item exists in left subtree
    {
      // Make the left of the current node be the updated subtree (After deletion)
      current->left = deleteNode(current->left, key);
    }
    else // If current node is the node i want to delete
    {
      // IF current node is a leaf node
      if (current->right == nullptr && current->left == nullptr)
      {
        // Delete the current node and return nullptr to the parent node to point at it
        delete current;
        return nullptr;
      }
      // Has one child (right child)
      else if (current->right != nullptr && current->left == nullptr)
      {
        // Move current node to be the right node (point at right subtree) and Deletes the the previous node (current node before moving it)
        node* prev = current; 
        current = current->right;
        delete prev;
        return current;
      }
      // Has one child (left child)
      else if (current->left != nullptr && current->right == nullptr)
      {
        // Move current node to be the left node (point at right subtree) then Deletes the previous node (current node before moving it);
        node* prev = current; 
        current = current->left;
        delete prev;
        return current;
      }
      // Has Two children
      else 
      {
        // Successor (minimum node of the right subtree)
        node* successor = findMin(current->right);
        // Move the successor data into current node then delete the successor node and return the updated current node to make parent point at it
        current->value = successor->value;
        // Make the current node point at the right subtree after deleting the successor node from it
        current->right = deleteNode(current->right, successor->value);
      }
    }
    // Balance Factor = Height of left subtree - Height of right subtree
    int BF = getBalanceFactor(current);
    
    // Node From Right Subtree was Deleted and Imbalance came from left of left Subtree.
    if (BF == 2 && getBalanceFactor(current->left) >= 0) // BF of left subtree can be 0 or 1 only for this case because it's already balanced subtree
    {
      return LL_Rotation(current);
    }
    // Node From Right Subtree was Deleted and Imbalance came from Right of left Subtree (left right node).
    else if (BF == 2 && getBalanceFactor(current->left) == -1)
    {
      return LR_Rotation(current);
    }
    // Node From Left Subtree was Deleted and Imbalance came from Right of Right Subtree.
    else if (BF == -2 && getBalanceFactor(current->right) <= 0) // BF of right subtree can be 0 or -1 only for this case because it's already balanced subtree
    {
      return RR_Rotation(current);
    }
    // Node From Left Subtree was Deleted and Imbalance came from Left of Right Subtree (Right Left node).
    else if (BF == -2 && getBalanceFactor(current->right) == 1)
    {
      return RL_Rotation(current);
    }
    return current;
  }

  void deleteNode(int key)
  {
    root = deleteNode(this->root, key);
  }
};

int main()
{
  AVL tree;
  tree.insert(5);
  tree.insert(9);
  tree.insert(8);
  tree.insert(7);
  tree.insert(6);
  tree.print("preorder");
  tree.deleteNode(7);
  cout << endl;
  tree.print("preorder");
}