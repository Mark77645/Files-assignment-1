#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <sstream>
#include <vector>
using namespace std;
static int byteOffsetemp = 0;
static int byteOffsetDep=0;
static int counter=0;
static vector<string> primary;
static vector<string> secoundry;
vector<int>primarysort;
vector<int>secoundrysort;
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
int binarySearch(int arr[], int p, int r, int num) {
    if (p <= r) {
        int mid = (p + r)/2;
        if (arr[mid] == num)
            return mid ;
        if (arr[mid] > num)
            return binarySearch(arr, p, mid-1, num);
        if (arr[mid] < num)
            return binarySearch(arr, mid+1, r, num);
    }
    return -1;
}
void sort_Primary(string filename){
    fstream file;
    int primaryKey;
    file.open(filename,ios::in);
    while (!file.eof()){
        string s;
        file>>s;
        primary.push_back(s);

    }
    file.close();

    file.open(filename,ios::in|ios::trunc);
    file.close();

    int size=primary.size();
    for ( string  x : primary) {
        stringstream geek(x);
        geek>>primaryKey;
        //بياخد اخر value  مرتين
        if(size==1) {
            break;
        };
        primarysort.push_back(primaryKey);
        size--;
    }
    sort(primarysort.begin(),primarysort.end());

    //sort the number of the primary
    file.open(filename,ios::out|ios::trunc);
    for (int i : primarysort) {
        int j=0;//بيبرينت space فالتانيه
        for (string x: primary) {

            stringstream geek(x);
            geek >> primaryKey;
            if (i == primaryKey&&j==0) {
                j++;
                file<<x<<"\n";
            }

        }

    }
    file.close();
    primary.clear();
    primarysort.clear();
};
/*
void sort_secoundry(string filename){
    fstream file;
    int primaryKey;
    file.open(filename,ios::in);
    while (!file.eof()){
        string s;
        file>>s;
        secoundry.push_back(s);

    }
    file.close();

    file.open(filename,ios::in|ios::trunc);
    file.close();

    int size=secoundry.size();
    for ( string  x : secoundry) {
        stringstream geek(x);
        geek>>primaryKey;
        //بياخد اخر value  مرتين
        if(size==1) {
            break;
        };
        secoundrysort.push_back(primaryKey);
        size--;
    }
    sort(secoundrysort.begin(),secoundrysort.end());

    //sort the number of the primary
    file.open(filename,ios::out|ios::trunc);
    for (int i : secoundrysort) {
        int j=0;//بيبرينت space فالتانيه
        for (string x: secoundry) {

            stringstream geek(x);
            geek >> primaryKey;
            if (i == primaryKey&&j==0) {
                j++;
                file<<x<<"\n";
            }

        }

    }
    file.close();
    secoundry.clear();
    secoundrysort.clear();
};*/
void add_Primary(int byte ,string id, string fileName){

    fstream file;
    file.open(fileName,ios::app);
    file<<id<<'|'<<byte<<"\n";
    file.close();
    sort_Primary(fileName);
};
void add_secoundry(int byte ,string name, string fileName){

    fstream file;
    file.open(fileName,ios::app);
    file<<name<<'|'<<byte<<"\n";
    file.close();
    //sort_secoundry(fileName);

};

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
    add_Primary(byteOffsetemp, e.employee_ID, "PrimaryEmp.txt");
    add_secoundry(byteOffsetemp, e.employee_name, "secoundryEmp.txt");
    byteOffsetemp+=input.size()+3;



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
    add_Primary(byteOffsetDep, d.Dept_ID, "PrimaryDep.txt");
    add_secoundry(byteOffsetDep, d.Dept_Name, "secoundryDep.txt");
    byteOffsetDep+=input.size()+3;


}


