#include "Trees.cpp"

using namespace std;

void printMenu();
void printMenuHeap();
void enterStudentData(int &ID, string &name, string &department, double &GPA);
void loadFileIntoTree(ifstream &file, AVL &tree);
void loadFileIntoTree(ifstream &file, minHeap &tree);
void loadFileIntoTree(ifstream &file, maxHeap &tree);

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

    ifstream file;

    cin >> choice;

    // BST
    if (choice == 1)
    {
      // Initialize the BST tree with a file
      BST tree(file);
      while (true)
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
          tree.deleteStudent(ID);
        }
        // Search for a Student By ID
        else if (Secondchoice == 3)
        {
          cout << "\nEnter Student ID to Search for him/her:\n\n> ";
          cin >> ID;
          tree.searchStudent(ID);
        }
        // Print All
        else if (Secondchoice == 4)
        {
          cout << "\n---------------------------------------" << endl;
          tree.printAll();
          tree.printDepartmentReport();
          cout << "---------------------------------------\n"
               << endl;
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
      loadFileIntoTree(file, tree);
      while (true)
      {
        printMenu();
        cin >> Secondchoice;
        // Add Student
        if (Secondchoice == 1)
        {
          enterStudentData(ID, name, department, GPA);
          if (tree.addStudent(Student(ID, name, department, GPA)))
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
          cout << "\nEnter Student ID to Search for him/her:\n> ";
          cin >> ID;
          tree.search4Student(ID);
        }
        // Print All
        else if (Secondchoice == 4)
        {
          cout << "\n---------------------------------------" << endl;
          tree.printAll();
          cout << "---------------------------------------\n"
               << endl;
        }
        // Return to Main Menu
        else if (Secondchoice == 5)
        {
          break;
        }
      }
    }
    // MinHeap
    else if (choice == 3)
    {
      minHeap tree;
      loadFileIntoTree(file, tree);
      while (true)
      {
        printMenuHeap();
        cin >> Secondchoice;
        // Add Student
        if (Secondchoice == 1)
        {
          enterStudentData(ID, name, department, GPA);
          tree.push(Student(ID, name, department, GPA));
          cout << "\nStudent Added Successfully" << endl;
        }
        // // Delete Student Node
        // else if (Secondchoice == 2)
        // {
        //   cout << "\nEnter Student ID:\n>";
        //   cin >> ID;
        //   tree.pop(ID);
        // }
        // // Search for a Student By ID
        // else if (Secondchoice == 3)
        // {
        //   cout << "\nEnter Student ID to Search for him/her:\n\n> ";
        //   cin >> ID;
        //   tree.searchStudent(ID);
        // }
        // Print All
        else if (Secondchoice == 2)
        {
          cout << "\n---------------------------------------" << endl;
          tree.print();
          // tree.printDepartmentReport();
          cout << "---------------------------------------\n"
               << endl;
        }
        // Return to Main Menu
        else if (Secondchoice == 3)
        {
          break;
        }
      }
    }
    // MaxHeap
    else if (choice == 4)
    {
      maxHeap tree;
      loadFileIntoTree(file, tree);
      while (true)
      {
        printMenuHeap();
        cin >> Secondchoice;
        // Add Student
        if (Secondchoice == 1)
        {
          enterStudentData(ID, name, department, GPA);
          tree.push(Student(ID, name, department, GPA));
          cout << "\nStudent Added Successfully" << endl;
        }
        // Print All
        else if (Secondchoice == 2)
        {
          cout << "\n---------------------------------------" << endl;
          tree.print();
          // tree.printDepartmentReport();
          cout << "---------------------------------------\n"
               << endl;
        }
        // Return to Main Menu
        else if (Secondchoice == 3)
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
void printMenuHeap()
{

  cout << "\nChoose One Option to Perform\n  1- Add student\n  2- Print All (sorted by id)\n  3- Return to main menu\n\n> ";
}

void enterStudentData(int &ID, string &name, string &department, double &GPA)
{
  cout << "\nEnter Student's ID: \n> ";
  cin >> ID;
  cout << "\nEnter Student's Name: \n> ";
  cin >> name;
  cout << "\nEnter Student's Department: \n> ";
  cin >> department;
  cout << "\nEnter Student's GPA: \n> ";
  cin >> GPA;
}

void loadFileIntoTree(ifstream &file, AVL &tree)
{
  int ID;
  string name, department;
  double GPA;
  string line = "";
  int numOfStudents = 0;

  file.open("Test.txt", ios::in);

  // Read Number of Students
  getline(file, line);
  numOfStudents = stoi(line);

  for (int i = 0; i < numOfStudents; i++)
  {
    getline(file, line); // Read ID
    ID = stoi(line);

    getline(file, line); // Read Name
    name = line;

    getline(file, line); // Read GPA
    GPA = stod(line);

    getline(file, line); // Read Department
    department = line;

    tree.addStudent(Student(ID, name, department, GPA));
  }
}

void loadFileIntoTree(ifstream &file, minHeap &tree)
{
  int ID;
  string name, department;
  double GPA;
  string line = "";
  int numOfStudents = 0;

  file.open("Test.txt", ios::in);

  // Read Number of Students
  getline(file, line);
  numOfStudents = stoi(line);

  for (int i = 0; i < numOfStudents; i++)
  {
    getline(file, line); // Read ID
    ID = stoi(line);

    getline(file, line); // Read Name
    name = line;

    getline(file, line); // Read GPA
    GPA = stod(line);

    getline(file, line); // Read Department
    department = line;

    tree.push(Student(ID, name, department, GPA));
  }
}

void loadFileIntoTree(ifstream &file, maxHeap &tree)
{
  int ID;
  string name, department;
  double GPA;
  string line = "";
  int numOfStudents = 0;

  file.open("Test.txt", ios::in);

  // Read Number of Students
  getline(file, line);
  numOfStudents = stoi(line);

  for (int i = 0; i < numOfStudents; i++)
  {
    getline(file, line); // Read ID
    ID = stoi(line);

    getline(file, line); // Read Name
    name = line;

    getline(file, line); // Read GPA
    GPA = stod(line);

    getline(file, line); // Read Department
    department = line;

    tree.push(Student(ID, name, department, GPA));
  }
}