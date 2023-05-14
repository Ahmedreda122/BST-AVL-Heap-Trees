#include <bits/stdc++.h>
using namespace std;

struct Student
{
  int ID;
  string name;
  string department;
  double GPA;
  Student(int ID, string name, string department, double GPA) : ID(ID), name(name), department(department), GPA(GPA) {}
  Student():ID(0),GPA(4.4){}

  Student& operator=(const Student& other)
  {
    if (this != &other)
    {
      this->ID = other.ID;
      this->name = other.name;
      this->department = other.department;
      this->GPA = other.GPA;
    }
    return *this;
  }

  Student(const Student& other)
  {
    this->ID = other.ID;
    this->name = other.name;
    this->department = other.department;
    this->GPA = other.GPA;
  }
};
