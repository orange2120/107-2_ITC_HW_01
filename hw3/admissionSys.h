#ifndef __ADMISSION_SYS_H__
#define __ADMISSION_SYS_H__

#include <iostream>
#include <vector>
using namespace std;

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

class student
{
    public:
      student(vector<uint16_t> &);
      student(const uint16_t &i, const uint16_t &a, const uint16_t &b, const uint16_t &c,
       vector<uint16_t> &v) : id(i), g1(a), g2(b), g3(c), depts(v){};
      student() {};
      ~student(){};

      void clearScore() { score = 0.0; }

      friend ostream &operator<<(ostream &, const student &);

    private:
      uint16_t id = 0;
      uint16_t g1 = 0;
      uint16_t g2 = 0;
      uint16_t g3 = 0;
      int admitted = -1;
      float score = 0.0;
      vector<uint16_t> depts;
};

class department
{
    public:
      department(){};
      department(const uint16_t &i, const float &w1, const float &w2, float &w3,
      const uint16_t &ms) : id(i), w1(w1), w2(w2), w3(w3), maxStu(ms) {};
      ~department(){};

    private:
      uint16_t id = 0;
      uint16_t maxStu = 0;
      float w1, w2, w3;
      
};

#endif