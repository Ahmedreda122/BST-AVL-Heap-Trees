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

public:
    BST(Student student) : student(student), left(nullptr), right(nullptr) {}
    void addStudent(Student student);
    void searchStudent(int ID);
};
void BST::addStudent(Student student)
{
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

int main()
{
    BST bst(Student(0, "Abdo", "CS", 4.441));
    bst.addStudent(Student(1, "Boda", "IS", 4.442));
    bst.addStudent(Student(2, "7mada", "IT", 4.443));

    bst.searchStudent(2);
}
