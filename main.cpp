#include "Trees.cpp"

using namespace std;

void printMenu();
void enterStudentData(int& ID, string& name, string& department, double& GPA);

int main()
{
  while (true)
  {
    cout << "\nChoose Data Structure:" << endl;
    cout << "  1- BST\n  2- AVL\n  3- MinHeap\n  4- MaxHeap\n  5- Exit Program\n\n> ";

    int choice;
    int Secondchoice;

    int ID;
    string name;
    string department;
    double GPA;

    cin >> choice;

    // BST
    if (choice == 1)
    {
      while(true)
      {
        printMenu();
        cin >> Secondchoice;
        // Add Student
        if (Secondchoice == 1)
        {

        }
        // Delete Student Node
        else if (Secondchoice == 2)
        {

        }
        // Search for a Student By ID
        else if (Secondchoice == 3)
        {
          
        }
        // Print All
        else if (Secondchoice == 4)
        {

        }
        // Return to Main Menu
        else if (Secondchoice == 5)
        {
          break;
        }
      }
    }
    // AVL Tree
    else if (choice == 2)
    {
      AVL tree;
      while(true)
      {
        printMenu();
        cin >> Secondchoice;
        // Add Student
        if (Secondchoice == 1)
        {
          enterStudentData(ID, name, department, GPA);
          tree.addStudent(Student(ID, name, department, GPA));
          cout << "\nStudent Added Successfully" << endl;
        }
        // Delete Student Node
        else if (Secondchoice == 2)
        {
          cout << "\nEnter Student ID:\n>";
          cin >> ID;
          tree.deleteStudentNode(ID);
        }
        // Search for a Student By ID
        else if (Secondchoice == 3)
        {
          cout << "\nEnter Student ID to Search for him/her:\n\n> ";
          cin >> ID;
          tree.search4Student(ID);
        }
        // Print All
        else if (Secondchoice == 4)
        {
          tree.printAll();
          tree.printDepartmentReport();
        }
        // Return to Main Menu
        else if (Secondchoice == 5)
        {
          break;
        }
      }
    }
    else if (choice == 3)
    {
      while(true)
      {
        printMenu();
        cin >> Secondchoice;
        // Add Student
        if (Secondchoice == 1)
        {

        }
        // Delete Student Node
        else if (Secondchoice == 2)
        {

        }
        // Search for a Student By ID
        else if (Secondchoice == 3)
        {
          
        }
        // Print All
        else if (Secondchoice == 4)
        {

        }
        // Return to Main Menu
        else if (Secondchoice == 5)
        {
          break;
        }
      }
    }
    else if (choice == 4)
    {
      while(true)
      {
        printMenu();
        cin >> Secondchoice;
        // Add Student
        if (Secondchoice == 1)
        {

        }
        // Delete Student Node
        else if (Secondchoice == 2)
        {

        }
        // Search for a Student By ID
        else if (Secondchoice == 3)
        {
          
        }
        // Print All
        else if (Secondchoice == 4)
        {

        }
        // Return to Main Menu
        else if (Secondchoice == 5)
        {
          break;
        }
      }  
    }
    else if (choice == 5)
    {
      return 0;
    }
  }
}

void printMenu()
{
  
  cout << "\nChoose One Option to Perform\n  1- Add student\n  2- Remove student\n  3- Search student\n  4- Print All (sorted by id)\n  5- Return to main menu\n\n> ";
}

void enterStudentData(int& ID, string& name, string& department, double& GPA)
{
  cout << "\nEnter Student's ID: \n\n> ";
  cin >> ID;
  cout << "Enter Student's Name: \n\n> ";
  cin >> name;
  cout << "Enter Student's Department: \n\n> ";
  cin >> department;
  cout << "Enter Student's GPA: \n\n> ";
  cin >> GPA;
}


