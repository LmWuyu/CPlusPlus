#include "workermanager.h"
WorkerManager::WorkerManager()
{
    // 数据初始化
    // 分三种情况
    //  1.文件不存在
    ifstream ifs;
    ifs.open(FILENAME, ios::in); // 读文件
    if (!ifs.is_open())
    {
        // 文件不存在
        //         cout << "文件不存在" << endl;
        this->m_EmpNum = 0;
        this->m_EmpArray = NULL;
        // 初始化文件是否为空
        this->m_FileIsEmpty = true;
        ifs.close();
        return;
    }
    // 2.文件存在,并且没有记录
    char ch;
    ifs >> ch;
    if (ifs.eof()) // 为真代表读取完了，文件为空
    {
        //        cout << "文件为空" << endl;
        this->m_EmpNum = 0;
        this->m_EmpArray = NULL;
        // 初始化文件是否为空
        this->m_FileIsEmpty = true;
        ifs.close();
        return;
    }
    //    cout << "文件存在，且有数据" << endl;
    // 3.文件存在，且有数据
    int num = this->get_EmpNum();
    //    cout << "职工人数" << num << endl; //获取人数
    this->m_EmpNum = num;

    // 初始化，大小为文件中的大小
    // 开辟空间
    this->m_EmpArray = new Worker *[this->m_EmpNum];
    // 创建数据
    this->init_Emp();

    // 测试代码
    //     for (int i = 0; i < this->m_EmpNum; i++) {
    //         cout << this->m_EmpArray[i]->m_Id << " "
    //              << this->m_EmpArray[i]->m_Name << " "
    //              << this->m_EmpArray[i]->m_DeptId << endl;
    //         cout << this->m_EmpArray[i]->getDeptName() << endl;

    //    }
}
WorkerManager::~WorkerManager()
{
    // 用于释放数据
    if (this->m_EmpArray != NULL)
    {
        for (int i = 0; i < this->m_EmpNum; i++)
        {
            if (this->m_EmpArray[i] != NULL)
            {
                delete this->m_EmpArray[i];
            }
        }
        delete[] this->m_EmpArray;
        this->m_EmpArray = NULL;
    }
}
void WorkerManager::Show_Menu()
{
    cout << "**********************************************" << endl;
    cout << "***********  欢迎使用职工管理系统  ***********" << endl;
    cout << "**************  0.退出管理程序  **************" << endl;
    cout << "**************  1.增加职工信息  **************" << endl;
    cout << "**************  2.显示职工信息  **************" << endl;
    cout << "**************  3.删除离职员工  **************" << endl;
    cout << "**************  4.修改职工信息  **************" << endl;
    cout << "**************  5.查找职工信息  **************" << endl;
    cout << "**************  6.按照编号排序  **************" << endl;
    cout << "**************  7.清空所有文档  **************" << endl;
    cout << "**********************************************" << endl;
}

void WorkerManager::exitSystem()
{
    cout << "欢迎下次使用" << endl;
    //    system("cat test.txt");
    exit(0); // 代表退出系统，返回代码0，代表正常退出
}

void WorkerManager::Add_Emp()
{
    cout << "请输入添加职工的数量" << endl;
    int addNum = 0;
    cin >> addNum;
    if (addNum > 0)
    {
        // 添加
        // 计算添加空间的大小
        int newSize = this->m_EmpNum + addNum; // 新空间大小 = 元人数+新增元素
        Worker **newSpace = new Worker *[newSize];
        // 将原来空间数据，拷贝到新空间下
        if (this->m_EmpArray != NULL)
        {
            for (int i = 0; i < this->m_EmpNum; i++)
            {
                newSpace[i] = this->m_EmpArray[i];
            }
        }
        // 添加新数据
        for (int i = 0; i < addNum; i++)
        {
            int id;      // 编号
            string name; // 姓名
            int dselect; // 部门选择
            cout << "请输入第" << i + 1 << "个新职工的编号" << endl;
            cin >> id;
            cout << "请输入第" << i + 1 << "个新职工的姓名" << endl;
            cin >> name;
            cout << "请选择新职工的岗位" << endl;
            cout << "1.普通职工" << endl;
            cout << "2.经理" << endl;
            cout << "3.老板" << endl;
            cin >> dselect;
            Worker *worker = NULL;
            switch (dselect)
            {
            case 1:
                worker = new Employee(id, name, dselect);
                break;
            case 2:
                worker = new Manager(id, name, dselect);
                break;
            case 3:
                worker = new Boss(id, name, dselect);
                break;
            default:
                break;
            }
            // 将创建的职工指针，保存到数组中
            newSpace[this->m_EmpNum + i] = worker;
        }
        // 释放原有的空间
        delete[] this->m_EmpArray;
        // 更改新空间的指向
        this->m_EmpArray = newSpace;
        // 更新新职工的人数
        this->m_EmpNum = newSize;
        // 提示添加成功
        cout << "成功添加" << addNum << "名职工" << endl;
        // 将数据置为false
        this->m_FileIsEmpty = false;

        // 按任意键继续，清理屏幕。
        system("cat test.txt");
        // system("clear");
    }
    else
    {
        cout << "输入有误" << endl;
        // system("cat test.txt");
        // system("clear");
    }
}