void remove_ll(int ID,string fileName,string filePrimary) {
    fstream file;
    int primaryKey;
    file.open(filePrimary,ios::in);

    while (!file.eof()){
        string s;
        file>>s;
        primary.push_back(s);
    }
    file.close();

    int arr[primary.size()-1];
    int size=primary.size();
    int i=0;

    for ( string  x : primary) {
        stringstream geek(x);
        geek>>primaryKey;
        //بياخد اخر value  مرتين
        if(size==1) {
            break;
        };
        primarysort.push_back(primaryKey);
        size--;
    }

    for (int j = 0; j <primarysort.size() ; ++j) {
        arr[j]=primarysort[j];

    }
    int var;
    for (int j = 0; j < sizeof(arr) ; ++j) {
        if(arr[j]==ID){
            var=j;
            break;
        }
    }
    string s=primary[var];
    int counter=0;
    string input="";
    for (int k = 0; k <s.size() ; ++k) {

        if(s[k]=='|'){
            counter++;
            continue;
        }
        if(counter==1){
            input+=s[k];

        }
    }
    int byte=0;
    string read;
    stringstream geek(input);
    geek>>byte;
    file.open(fileName,ios::out);
    file.seekp(byte+2,ios::beg);
    file.put('*');
    file.close();

}

void print_UsingID(int ID,string fileName,string filePrimary) {

    fstream file;
    int primaryKey;
    file.open(filePrimary,ios::in);

    while (!file.eof()){
        string s;
        file>>s;
        primary.push_back(s);
    }
    file.close();

    int arr[primary.size()-1];
    int size=primary.size();
    int i=0;

    for ( string  x : primary) {
        stringstream geek(x);
        geek>>primaryKey;
        //بياخد اخر value  مرتين
        if(size==1) {
            break;
        };
        primarysort.push_back(primaryKey);
        size--;
    }

    for (int j = 0; j <primarysort.size() ; ++j) {
        arr[j]=primarysort[j];

    }
    int var;
    for (int j = 0; j < sizeof(arr) ; ++j) {
        if(arr[j]==ID){
            var=j;
            break;
        }
    }
    string s=primary[var];
    int counter=0;
    string input="";
    for (int k = 0; k <s.size() ; ++k) {

        if(s[k]=='|'){
            counter++;
            continue;
        }
        if(counter==1){
            input+=s[k];

        }
    }
    int byte=0;
    string read;
    stringstream geek(input);
    geek>>byte;
    file.open(fileName,ios::in);
    file.seekg(byte,ios::beg);
    while(getline(file,read,'$')){
        cout<<read<<endl;
        break;


    }
    primary.clear();
    primarysort.clear();
}

int main() {
    int choice;
    do {
        fstream Employee_file;
        fstream Department_file;
        fstream primary_INdx;
        fstream Secondary_INdx;
        Employee_file.open("Employee_file.txt", ios::app);
        Department_file.open("Department_file.txt", ios::app);
        primary_INdx.open("PrimaryEmp.txt", ios::app);
        primary_INdx.open("PrimaryDep.txt", ios::app);
        Secondary_INdx.open("secoundryEmp.txt", ios::app);
        Secondary_INdx.open("secoundryDep.txt", ios::app);
        cout << "1-Add New Employee\n";
        cout << "2-Add New Department\n";
        cout << "3-Delete Employee(ID)\n";
        cout << "4-Delete Department(ID)\n";
        cout << "5-print Employee(ID)\n";
        cout << "6-print Employee(Dept_ID)\n";
        cout << "7-print Department(ID)\n";
        cout << "8-print Department(name)\n";
        cout << "9-Write a Query\n";
        cout << "10-Exit\n";
        cout << "select choice:\n";

        cin >>choice ;

        if (choice == 1) {
            add_employee();

        }
        else if (choice == 2) {
            add_Department();
        }
        else if (choice == 3) {
            int id;
            cout<<"pls enter the id";
            cin>>id;
            remove_ll(id,"Employee_file.txt","PrimaryEmp.txt");

        }
        else if (choice == 4) {
            int id;
            cout<<"pls enter the id";
            cin>>id;
            remove_ll(id,"Department_file.txt","PrimaryDep.txt");

        }
        else if (choice == 5) {
            int id;
            cout<<"pls enter the id";
            cin>>id;
            print_UsingID(id,"Employee_file.txt","PrimaryEmp.txt");

        }
        else if (choice == 6) {

        }
        else if (choice == 7) {
            int id;
            cout<<"pls enter the id";
            cin>>id;
            print_UsingID(id,"Department_file.txt","PrimaryDep.txt");

        }
        else if (choice == 8) {

        }
        else if (choice == 9) {

        }else if (choice==10){
            cout << "Exit" << endl;
            Employee_file.close();
            Department_file.close();
            primary_INdx.close();
            Secondary_INdx.close();
            return 0;
        }
        else{
            cout<<"write correct Number"<<endl;
        }


    } while (true);

}