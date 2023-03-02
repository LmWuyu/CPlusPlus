#ifndef WORKER_H_
#define WORKER_H_
#include <iostream>
#include <string>
using namespace std;

class Worker {
    public:
        Worker();
        virtual void showInfo() = 0;
        virtual string getDeptName() = 0;
        int m_Id;
        string m_Name;
        int m_DeptId;
};

#endif 