void WorkerManager::save()
{
    ofstream ofs;
    ofs.open(FILENAME, ios::out); // 这里进行out不会产生文件的覆盖，不知道为啥，按理说out是覆盖写，可以用ios::app，进行追加,文件过多app会数据重复
    // 将数据写入文件中
    for (int i = 0; i < this->m_EmpNum; i++)
    {
        ofs << this->m_EmpArray[i]->m_Id << " "
            << this->m_EmpArray[i]->m_Name << " "
            //            << this->m_EmpArray[i]->getDeptName() << endl;
            << this->m_EmpArray[i]->m_DeptId << endl;
    }
    ofs.close();
}
int WorkerManager::get_EmpNum()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in); // 读
    int id;
    string name;
    int did;
    int num = 0;
    while (ifs >> id && ifs >> name && ifs >> did)
    {
        num++;
    }
    ifs.close();
    return num; // 返回记录人数
}

void WorkerManager::init_Emp()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in);
    int id;
    string name;
    int did;
    int index = 0;
    while (ifs >> id && ifs >> name && ifs >> did)
    {
        Worker *worker = NULL;
        if (did == 1)
        {
            worker = new Employee(id, name, did); // 创建普通员工
        }
        else if (did == 2)
        {
            worker = new Manager(id, name, did); // 创建经理
        }
        else
        {
            worker = new Boss(id, name, did); // 创建老板
        }
        this->m_EmpArray[index] = worker;
        index++;
    }
    this->m_FileIsEmpty = false;

    ifs.close();
}

void WorkerManager::show_Emp()
{
    if (this->m_EmpNum == 0)
    {
        this->m_FileIsEmpty = true;
    }

    // 判断文件是否为空
    if (this->m_FileIsEmpty || this->m_EmpNum == 0)
    {
        // true 为空
        cout << "文件不存在，或者文件为空" << endl;
    }
    else
    {
        // 不为空
        for (int i = 0; i < this->m_EmpNum; i++)
        {
            this->m_EmpArray[i]->showInfo(); // 不同的对象调用同一个函数，结果一样。
        }
    }
    system("cat test.txt");
    // system("clear");
}
void WorkerManager::Del_Emp()
{
    // 删除数组中的数据：本质就是数据的前移，数组下标--
    if (this->m_FileIsEmpty)
    {
        cout << "文件不存在或者记录为空" << endl;
    }
    else
    {
        // 按照编号删除
        cout << "输入你要删除的编号" << endl;
        int id = 0;
        cin >> id;

        int index = this->IsExist(id);

        if (index != -1)
        {
            // 存在，并且要删除到数据
            // 找到删除的下标，遍历进行覆盖
            for (int i = index; i < this->m_EmpNum - 1; i++)
            {
                this->m_EmpArray[i] = this->m_EmpArray[i + 1];
            }
            this->m_EmpNum--; // 更新数组中记录的人员个数
            // 同步更新文件
            this->save();
            cout << "删除成功" << endl;
        }
        else
        {
            cout << "删除失败，没找到员工" << endl;
        }

        system("cat test.txt");
        // system("clear");
    }
}

int WorkerManager::IsExist(int id)
{
    int index = -1;
    for (int i = 0; i < this->m_EmpNum; i++)
    {
        if (this->m_EmpArray[i]->m_Id == id)
        {
            index = i; // 找到索引，i是所在的下标
            break;
        }
    }
    return index;
}

void WorkerManager::Mod_Emp()
{
    if (this->m_FileIsEmpty)
    {
        cout << "文件不存在或者记录为空" << endl;
    }
    else
    {
        cout << "请输入修改职工的编号" << endl;
        int id;
        cin >> id;
        int ret = this->IsExist(id);
        if (ret != -1)
        {
            // 找到了员工
            cout << "查到：" << id << "号职工,职工号 " << this->m_EmpArray[ret]->m_Id << " "
                 << "姓名" << this->m_EmpArray[ret]->m_Name << " "
                 << "部门" << this->m_EmpArray[ret]->m_DeptId << endl;

            delete this->m_EmpArray[ret];
            int newId = 0;
            string newName = "";
            int newDid = 0;

            cout << "请输入新的职工号" << endl;
            cin >> newId;
            cout << "输入新的姓名" << endl;
            cin >> newName;
            cout << "请输入新的岗位" << endl;
            cout << "1.普通员工" << endl;
            cout << "2.经理" << endl;
            cout << "3.老板" << endl;

            cin >> newDid;
            Worker *worker = NULL;
            switch (newDid)
            {
            case 1:
                worker = new Employee(newId, newName, newDid);
                break;
            case 2:
                worker = new Manager(newId, newName, newDid);
                break;
            case 3:
                worker = new Boss(newId, newName, newDid);
                break;
            default:
                break;
            }
            // 更新数据 到数组
            this->m_EmpArray[ret] = worker;
            cout << "修改数据成功" << this->m_EmpArray[ret]->m_DeptId << endl;
            // 保存到文件
            this->save();
        }
        else
        {
            cout << "没有该员工" << endl;
        }
    }
    system("cat test.txt");
    // system("clear");
}

