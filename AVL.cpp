#include <algorithm>
#include <iostream>
#include "Student.cpp"

using namespace std;

struct StudentNode
{
  StudentNode* left;
  StudentNode* right;
  
  Student dataOBJ;

  int getID() const
  {
    return dataOBJ.ID;
  }

  StudentNode()
  {
    left = nullptr;
    right = nullptr;
    dataOBJ = Student(0, "none", "none", 0.0);
  }

  StudentNode(const Student& data)
  {
    left = nullptr;
    right = nullptr;
    dataOBJ = data;
  }
};

class AVL
{
private:
  StudentNode* root;
  map<string, int> departmentCounters;

  void LoadDepartmentCounter(StudentNode* current)
  {
    if (current == nullptr)
    {
      return;
    }
    ++departmentCounters[current->dataOBJ.department];
    LoadDepartmentCounter(current->left);
    LoadDepartmentCounter(current->right);
  }
public: 

  AVL(): root(nullptr) {}

  StudentNode* insertion(Student newStdnt, StudentNode* current)
  {
    if (current == nullptr)
    {
      StudentNode* newNode = new StudentNode(newStdnt);
      current = newNode;
      return current;
    }
    else if (newStdnt.ID > current->getID())
    { 
      current->right = insertion(newStdnt, current->right);
    }
    else if (newStdnt.ID < current->getID())
    {
      current->left = insertion(newStdnt, current->left);
    }
    else
    {
      // NO DUPLICATES ALLOWED
      return current;
    }
    
    int BF = getBalanceFactor(current);
    
    // Imbalance comes from Left of Left child
    if (BF > 1 && newStdnt.ID < current->left->getID())
    {
      return LL_Rotation(current);
    }
    // Imbalance comes from Right of Right child
    else if (BF < -1 && newStdnt.ID > current->right->getID())
    {
      return RR_Rotation(current);
    } 
    // Imbalance comes from Right of Left Child (Left Right Grand Child)
    else if (BF > 1 && newStdnt.ID > current->left->getID())
    {
      return LR_Rotation(current);
    }
    // Imbalance comes from left Right Child (Right Left Grand Child)
    else if (BF < -1 && newStdnt.ID < current->right->getID())
    {
      return RL_Rotation(current);
    }
    return current;
  }

  int getHeight(StudentNode* current)
  {
    if (current == nullptr)
      // Return -1 because the leaf StudentNode will have 0 as a height
      return -1;
    else
      // 1 + the maximum height of the children of that StudentNode 
      return 1 + max(getHeight(current->left), getHeight(current->right));
  } 

  int getBalanceFactor(StudentNode* current)
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
  StudentNode* LL_Rotation(StudentNode* current)// Single Right Rotation
  {
    StudentNode* child = current->left;

    current->left = child->right;
    child->right = current;

    return child;
  }

  StudentNode* RR_Rotation(StudentNode* current) { // Single Left Rotation
    StudentNode* child = current->right;
    
    current->right = child->left;
    child->left = current;

    return child;
  }

  StudentNode *LR_Rotation(StudentNode *current) // Double Rotition (Left then Right)
  { 
    StudentNode *child = current->left;
    StudentNode *GrChild = child->right;

    current->left = GrChild->right; 
    child->right = GrChild->left;

    GrChild->left = child;
    GrChild->right = current; 

    return GrChild;
    // RR_Rotation(child);
    // LL_Rotation(current);
  }

  StudentNode *RL_Rotation(StudentNode *current) // Double Rotition (Right then Left)
  { 
    StudentNode *child = current->right;
    StudentNode *GrChild = child->left;

    current->right = GrChild->left;
    child->left = GrChild->right;

    GrChild->right = child;
    GrChild->left = current;

    return GrChild;
    // LL_Rotation(child);
    // RR_Rotation(current);
  }

  void addStudent(Student newStdnt)
  {
    root = insertion(newStdnt, this->root);
  }

  void preOrder(StudentNode* current)
  {
    if (current == nullptr)
    {
      return;
    }

    static int counter = 0;

    cout << ++counter << "- "; 
    this->printStuData(current);
    preOrder(current->left);
    preOrder(current->right);
  }

  void inOrder(StudentNode* current)
  {
    if (current == nullptr)
    {
      return;
    }
    static int counter = 0;

    inOrder(current->left);
    cout << ++counter << "- ";
    this->printStuData(current);
    cout << setfill('0') << setw(2);
    inOrder(current->right);
  }

  void postOrder(StudentNode* current)
  {
    if (current == nullptr)
    {
      return;
    }
    static int counter = 0;

    postOrder(current->left);
    postOrder(current->right);
    cout << ++counter << "- ";
    this->printStuData(current);
  }

