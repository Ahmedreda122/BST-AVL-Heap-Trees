#include "Student.cpp"
using namespace std;

// For BST
map<string, int> departmentCount;

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

// ___________________________________<<<<***<AVL Tree>****>>>>_______________________________________________
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

  StudentNode* insertion(Student newStdnt, StudentNode* current, bool& isExist)
  {
    if (current == nullptr)
    {
      StudentNode* newNode = new StudentNode(newStdnt);
      current = newNode;
      return current;
    }
    else if (newStdnt.ID > current->getID())
    { 
      current->right = insertion(newStdnt, current->right, isExist);
    }
    else if (newStdnt.ID < current->getID())
    {
      current->left = insertion(newStdnt, current->left, isExist);
    }
    else
    {
      // NO DUPLICATES ALLOWED
      isExist = true;
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


  bool addStudent(Student newStdnt)
  {
    bool isExist = false;
    root = insertion(newStdnt, this->root, isExist);
    if (isExist)
    {
      cout << "This Student ID Added already!" << endl;
      return false;
    }
    return true;
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

  StudentNode* LR_Rotation(StudentNode* current) { // Double Rotition (Left then Right)
    StudentNode* child = current->left;
    StudentNode* GrChild = child->right;

    current->left = GrChild->left;
    child->right = GrChild->right;

    GrChild->left = child;
    GrChild->right = current; 

    return GrChild;
    // RR_Rotation(child);
    // LL_Rotation(current);
  }
  
  StudentNode* RL_Rotation(StudentNode* current) { // Double Rotition (Right then Left)
    StudentNode* child = current->right;
    StudentNode* GrChild = child->left;

    current->right = GrChild->left;
    child->left = GrChild->right;

    GrChild->right = child;
    GrChild->left = current;

    return GrChild;
    //LL_Rotation(child);
    //RR_Rotation(current);
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
    cout << "ID: " << stdntNode->dataOBJ.ID << "| Name: " << stdntNode->dataOBJ.name << "| Department: " << stdntNode->dataOBJ.department << "| GPA: " << stdntNode->dataOBJ.GPA << endl;
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
    printDepartmentReport();
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

// ___________________________________<<<<***<BST>****>>>>_______________________________________________
class BST
{
private:
    Student student;
    BST *left;
    BST *right;
    bool searchStudentHelper(int ID);
    BST *minNode()
    {
        BST *current = this;
        while (current && current->left)
            current = current->left;
        return current;
    }
    BST *deleteNode(int ID, BST *node);
    void specialDelete(BST *parent, BST *Child);

public:
    BST(ifstream& file)
    {
      left = nullptr;
      right = nullptr;
  
      file.open("Test.txt", ios::in);
      int ID;
      string name, department;
      double GPA;
      string line = "";
      int numOfStudents = 0;

      // Read Number of Students
      getline(file, line);
      numOfStudents = stoi(line);

      // Read first student
      getline(file, line); // Read ID
      ID = stoi(line);

      getline(file, line); // Read Name
      name = line;

      getline(file, line); // Read GPA
      GPA = stod(line);

      getline(file, line); // Read Department
      department = line;

      this->student.addData(ID, name, department, GPA);

      for (int i = 1; i < numOfStudents; i++)
      {
          getline(file, line); // Read ID
          ID = stoi(line);

          getline(file, line); // Read Name
          name = line;

          getline(file, line); // Read GPA
          GPA = stod(line);

          getline(file, line); // Read Department
          department = line;

          this->addStudent(Student(ID, name, department, GPA));
      }
    }
    BST(Student student) : student(student), left(nullptr), right(nullptr) {}
    void addStudent(Student student);
    void searchStudent(int ID);
    void deleteStudent(int ID);
    void printAll();
    void printDepartmentReport();
};

void BST::printDepartmentReport()
{
    departmentCount[this->student.department]++;
    if (left)
    {
        left->printDepartmentReport();
    }
    else if (right)
    {
        right->printDepartmentReport();
    }
    else
    {
        cout << "\nDepartment Report:\n";
        for (const auto &count : departmentCount)
        {
            cout << count.first << ": " << count.second << " students\n";
        }
    }
}
void BST::printAll()
{
    if (left)
    {
        left->printAll();
    }
    cout << "ID: " << student.ID << ", Name: " << student.name << ", Department: " << student.department << ", GPA: " << student.GPA << endl;
    if (right)
    {
        right->printAll();
    }
}
void BST::addStudent(Student student)
{
    if (student.ID < 0 || student.ID > 100)
    {
        cout << "ID should be between 0 and 100\n";
        return;
    }
    if (student.ID < this->student.ID)
    {
        if (!left) // if there is no left student (left == nullptr)
        {
            left = new BST(student);
        }
        else
        {
            left->addStudent(student); // call addStudent method on the left subtree of the current node
        }
    }
    else if (student.ID > this->student.ID)
    {
        if (!right) // if there is no right student (right == nullptr)
        {
            right = new BST(student);
        }
        else
        {
            right->addStudent(student); //  call addStudent method on the right subtree of the current node
        }
    }

    else // if student.ID == this->student.ID, update the existing node's data
    {
        this->student = student;
    }
}
void BST::searchStudent(int ID)
{
    if (!searchStudentHelper(ID))
    {
        cout << "Student with ID " << ID << " not found.\n";
    }
}
bool BST::searchStudentHelper(int ID)
{
    if (ID == this->student.ID)
    {
        cout << "Student ID: " << this->student.ID << '\n';
        cout << "Student Name: " << this->student.name << '\n';
        cout << "Student Department: " << this->student.department << '\n';
        cout << "Student GPA: " << this->student.GPA << '\n';
        return true;
    }
    if (ID < this->student.ID)
    {
        return (left && left->searchStudentHelper(ID));
    }
    return (right && right->searchStudentHelper(ID));
}
void BST::specialDelete(BST *parent, BST *child)
{
    // Instead of deleting the node and returning its child
    // we copy the child's data and remove it, effectively replacing the node with the child
    // This is to avoid deleting the root node, then loose its subtrees as it's the root

    // copy the child's data into the current node
    parent->student.ID = child->student.ID;
    parent->student.name = child->student.name;
    parent->student.department = child->student.department;
    parent->student.GPA = child->student.GPA;
    parent->left = child->left;   // copy the child's left subtree into the current node's left subtree
    parent->right = child->right; // copy the child's right subtree into the current node's right subtree
    delete child;
}

BST *BST::deleteNode(int ID, BST *node)
{
    if (!node) // There is no node
        return nullptr;
    if (ID > node->student.ID) // If the ID is in the right subtree
    {
        node->right = deleteNode(ID, node->right);
    }
    else if (ID < node->student.ID) // If the ID is in the left subtree
    {
        node->left = deleteNode(ID, node->left);
    }
    else // if ID is found (node is found) (==)
    {
        if (!node->left && !node->right) // Case: 1 if there is no left/right subtree (has no child) (a leaf)
        {
            delete node;
            node = nullptr;
        }
        // Case: 2 if there is only one child
        else if (!node->left) // If there is no left
        {
            specialDelete(node, node->right);
        }
        else if (!node->right) // If there is no right
        {
            specialDelete(node, node->left);
        }
        // Case: 3 if there is 2 child then use successor
        else
        {
            BST *min = node->right->minNode();
            node->student.ID = min->student.ID;
            node->student.name = min->student.name;
            node->student.department = min->student.department;
            node->student.GPA = min->student.GPA;
            node->right = deleteNode(node->student.ID, node->right);
        }
    }
    return node;
}

void BST::deleteStudent(int ID)
{
    deleteNode(ID, this);
}

class maxHeap{
    private:
    int size;
    int capacity = 10;
    Student *heap;
    public:
    maxHeap(){
        size = 0;
        heap = new Student[capacity];
    }
    // this function to get child in the left of node
    int left(int node){
        int in = node*2+1;
        return(size <= in?-1:in);
    }
    // this function to get child in the right of node
    int right(int node){
        int in = node*2+2;
        return(size <= in?-1:in);
    }
    // this function to get parent of this node
    int parent(int node){
        int in = (node-1)/2;
        return(size <= in?-1:in);
    }
    void heapifyUp(int childPos){
        int parentPos = parent(childPos);
        if(childPos == 0||heap[parentPos].ID > heap[childPos].ID)return;
        swap(heap[childPos].ID,heap[parentPos].ID);
        heapifyUp(parentPos);
    }
    // insert in heap
    void push(Student student){
        // to recapacity heap to protect memory
        if(capacity == size){
            capacity *= 2;
            Student *newHeap = new Student[capacity];
            for (int i = 0; i < size; i++)newHeap[i] = heap[i];
            delete[] heap;
            heap = newHeap;
        }
        heap[size++] = student;
        heapifyUp(size-1);
    }
    void heapifyDown(int parentPos){
        int childPos = left(parentPos);
        int rightChild = right(parentPos);

        // no children
        if(childPos == -1)return;
        
        // to minimize between left and right child 
        if(rightChild != -1 && heap[childPos].ID < heap[rightChild].ID)
        childPos = rightChild;

        // swap between parent and least child
        if(heap[childPos].ID > heap[parentPos].ID){
            swap(heap[parentPos].ID, heap[childPos].ID);
            heapifyDown(childPos);
        }
    }
    // delete element
    void pop()
    {
        if(size < (capacity/4)){
            capacity = capacity/2;
            Student* newHeap = new Student[capacity];
            for (int i = 0; i < size; i++)newHeap[i] = heap[i];
            delete [] heap;
            heap = newHeap;
        }
        if(isEmpty())return;
        // delete parent then parent -> last child
        heap[0] = heap[--size]; 
        heapifyDown(0);
    }
    bool isEmpty(){
        return(size == 0);
    }
    int sizeHeap(){
        return(size);
    }
    void print(){
        for (int i = 0; i < size; i++)
        {
            cout << heap[i].ID << " " << heap[i].name << " " << heap[i].department << " " << 
            heap[i].GPA << endl;
        }cout << endl;
    }
    ~maxHeap(){
        delete[] heap;
    }

};


class minHeap{
    private:
    int size;
    int capacity = 10;
    Student *heap;
    public:
    minHeap(){
        size = 0;
        heap = new Student[capacity];
    }
    // this function to get child in the left of node
    int left(int node){
        int in = node*2+1;
        return(size <= in?-1:in);
    }
    // this function to get child in the right of node
    int right(int node){
        int in = node*2+2;
        return(size <= in?-1:in);
    }
    // this function to get parent of this node
    int parent(int node){
        int in = (node-1)/2;
        return(size <= in?-1:in);
    }
    void heapifyUp(int childPos){
        int parentPos = parent(childPos);
        if(childPos == 0||heap[parentPos].ID < heap[childPos].ID)return;
        swap(heap[childPos].ID,heap[parentPos].ID);
        heapifyUp(parentPos);
    }
    // insert in heap
    void push(Student student){
        // to recapacity heap to protect memory
        if(capacity == size){
            capacity *= 2;
            Student *newHeap = new Student[capacity];
            for (int i = 0; i < size; i++)newHeap[i] = heap[i];
            delete[] heap;
            heap = newHeap;
        }
        heap[size++] = student;
        heapifyUp(size-1);
    }
    void heapifyDown(int parentPos){
        int childPos = left(parentPos);
        int rightChild = right(parentPos);

        // no children
        if(childPos == -1)return;
        
        // to minimize between left and right child 
        if(rightChild != -1 && heap[childPos].ID > heap[rightChild].ID)
        childPos = rightChild;

        // swap between parent and least child
        if(heap[childPos].ID < heap[parentPos].ID){
            swap(heap[parentPos].ID, heap[childPos].ID);
            heapifyDown(childPos);
        }
    }
    // delete element
    void pop()
    {
        if(size < (capacity/4)){
            capacity = capacity/2;
            Student* newHeap = new Student[capacity];
            for (int i = 0; i < size; i++)newHeap[i] = heap[i];
            delete [] heap;
            heap = newHeap;
        }
        if(isEmpty())return;
        // delete parent then parent -> last child
        heap[0] = heap[--size]; 
        heapifyDown(0);
    }
    bool isEmpty(){
        return(size == 0);
    }
    int sizeHeap(){
        return(size);
    }
    void print(){
      for (int i = 0; i < size; i++)
        {
            cout << heap[i].ID << " " << heap[i].name << " " << heap[i].department << " " << 
            heap[i].GPA << endl;
        }cout << endl;
    }
    ~minHeap(){
        delete[] heap;
    }
};