#include <bits/stdc++.h>
#include "Student.cpp"
using namespace std;

map<string, int> departmentCount;

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

int main()
{
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

    BST students(Student(ID, name, department, GPA));

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

    // students.addStudent(Student(11, "Bozo", "IT", 3.3));
    // students.addStudent(Student(12, "Bozo", "IT", 3.3));
    // students.addStudent(Student(13, "Bozo", "IT", 3.3));
    students.printAll();
    students.addStudent(Student(11, "Bozo", "IT", 3.3));
    students.printAll();
    students.printDepartmentReport();
    students.searchStudent(11);
}
