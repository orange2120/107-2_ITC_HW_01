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
#include <cassert>
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
        stu_id.erase(i);

        // student has been admitted or exceed the max choices size
        if (stus[i]->admitted || (stus[i]->choiceIdx >= stus[i]->choice.size()))
        {
            #ifdef DEBUG
            cout << "PASS" << endl;
            #endif
            continue;
        }

        #ifdef DEBUG
            cout << "S[" << setw(5) << setfill('0') << i + 1 << "]--C[" << stus[i]->choiceIdx << "]--";
        #endif

        department *currDept = depts[stus[i]->choice[stus[i]->choiceIdx++] - 1]; // get current department from student's choice list
        stus[i]->admitted = true;                                                // set student admitted at frist
        stus[i]->admittedDept = currDept->id;

        #ifdef DEBUG
        cout << "CID[" << currDept->id << "]" << endl;
        #endif

        // push score and student ID into department's admitted list
        currDept->pq.push(MP(stus[i]->getScoreSum(currDept->weight), stus[i]->id - 1));

        // the quota of the department has ran out
        if (currDept->full())
        {
            // set the last (the lowest score) student back to unadmitted, and pop out
            stus[currDept->pq.top().second]->admitted = false;
            stus[currDept->pq.top().second]->admittedDept = -1;
            stu_id.insert(currDept->pq.top().second);
            currDept->pq.pop();
        }
    }

    #ifdef DEBUG
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
        cout << "TOT.AD.S: " << tot_ad << endl;
    #endif
    
}

bool admissionSys::verify() const
{
    bool correct = true;
    for (const auto &student : stus)
    {
        uint16_t idx = 0;
        if(!student->admitted) {
            idx = depts.size();
        }
        else{
            for (; ; ++idx){
                if(student->choice[idx] == student->admittedDept)
                    break;
            }
        }
        for (uint16_t i = 0, totalDepts = depts.size(); i < idx && i < totalDepts; ++i)
        {
            if(student->admitted)
                assert(depts[student->choice[idx] - 1]->id == student->admittedDept);
            auto currentDep = depts[student->choice[i] - 1];
            float minScore = stus[currentDep->pq.top().second]->getScoreSum(currentDep->weight),
                  currentScore = student->getScoreSum(currentDep->weight);
            if (minScore < currentScore)
            {
                std::cerr << "Department[" << (currentDep->id - 1) << "] have a min score of " << minScore << ", but student[" << (student->id - 1) << "] has a higher score of " << currentScore << '\n';
                correct = false;
            }
            }
    }
    return correct;
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