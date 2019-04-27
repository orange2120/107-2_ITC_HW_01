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
    //ofs << setw(5) << setfill('0') << stus[0]->id << " " << stus[0]->admittedDept;
    for (uint16_t i = 1; i < stus.size(); ++i)
        ofs << endl << *stus[i];
        //ofs << endl << setw(5) << setfill('0') << stus[i]->id << " " << stus[i]->admittedDept;

    ofs.close();
}

/*
void admissionSys::admit()
{
    for (uint32_t i = 0; i < stus.size(); ++i)
    {
        uint16_t currDeptId = stus[i]->choice[0];
        uint16_t currDeptIdx = 0; // the index of department in student's choices
        float currScore = 0.0;

        while (!stus[i]->isAdmitted()) // the student hasn't be admitted
        {
            department *curDep = depts[stus[i]->choice[currDeptIdx]];

            if (currDeptId >= stus[i]->choice.size())
                break; // flunk

            currScore = stu[i]->getScore()
            
            if (curDep->admittedStu.size() < curDep->quota) // current department remain quota
            {
                stus[i]->admitted = currDeptId;
                break;
            }

            if (curDep->admittedStu.size() == curDep->quota) // the department is full
            {
                if (stu[i]->(s))

            }

            currDeptIdx++;
        }
    }
}*/

void admissionSys::admit()
{
    for (uint16_t k = 0; k < 10; ++k)
    {
        for (uint32_t i = 0; i < stus.size(); ++i)
        {
            cout << "S[" << setw(5) << setfill('0') << i << "]--";
            
            if (stus[i]->admitted || (stus[i]->choiceIdx >= stus[i]->choice.size()))
            {
                cout << "PASS" << endl;
                continue; // student has been admitted or exceed the max choices size
            }

            stus[i]->admitted = true;
            
            department* currDept = depts[stus[i]->choice[stus[i]->choiceIdx++] - 1]; // get current department from student's choice list
            stus[i]->admittedDept = currDept->id;
            cout << "C[" << stus[i]->choiceIdx << "]--" << "CID[" << currDept->id << "]" << endl;

            // push score and student ID into department's admitted list
            currDept->pq.push(MP(stus[i]->getScoreSum(currDept->weight), stus[i]->id - 1));
            
            // the quota of department saturated
            if (currDept->pq.size() > currDept->quota)
            {
                stus[currDept->pq.top().second]->admitted = false;
                stus[i]->admittedDept = -1;
                currDept->pq.pop();
            }
        }
    }

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
inline float student::getScoreSum(const float *w) const
{
    return (score[0] * w[0] + score[1] * w[1] + score[2] * w[2]);
}

ostream &operator<<(ostream &os, const student &s)
{
    return (os << setw(5) << setfill('0')<< s.id << " " << s.admittedDept);
}