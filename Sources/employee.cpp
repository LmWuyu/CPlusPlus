#include <employee.h>

Employee::Employee(int id, string name, int did)
{
    m_Id = id;
    this->m_Name = name;
    m_DeptId = did;
}

void Employee::showInfo()
{
    cout << "职工编号 " << this->m_Id << "\t";
    cout << "职工姓名 " << this->m_Name << "\t";
    //    cout << "岗位名称 " << this->m_DeptId << "\t";
    cout << "岗位名称 " << this->getDeptName() << "\t";
    cout << "岗位职责:完成经理交给的任务" << endl;
}
// 获取岗位名称
string Employee::getDeptName()
{
    return string("员工"); // 返回const char *
}