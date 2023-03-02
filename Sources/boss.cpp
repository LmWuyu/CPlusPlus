#include "boss.h"

Boss::Boss(int id, string name, int did)
{
    // 初始化
    this->m_Id = id;
    this->m_Name = name;
    this->m_DeptId = did;
}
void Boss::showInfo()
{
    cout << "职工编号 " << this->m_Id << "\t";
    cout << "职工姓名 " << this->m_Name << "\t";
    cout << "岗位名称 " << this->getDeptName() << "\t";
    cout << "岗位职责:管理所有的事物" << endl;
}
// 获取岗位名称
string Boss::getDeptName()
{
    return string("老板"); // 返回const char *
}