#ifndef BOSS_H // 宏定义，注意复制的时候，这里不要重复，会报错
#define BOSS_H
#include "worker.h"
#include <iostream>
using namespace std;

class Boss : public Worker
{
    public:
        Boss(int id, string name, int did);
        // 显示个人信息
        virtual void showInfo(); // 实现
        // 获取岗位名称
        virtual string getDeptName(); // 实现
};

#endif // MANAGER_H