//
// Created by marks on 12/5/2021.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include<bits/stdc++.h>
using namespace std;

class Employee{
public:
    char Employee_ID[13];
    char Employee_Name[50];
    char Employee_Position[50];
    char Dept_ID[30];

};

class Department{
public:
    char Dept_ID[30];
    char Dept_Name[50];
    char Dept_Manager[50];
};

int main(){
    fstream Employee_File;
    fstream Department_File;
    Employee_File.open("C:\\Users\\marks\\CLionProjects\\Files-assignment-1");
    return 0;
}