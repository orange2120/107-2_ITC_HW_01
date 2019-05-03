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

    // read in students information
    while(getline(stu, str, '\n'))
    {
        istringstream line(str);
        vector<uint16_t> stuDept;
        uint16_t id;
        float g1, g2, g3;
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

    // read in departments information
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

        depts.push_back(new department(tmp[0], tmp[1], tmpF[0], tmpF[1], tmpF[2]));
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

    ofs << *stus[0];
    for (uint16_t i = 1; i < stus.size(); ++i)
        ofs << endl << *stus[i];

    ofs.close();
}

void admissionSys::admit()
{
    uint32_t nStus = stus.size();
    stu_id.reserve(nStus);
    for (uint32_t i = 0; i < nStus; ++i)
        stu_id.emplace(stus[i]->id - 1); // add student ID into unordered set
    
    while (!stu_id.empty())
    {
        auto i = *stu_id.begin();
        cout << "S[" << setw(5) << setfill('0') << i << "]--";

        stu_id.erase(i);

        // student has been admitted or exceed the max choices size
        if (stus[i]->admitted || (stus[i]->choiceIdx >= stus[i]->choice.size()))
        {
            cout << "PASS" << endl;
            continue;
        }

        department *currDept = depts[stus[i]->choice[stus[i]->choiceIdx++] - 1]; // get current department from student's choice list
        stus[i]->admitted = true;                                                // set student admitted frist
        stus[i]->admittedDept = currDept->id;

        cout << "C[" << stus[i]->choiceIdx << "]--"
             << "CID[" << currDept->id << "]" << endl;

        // push score and student ID into department's admitted list
        currDept->pq.push(MP(stus[i]->getScoreSum(currDept->weight), stus[i]->id - 1));

        // the quota of the department has saturated
        if (currDept->full())
        {
            // set the last student back to unadmitted
            stus[currDept->pq.top().second]->admitted = false;
            stus[currDept->pq.top().second]->admittedDept = -1;
            stu_id.insert(currDept->pq.top().second);
            currDept->pq.pop();   
        }
    }

    // for debugging
    for (uint8_t i = 0; i < depts.size(); ++i)
    {
        cout << "D[" << depts[i]->id << "].S.Size: " << depts[i]->pq.size() << endl;
    }

    uint16_t tot_ad = 0;
    for (uint32_t i = 0; i < stus.size(); ++i)
    {
        if (stus[i]->admittedDept != -1)
            tot_ad++;
    }
    cout << "AD.S: " << tot_ad << endl;
}

//
// Member functions of student class
//
// Caculate score by weighted sum of each subject
inline float student::getScoreSum(const float *w) const
{
    return (score[0] * w[0] + score[1] * w[1] + score[2] * w[2]);
}

ostream &operator<<(ostream &os, const student &s)
{
    return (os << setw(5) << setfill('0')<< s.id << " " << s.admittedDept);
}