  void printStuData(StudentNode* stdntNode)
  {
    cout << "ID: " << stdntNode->dataOBJ.ID << ", Name: " << stdntNode->dataOBJ.name << ", Department: " << stdntNode->dataOBJ.department << ", GPA: " << stdntNode->dataOBJ.GPA << endl;
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

  void printAll()
  {
    inOrder(this->root);
  }

  void printDepartmentReport()
  {
    LoadDepartmentCounter(this->root);
    for (const auto &counter : departmentCounters)
    {
      cout << counter.first << ": " << counter.second << " Students\n";
    }
  }

  bool search(StudentNode* current, int ID)
  {
    while(true)
    {
      if (current == nullptr)
      {
        cout << "Item Does not Exist In The Tree" << endl;
        return false;
      }
      else if (current->getID() == ID)
      {
        cout << "Student's data is Found\n";
        this->printStuData(current);
        return true;
      }
      else if (ID > current->getID())
      {
        current = current->right;
      }
      else
      {
        current = current->left;
      }
    }
  }

  bool search4Student(int ID)
  {
    return search(root, ID);
  }

  StudentNode* findMin(StudentNode* current)
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

  StudentNode* findMin()
  {
    return findMin(root);
  }

  StudentNode* findMax(StudentNode* current)
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

  StudentNode* findMax()
  {
    return findMax(root);
  }


  StudentNode* deleteStudentNode(StudentNode* current, int ID)
  {
    if (current == nullptr)
    {
      return 0;
    }

    if (ID > current->getID()) // Item exists in right subtree
    {
      // Make the right of the current StudentNode be the updated subtree (After deletion)
      current->right = deleteStudentNode(current->right, ID);
    }
    else if (ID < current->getID()) // Item exists in left subtree
    {
      // Make the left of the current StudentNode be the updated subtree (After deletion)
      current->left = deleteStudentNode(current->left, ID);
    }
    else // If current StudentNode is the StudentNode i want to delete
    {
      // IF current StudentNode is a leaf StudentNode
      if (current->right == nullptr && current->left == nullptr)
      {
        // Delete the current StudentNode and return nullptr to the parent StudentNode to point at it
        delete current;
        return nullptr;
      }
      // Has one child (right child)
      else if (current->right != nullptr && current->left == nullptr)
      {
        // Move current StudentNode to be the right StudentNode (point at right subtree) and Deletes the the previous StudentNode (current StudentNode before moving it)
        StudentNode* prev = current; 
        current = current->right;
        delete prev;
        return current;
      }
      // Has one child (left child)
      else if (current->left != nullptr && current->right == nullptr)
      {
        // Move current StudentNode to be the left StudentNode (point at right subtree) then Deletes the previous StudentNode (current StudentNode before moving it);
        StudentNode* prev = current; 
        current = current->left;
        delete prev;
        return current;
      }
      // Has Two children
      else 
      {
        // Successor (minimum StudentNode of the right subtree)
        StudentNode* successor = findMin(current->right);
        // Move the successor data into current StudentNode then delete the successor StudentNode and return the updated current StudentNode to make parent point at it
        current->dataOBJ = successor->dataOBJ;
        // Make the current StudentNode point at the right subtree after deleting the successor StudentNode from it
        current->right = deleteStudentNode(current->right, successor->getID());
      }
    }
    // Balance Factor = Height of left subtree - Height of right subtree
    int BF = getBalanceFactor(current);
    
    // StudentNode From Right Subtree was Deleted and Imbalance came from left of left Subtree.
    if (BF == 2 && getBalanceFactor(current->left) >= 0) // BF of left subtree can be 0 or 1 only for this case because it's already balanced subtree
    {
      return LL_Rotation(current);
    }
    // StudentNode From Right Subtree was Deleted and Imbalance came from Right of left Subtree (left right StudentNode).
    else if (BF == 2 && getBalanceFactor(current->left) == -1)
    {
      return LR_Rotation(current);
    }
    // StudentNode From Left Subtree was Deleted and Imbalance came from Right of Right Subtree.
    else if (BF == -2 && getBalanceFactor(current->right) <= 0) // BF of right subtree can be 0 or -1 only for this case because it's already balanced subtree
    {
      return RR_Rotation(current);
    }
    // StudentNode From Left Subtree was Deleted and Imbalance came from Left of Right Subtree (Right Left StudentNode).
    else if (BF == -2 && getBalanceFactor(current->right) == 1)
    {
      return RL_Rotation(current);
    }
    return current;
  }

  void deleteStudentNode(int ID)
  {
    root = deleteStudentNode(this->root, ID);
  }

};

int main()
{
    AVL students;
    ifstream myFile;

    myFile.open("Test.txt", ios::in);
    int ID;
    string name, department;
    double GPA;
    string line = "";
    int numOfStudents = 0;

    // Read Number of Students
    getline(myFile, line);
    numOfStudents = stoi(line);

    // Read first student
    getline(myFile, line); // Read ID
    ID = stoi(line);

    getline(myFile, line); // Read Name
    name = line;

    getline(myFile, line); // Read GPA
    GPA = stod(line);

    getline(myFile, line); // Read Department
    department = line;

    students.addStudent(Student(ID, name, department, GPA));
    for (int i = 1; i < numOfStudents; i++)
    {
        getline(myFile, line); // Read ID
        ID = stoi(line);

        getline(myFile, line); // Read Name
        name = line;

        getline(myFile, line); // Read GPA
        GPA = stod(line);

        getline(myFile, line); // Read Department
        department = line;

        students.addStudent(Student(ID, name, department, GPA));
    }

    students.addStudent(Student(11, "Bozo", "IT", 3.3));
    students.addStudent(Student(12, "Bozo", "IT", 3.3));
    students.addStudent(Student(13, "Bozo", "IT", 3.3));
    students.deleteStudentNode(13);
    students.deleteStudentNode(8);
    students.deleteStudentNode(5);
    students.printAll();
    students.printDepartmentReport();
    //students.search4Student(11);
}