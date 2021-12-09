#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>

using namespace std;
static int byteOffset = 0;
struct employee {

    char employee_ID[13];
    char Dept_ID[13];
    char employee_name[50];
    char Employee_Position[50];
};

class department {
public:
    char Dept_ID[30];
    char Dept_Name[50];
    char Dept_Manager[50];
};

struct PIndex_Emp {
    int Byteoffset;
    char EID[10];

    bool operator<(const PIndex_Emp &r) const { // for the sort function
        return strcmp(EID, r.EID) < 0;
    }
};

struct PIndex_Dept {
    int by;
    char dept_ID[13];

    bool operator<(const PIndex_Dept &r) const { // for the sort function
        return strcmp(dept_ID, r.dept_ID) < 0;
    }
};

struct SIndex {
    char ID[10];
    char name[20];

    bool operator<(const SIndex &r) const { // for the sort function
        if (strcmp(name, r.name) == 0)
            return strcmp(ID, r.ID) < 0;
        return strcmp(name, r.name) < 0;
    }
};

void add_Primary(int byte ,string id, string fileName){

    fstream file;
    file.open(fileName,ios::app);
    file<<id<<'|'<<byte<<"\n";
    sort(id);
}

void add_employee() {

    fstream file;
    file.open("Employee_file.txt",ios::app);
    string input="|";
    employee e;
    cout << "pls Enter the Employee ID : " << endl;
    cin >> e.employee_ID;
    input =input.append(e.employee_ID)+'|';

    cout << "pls Enter the Department ID : " << endl;
    cin >> e.Dept_ID;
    input = input + e.Dept_ID +'|';

    cout << "pls Enter the Employee Name : " << endl;
    cin >> e.employee_name;
    input = input + e.employee_name+ '|';

    cout << "pls Enter the Employee position : " << endl;
    cin >> e.Employee_Position;
    input = input + e.Employee_Position;


    file <<to_string(input.size())<<input<<'$' ;
    file.close();

    byteOffset+=input.size();
    add_Primary(byteOffset, e.employee_ID, "PrimaryEmp.txt");

}
void add_Department() {

    fstream file;
    file.open("Department_file.txt",ios::app);
    string input="|";
    department d;
    cout << "pls Enter the Department ID : " << endl;
    cin >> d.Dept_ID;
    input =input.append(d.Dept_ID)+'|';

    cout << "pls Enter the Department Name : " << endl;
    cin >> d.Dept_Name;
    input = input + d.Dept_Name +'|';

    cout << "pls Enter the Department Manager : " << endl;
    cin >> d.Dept_Manager;
    input = input + d.Dept_Manager+ '|';

    file <<to_string(input.size())<<input<<'$' ;
    file.close();

    byteOffset+=input.size();
    add_Primary(byteOffset, d.Dept_ID, "PrimaryDep.txt");

}

void removeEmployee() {
    fstream file;
    employee e;
    string input;
    file.open("Employee_file.txt", ios::app);
    file.seekp(0, ios::beg);
    cout << "pls enter the id of the employee : " << endl;
    cin >> input;
    if (input != e.employee_ID) {
        file.put('*');
        cout<<"recored of employee "<<input<<" is deleted"<<endl;
    }
}


//void delete_employee(char employee_ID[13]) {}

void print_ID(char departmentID[13]) {

}

void print(char employeeID[13]) {

}

void delete_department(char departmentID[30]) {

}

void print_de_ID(char departmentID[30]) {

}

void print_dp_NAME(char departmentName[50]) {

}

void makeQuery(string message) {
    string temp = ""; //Carries the query itself.
    char splitter = '=';
    string temp2 = ""; //Carries the argument of the query.
    for (int i = 0; i < (int) message.size(); i++) {
        if (message[i] != splitter) {
            temp += message[i];
        } else if (message[i] == splitter) {
            break;
        }
        for (int j = 0; j < message.size(); i++) {
            if (message[j] != splitter) {
                continue;
            } else if (message[j] == splitter) {
                for (int k = j + 1; k < message.size(); k++) {
                    temp2 += message[k];
                }
                break;
            }
        }
        temp2.erase(std::remove_if(temp2.begin(), temp2.end(), ::isspace), temp2.end()); //To remove whitespaces
        string mess1 = "select all from Employee where Dept_ID";
        string mess2 = "select all from Employee where Dept_ID";
        string mess3 = "select Employee_Name from Employee where Employee";
        if (temp == mess1) {

        } else if (temp == mess2) {

        } else if (temp == mess3) {

        } else {
            cout << "Please enter a valid query\n";
        }
    }

}

int main() {
    fstream Employee_file;
    fstream Department_file;
    fstream primary_INdx;
    fstream Secondary_INdx;
    Employee_file.open("Employee_file.txt", ios::app);
    Department_file.open("Department_file.txt",ios::app);
    primary_INdx.open("PrimaryEmp.txt",ios::app);
    primary_INdx.open("PrimaryDep.txt",ios::app);
    int n;
    cin>>n;
    for (int i = 0; i <n ; ++i) {
        add_employee();
        add_Department();

    }//removeEmployee();
}