void WorkerManager::Find_Emp()
{
    if (this->m_FileIsEmpty)
    {
        cout << "文件不存在或者文件为空" << endl;
    }
    else
    {
        cout << "请输入查找的方式" << endl;
        cout << "1.按职工的编号查找 " << endl;
        cout << "2.按职工的姓名查找 " << endl;
        int select = 0;
        cin >> select;
        if (select == 1)
        {
            int id;
            cout << "输入职工的编号" << endl;
            cin >> id;
            int ret = this->IsExist(id);
            if (ret != -1)
            {
                cout << "查找成功！该职工信息如下" << endl;
                this->m_EmpArray[ret]->showInfo();
            }
            else
            {
                cout << "查无此人" << endl;
            }
        }
        else if (select == 2)
        {
            // 按姓名查
            string name;
            cout << "请输入要查找的姓名" << endl;
            cin >> name;
            // 添加判断是否查找到的标志
            bool flag = false; // 默认为没有找到
            for (int i = 0; i < this->m_EmpNum; i++)
            {
                if (this->m_EmpArray[i]->m_Name == name)
                {
                    cout << "查找成功，职工编号为" << this->m_EmpArray[i]->m_Id << "号职工信息如下" << endl;
                    this->m_EmpArray[i]->showInfo();
                    flag = true;
                }
            }
            if (flag == false)
            {
                cout << "查找失败，查无此人" << endl;
            }
        }
        else
        {
            cout << "输入的选项有误" << endl;
        }
    }
    // 按任意键清频
    system("cat test.txt");
    // system("clear");
}

void WorkerManager::Sort_Emp()
{
    // 使用选择排序进行实现
    if (this->m_FileIsEmpty)
    {
        cout << "文件不存在，或记录为空" << endl;
        system("cat test.txt");
        // system("clear");
    }
    else
    {
        cout << "请选择排序方式" << endl;
        cout << "1.按照职工号进行升序" << endl;
        cout << "2.按照职工号进行降序" << endl;
        int select = 0;
        cin >> select;
        for (int i = 0; i < this->m_EmpNum; i++)
        {
            int minOrmax = i; // 声明最小值或者最大值的下标
            for (int j = i + 1; j < this->m_EmpNum; j++)
            {
                if (select == 1)
                {
                    // 升序
                    if (this->m_EmpArray[minOrmax]->m_Id > this->m_EmpArray[j]->m_Id)
                    {
                        // 我们认为的最小数不是最小值
                        minOrmax = j;
                    }
                }
                else
                {
                    // 降序
                    if (this->m_EmpArray[minOrmax]->m_Id < this->m_EmpArray[j]->m_Id)
                    {
                        // 我们认为的最小数不是最小值
                        minOrmax = j;
                    }
                }
            }
            // 判断一开始认定的最小值和最大值 是不是计算的最小值，最大值，如果不是 交换数据
            if (i != minOrmax)
            {
                Worker *temp = this->m_EmpArray[i];
                this->m_EmpArray[i] = this->m_EmpArray[minOrmax];
                this->m_EmpArray[minOrmax] = temp;
            }
        }
        cout << "排序成功！排序成功后的结果为：" << endl;
        this->save();     // 将数据保存文件
        this->show_Emp(); // 展示所有职工
    }
}
void WorkerManager::Clear_File()
{
    cout << "确认清空么？" << endl;
    cout << "1.确定" << endl;
    cout << "2.返回" << endl;
    int select;
    cin >> select;
    if (select == 1)
    {
        // 清空
        ofstream ofs(FILENAME, ios::trunc); // 删除文件后在创建
        ofs.close();
        if (this->m_EmpArray != NULL)
        {
            // 删除堆区每个对象
            for (int i = 0; i < this->m_EmpNum; i++)
            {
                delete this->m_EmpArray[i];
                this->m_EmpArray = NULL;
            }
            // 删除堆区数组指针
            delete[] this->m_EmpArray;
            this->m_EmpArray = NULL;
            this->m_EmpNum = 0;
            this->m_FileIsEmpty = true;
        }
        cout << "清空成功" << endl;
    }
    system("cat test.txt");
    // system("clear");
}