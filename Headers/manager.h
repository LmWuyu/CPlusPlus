#ifndef MANAGER_H
#define MANAGER_H
#include "worker.h"
#include <iostream>
using namespace std;

class Manager : public Worker
{
public:
    Manager(int id, string name, int did);
    // 显示个人信息
    virtual void showInfo(); // 实现
    // 获取岗位名称
    virtual string getDeptName(); // 实现
};

#endif // MANAGER_H