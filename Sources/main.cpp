#include "boss.h"
#include "employee.h"
#include "worker.h"
#include "workermanager.h"
#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;
#include "manager.h"
int main()
{
    // 测试代码

    //    Worker* worker = NULL;
    //    worker = new Employee(1, "张三", 1);
    //    worker->showInfo();
    //    Worker* worke = new Manager(1, "张三", 1);
    //    worke->showInfo();
    //    worker = new Boos(1, "张三", 1);
    //    worker->showInfo();

    WorkerManager work;
    int select = 0;
    while (true)
    {
        // 显示
        work.Show_Menu();
        cout << "请选择您的操作：" << endl;
        cin >> select;
        switch (select)
        {
        case 0: // 退出系统
            work.exitSystem();

        case 1: // 添加职工
            work.Add_Emp();
            work.save();
            break;
        case 2: // 显示职工
            work.show_Emp();
            break;
        case 3: // 删除职工
            work.Del_Emp();
            break;
        case 4: // 修改职工
            work.Mod_Emp();
            break;
        case 5: // 查找职工
            work.Find_Emp();
            break;
        case 6: // 排序职工
            work.Sort_Emp();
            break;
        case 7: // 清空文件
            work.Clear_File();
            break;
        default:
            system("clear");
            break;
        }
    }
    return 0;
}