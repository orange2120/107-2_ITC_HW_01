/****************************************************************************
  FileName     [ admissionSys.cpp ]
  PackageName  [ admissionSys ]
  Synopsis     [ Define member functions of class admissionSys ,student and department ]
  Author       [ Orange Hsu ]
  Copyright    [ Copyleft(c) 2019-present , NTU, Taiwan ]
****************************************************************************/
#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "admissionSys.h"
using namespace std;

//
// Member functions of admissionSys class
//
void admissionSys::readFile(const string &stuPath, const string &deptPath)
{
    ifstream stu;
    ifstream dept;
    string str;

    try
    {
        stu.open(stuPath.c_str(), ifstream::in);
        dept.open(deptPath.c_str(), ifstream::in);
    }
    catch (std::ifstream::failure e)
    {
        cerr << "Exception opening file\n";
    }

    while(getline(stu, str, '\n'))
    {
        istringstream line(str);
        vector<uint16_t> stuDept;
        uint16_t id, g1, g2, g3;
        uint16_t tmp = 0;

        // read student ID
        line >> id;
        line >> g1;
        line >> g2;
        line >> g3;
        
        // read departments
        while (line >> tmp)
            stuDept.push_back(tmp);

        // create student object
        stus.push_back(new student(id, g1, g2, g3, stuDept));
    }

    while(getline(dept, str, '\n'))
    {
        istringstream line(str);
        uint16_t tmp[2] = {0};
        float tmpF[3] = {0.0};

        line >> tmp[0];
        line >> tmpF[0];
        line >> tmpF[1];
        line >> tmpF[2];
        line >> tmp[1];

        depts.push_back(new department(tmp[0], tmpF[0], tmpF[1], tmpF[2], tmp[1]));
    }

    stu.close();
    dept.close();
}

void admissionSys::writeOutput(const string &path)
{
    ofstream ofs;

    try
    {
        ofs.open(path.c_str(), ofstream::out);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    for (uint16_t i = 0; i < stus.size(); ++i)
        ofs << stus[i] << endl;

    ofs.close();
}

void admissionSys::admit()
{

}

//
// Member functions of student class
//
student::student(vector<uint16_t> &v)
{

}

ostream &operator<<(ostream &os, const student &s)
{
    return (os << setw(5) << s.id << " " << s.admitted);
}

// 
// Member functions of department class
//


/*
size_t
myStrGetTok(const string& str, string& tok, size_t pos = 0,
            const char del = ' ')
{
   size_t begin = str.find_first_not_of(del, pos);
   if (begin == string::npos) { tok = ""; return begin; }
   size_t end = str.find_first_of(del, begin);
   tok = str.substr(begin, end - begin);
   return end;
}
*/