#pragma once // 保证头文件只被编译一次
#include "boss.h"
#include "employee.h"
#include "manager.h"

#include <fstream>
#include <iostream>
#define FILENAME "test.txt" // 宏定义

using namespace std;
#ifndef WORKERMANAGER_H
#define WORKERMANAGER_H
#include "worker.h"
// 一般在头文件中做声明，在源文件里实现。
class WorkerManager
{
public:
    // 记录文件中的人数个数
    int m_EmpNum;
    // 员工数组指针
    Worker **m_EmpArray;
    // 添加属性判断文件是否为空
    bool m_FileIsEmpty;
    // 统计文件中的人数
    int get_EmpNum();
    WorkerManager();
    ~WorkerManager();
    // 显示菜单
    void Show_Menu();
    // 退出操作
    void exitSystem();
    // 添加职工
    void Add_Emp();
    // 保存文件
    void save();
    // 初始化职工
    void init_Emp();
    // 显示职工
    void show_Emp();
    // 删除职工
    void Del_Emp();

    // 判断职工是否存在

    // 根据职工编号判断职工是否存在，若存在返回职工在数组中的位置，不存在返回-1
    int IsExist(int id);

    // 修改职工
    void Mod_Emp();
    // 查找员工
    void Find_Emp();

    // 排序算法
    void Sort_Emp();
    // 清空文件
    void Clear_File();
};

#endif // WORKERMANAGER_H