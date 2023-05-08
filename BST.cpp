#include <bits/stdc++.h>
#include "Student.cpp"
using namespace std;

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

public:
    BST(Student student) : student(student), left(nullptr), right(nullptr) {}
    void addStudent(Student student);
    void searchStudent(int ID);
    void deleteStudent(int ID);
};
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
    // if student.ID == this->student.ID do nothing as it's already exist
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
        if (!node->left && !node->right) // Case: 1 if there is no left/right subtree (has no child)
        {
            node = nullptr;
        }
        // Case: 2 if there is only one child
        else if (!node->left) // If there is no left
        {
            BST *temp = node->right;
            delete node;
            node = temp;
        }
        else if (!node->right) // If there is no right
        {
            BST *temp = node->left;
            delete node;
            node = temp;
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
    if (this->student.ID == ID && !this->left && !this->right) // if it's the root then do nothing
    {
        cout << "Can't delete the root\n";
        return;
    }
    deleteNode(ID, this);
}

int main()
{
    BST bst(Student(50, "Abdo", "CS", 4.441));
    bst.addStudent(Student(5, "Boda", "IS", 4.442));
    bst.addStudent(Student(90, "7mada", "IT", 4.443));
    bst.addStudent(Student(6, "Body", "IP", 4.444));

    bst.searchStudent(90);
    bst.deleteStudent(50);
    // bst.searchStudent(90);
    // bst.searchStudent(1);
}
