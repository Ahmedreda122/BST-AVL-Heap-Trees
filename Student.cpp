#include <bits/stdc++.h>
using namespace std;

struct Student
{
    int ID;
    string name;
    string department;
    double GPA;
    Student(int ID, string name, string department, double GPA) : ID(ID), name(name), department(department), GPA(GPA) {}
    Student() : ID(0), name(""), department(""), GPA(0.0) {}
};