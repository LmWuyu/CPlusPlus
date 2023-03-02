#include "manager.h"

Manager::Manager(int id, string name, int did)
{
    // 初始化
    m_Id = id;
    this->m_Name = name;
    m_DeptId = did;
}

void Manager::showInfo()
{
    cout << "职工编号 " << this->m_Id << "\t";
    cout << "职工姓名 " << this->m_Name << "\t";
    cout << "岗位名称 " << this->getDeptName() << "\t";
    cout << "岗位职责:完成老板交给的任务，并给员工布置任务" << endl;
}
// 获取岗位名称
string Manager::getDeptName()
{
    return string("经理"); // 返回const char *
}