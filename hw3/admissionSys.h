/****************************************************************************
  FileName     [ admissionSys.h ]
  PackageName  [ admissionSys ]
  Synopsis     [ Define member functions of class admissionSys ,student and department ]
  Author       [ Orange Hsu ]
  Copyright    [ Copyleft(c) 2019-present , NTU, Taiwan ]
****************************************************************************/
#ifndef __ADMISSION_SYS_H__
#define __ADMISSION_SYS_H__

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef pair<float, uint16_t> PFU;
#define MP make_pair

class student
{
  friend class admissionSys;

  public:
    student(const uint16_t &i, const float &s1, const float &s2, const float &s3,
            vector<uint16_t> &v) : id(i), score{s1, s2, s3}, choice(v){};
    student(){};
    ~student(){};

    bool isAdmitted() { return admitted; }
    float getScoreSum(const float *) const;

    friend ostream &operator<<(ostream &, const student &);

  private:
    bool admitted = false;
    uint16_t id = 0;
    float score[3] = {0};
    int admittedDept = -1;
    uint16_t choiceIdx = 0; // current first choice
    vector<uint16_t> choice;
};

class department
{
  friend class admissionSys;
  public:
    department(){};
    department(const uint16_t &i, const uint16_t &qt, const float &w1,
      const float &w2, float &w3) : id(i), quota(qt), weight{w1, w2, w3} {};
    ~department(){};
    bool full() const { return pq.size() > quota; }

  private:
    uint16_t id = 0;
    uint16_t quota = 0;
    priority_queue< PFU, vector<PFU>, greater<PFU>> pq;
    float weight[3] = {0.0};
};

class admissionSys
{
    public:
      admissionSys(){};
      ~admissionSys(){};
      void readFile(const string &, const string &);
      void writeOutput(const string &);
      void admit();

    private:
      vector<student *> stus;
      vector<department *> depts;
};

#endif