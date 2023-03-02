#ifndef EMPLOYEE_H_
#define EMPLOYEE_H_
#include "worker.h"
class Employee: public Worker{
    public:
        Employee(int id, string name, int did);
        virtual void showInfo();
        virtual string getDeptName();
};

#endif 