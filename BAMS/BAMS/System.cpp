#include "System.h"
#include "Account.h"
#include"List.h"
#include <iostream>
#include<string>
#include<fstream>
#include<iomanip>
#include<sstream>
#include<ctime>
#include"Tools.h"

using namespace std;

System::System() :nextAcNumber(100001),nextDealNum_m(1), role_m(-1), user_id_m(""), admin_m("123456") {};

void System::run() {
    loadUsers();
    loadAc();
    loadDeals();
    while (role_m != 0) {
        login();

        if (role_m == 1) {
            adminMenu();
        }
        else if (role_m == 2) {
            userMenu();
        }
        else if (role_m == 0) {
            cout << "系统退出。" << endl;
        }
    }
}

//登录菜单：
void System::login() {
    int choice;

    cout << "\n================ 登录系统 ================" << endl;
    cout << "1. 管理员登录" << endl;
    cout << "2. 普通用户登录" << endl;
    cout << "0. 退出系统" << endl;
    choice = Tools::readInt("请选择：");

    if (choice == 1) {
        string password;

        cout << "请输入管理员密码：";
        cin >> password;

        if (admin_m.ckPassword(password)) {  //adminuser使用从user类继承来的密码检查函数；
            role_m = 1;
            cout << "管理员登录成功。" << endl;
        }
        else {
            cout << "管理员密码错误，系统退出。" << endl;
            role_m = -1;
        }
    }
    else if (choice == 2) {
        string id;
        string password;

        cout << "请输入身份证号：";
        cin >> id;

        cout << "请输入密码：";
        cin >> password;

        Node<User>* userNode = findUserById(id);

        if (userNode == nullptr || !userNode->data.ckPassword(password)) {
            cout << "登录失败：用户名或密码错误。" << endl;
            role_m = -1;
            return;
        }

        user_id_m = id;
        role_m = 2;

        cout << "用户登录成功。" << endl;
    }
    else {
        role_m = choice;
    }
}
//管理员菜单：
void System::adminMenu() {
    int choice = -1;

    while (choice != 0) {
        cout << "\n================ 管理员菜单 ================" << endl;
        cout << "1. 浏览全部账户" << endl;
        cout << "2. 按账号查询账户" << endl;
        cout << "3. 开户" << endl;
        cout << "4. 存款" << endl;
        cout << "5. 取款" << endl;
        cout << "6. 转账" << endl;
        cout << "7. 销户" << endl;
        cout << "8. 按姓名查询账户" << endl;
        cout << "9. 修改账户信息" << endl;
        cout << "10. 模糊查询账户" << endl;
        cout << "11. 排序账户" << endl;
        cout << "12. 查看全部流水" << endl;
        cout << "13. 字段精确查询" << endl;
        cout << "0. 退出系统" << endl;
        choice = Tools::readInt("请选择：");

        switch (choice) {
        case 1:
            displayAllAc();
            break;

        case 2:
            queryByAcnumber();
            break;

        case 3:
            openAc();
            break;

        case 4:
            depositMoney();
            break;

        case 5:
            outMoney();
            break;

        case 6:
            moveMoney();
            break;

        case 7:
            closeAc();
            break;

        case 8:
            queryByName();
            break;

        case 9:
            InfoChange();
            break;

        case 10:
            mohuSearch();
            break;

        case 11:
            sortMenu();
            break;

        case 12:
            displayAllDeals();
            break;

        case 13:
            preciSearch();
            break;

        case 0:
            saveUsers();
            saveAc();
            saveDeals();
            cout << "用户信息已保存。" << endl;
            cout << "账户信息已保存。" << endl;
            cout << "流水信息已保存。" << endl;
            cout << "系统已退出。" << endl;
            break;

        default:
            cout << "输入错误，请重新选择。" << endl;
            break;
        }
    }
}
//一般用户菜单：
void System::userMenu() {
    int choice = -1;

    while (choice != 0) {
        cout << "\n================ 普通用户菜单 ================" << endl;
        cout << "1. 查看我的全部账户" << endl;
        cout << "2. 按账号查询我的账户" << endl;
        cout << "3. 存款" << endl;
        cout << "4. 取款" << endl;
        cout << "5. 转账" << endl;
        cout << "6. 查看我的流水" << endl;
        cout << "0. 退出系统" << endl;
        choice = Tools::readInt("请选择：");

        switch (choice) {
        case 1:
            showMine();
            break;

        case 2:
            queryByAcnumber();
            break;

        case 3:
            depositMoney();
            break;

        case 4:
            outMoney();
            break;

        case 5:
            moveMoney();
            break;

        case 6:
            displayMyDeals();
            break;

        case 0:
            saveUsers();
            saveAc();
            saveDeals();
            cout << "用户信息已保存。" << endl;
            cout << "账户信息已保存。" << endl;
            cout << "流水信息已保存。" << endl;
            cout << "系统已退出。" << endl;
            break;

        default:
            cout << "输入错误，请重新选择。" << endl;
            break;
        }
    }
}
void System::displayAllAc() const {
    cout << "以下是全部账户的信息：" << endl;
    if (accounts_m.empty()) {
        cout << "本系统无任何账号" << endl;
        return;
    }

    Node<Account>* p = accounts_m.getHead();
    while (p != nullptr) {
        p->data.display();
        p = p->next;
    }
}
Node<Account>* System::findByAcnumber(const std::string& key) const {
    Node<Account>* f = nullptr;//用来暂存候选（可能未激活）
    Node<Account>* p = accounts_m.getHead();

    while (p != nullptr) {
        if (p->data.getAcNumber() == key) {
            if (f == nullptr) {
                f = p;
            }

            if (p->data.is_active()) {
                return p;
            }
        }
        p = p->next;
    }

    return f;
}


Node<User>* System::findUserById(const std::string& id) const {
    return users_m.find([id](const User& u) {
        return u.getIdNumber() == id;
        });
}

void System::queryByAcnumber() {
    string key;
    cout << "请输入要查询的账号：";
    cin >> key;
    Node<Account>* result = findByAcnumber(key);
    if (result == nullptr) {
        cout << "查找失败，没有该账号。" << endl;
        return;
    }
    else if (!CkCanWatch(key)) {//权限限制；
            cout << "查找失败：无权访问该账户。" << endl;
            return;
    }
    else {
        cout << "查找成功" << endl;
        result->data.display();
    }
}


void System::openAc() {
    string name;
    string id;
    string workplace;
    string phone;
    string address;
    string openday;

    cout << "请输入姓名：";
    cin >> name;

    cout << "请输入身份证号：";
    cin >> id;
    while (!Tools::ckIdFormat(id)) {
        cout << "身份证号格式不合法，请重新输入：";
        cin >> id;
    }

    cout << "请输入单位：";
    cin >> workplace;

    cout << "请输入电话号码：";
    cin >> phone;
    while (!Tools::ckPhoneFormat(phone)) {
        cout << "电话号码格式不合法，请重新输入：";
        cin >> phone;
    }

    cout << "请输入地址：";
    cin >> address;

    cout << "请输入开户日期：";
    cin >> openday;
    while (!Tools::ckDateFormat(openday)) {
        cout << "开户日期格式不合法，请按YYYY-MM-DD重新输入：";
        cin >> openday;
    }
    string acnumber = allocateAcNumber();
    Account newAccount(
        acnumber,
        name,
        id,
        workplace,
        phone,
        address,
        openday,
        "",
        0.0
    );
    accounts_m.push_back(newAccount);

    Node<User>* userNode = findUserById(id);//在开户同时

    if (userNode == nullptr) {
        string password;

        cout << "该身份证号是新用户，请让用户设置登录密码：";
        cin >> password;

        User newUser(id, name, password);

        newUser.addAcNumber(acnumber); //推入该用户的名下账户；

        users_m.push_back(newUser);

        cout << "新用户创建成功。" << endl;
        
    }
    else {
        userNode->data.addAcNumber(acnumber);//推入名下账户；
    }
    

    cout << "开户成功！系统自动分配账号为：" << acnumber << endl;
    addDeal("开户", acnumber, "", 0.0, "开户成功");
}



void System::depositMoney() {
    string acnumber;
    cout << "请您输入要存款的银行账号：";
    cin >> acnumber;

    Node<Account>* pf = findByAcnumber(acnumber);

    if (pf == nullptr) {
        cout << "存款失败：账号不存在。" << endl;
        return;
    }
    else if (!CkCanWatch(acnumber)) {
        cout << "存款失败：无权操作该账户。" << endl;
        return;
    }
    else if (!pf->data.is_active()) {
        cout << "存款失败：该账户已销户，不能继续存款。" << endl;
        return;
    }

    double dep = Tools::readPositiveDouble("请你输入要存入的款项金额：");

    pf->data.inMoney(dep);
    addDeal("存款", acnumber, "", dep, "存款成功");

    cout << "存款成功，当前账户信息如下：" << endl;
    pf->data.display();
}

void System::outMoney() {
    string acnumber;
    cout << "请您输入要取款的银行账号：";
    cin >> acnumber;

    Node<Account>* pf = findByAcnumber(acnumber);

    if (pf == nullptr) {
        cout << "取款失败：账号不存在。" << endl;
        return;
    }
    else if (!CkCanWatch(acnumber)) {
        cout << "取款失败：无权操作该账户。" << endl;
        return;
    }
    else if (!pf->data.is_active()) {
        cout << "取款失败：该账户已销户，不能继续取款。" << endl;
        return;
    }

    double om = Tools::readPositiveDouble("请你输入要取出的款项金额：");

    if (!pf->data.outMoney(om)) {
        cout << "取款失败：余额不足。" << endl;
    }
    else {
        addDeal("取款", acnumber, "", om, "取款成功");
        cout << "取款成功，当前账户信息如下：" << endl;
        pf->data.display();
    }
}

void System::moveMoney() {
    string oacnumber;
    string iacnumber;
    cout << "请输入转出账号：";
    cin >> oacnumber;
    cout << "请输入转入账号：";
    cin >> iacnumber;
    Node<Account>* pfo = findByAcnumber(oacnumber);
    Node<Account>* pfi = findByAcnumber(iacnumber);
    if (pfo == nullptr) {
        cout << "转账失败：转出账号不存在。" << endl;
        return;
    }
    if (pfi == nullptr) {
        cout << "转账失败：转入账号不存在。" << endl;
        return;
    }

    if (!CkCanWatch(oacnumber)) {
        cout << "转账失败：无权从该账户转出。" << endl;
        return;
    }


    if (pfi == pfo) {
        cout << "转账失败：转出账号和转入账号不能相同。" << endl;
        return;
    }
    if (!pfo->data.is_active()) {
        cout << "转账失败：转出账户已销户，不能转账。" << endl;
        return;
    }
    if (!pfi->data.is_active()) {
        cout << "转账失败：转入账户已销户，不能接收转账。" << endl;
        return;
    }
    double mon = Tools::readPositiveDouble("请输入转账金额：");

    if (!pfo->data.outMoney(mon)) {
        cout << "转账失败：转出账户余额不足。" << endl;
        return;
    }
    else {
        pfi->data.inMoney(mon);
        addDeal("转账", oacnumber, iacnumber, mon, "转账成功");
        cout << "转账成功！" << endl;
        cout << "转出账户当前信息：" << endl;
        pfo->data.display();
        cout << "转入账户当前信息：" << endl;
        pfi->data.display();
    }



}


void System::closeAc() {
    string acnumber;
    cout << "请输入要销户的银行账号：";
    cin >> acnumber;
    Node<Account>* pf = findByAcnumber(acnumber);

    if (pf == nullptr) {
        cout << "销户失败：账号不存在。" << endl;
        return;
    }
    if (!pf->data.is_active()) {
        cout << "销户失败：该账户已经销户。" << endl;
        return;
    }
    //余额不为零
    else if (pf->data.getMoney() > 1e-5) {
        cout << "销户失败：账户余额不为 0，请先取款或转账清零。" << endl;
        return;
    }
    else {
        string closeday;

        cout << "请输入销户日期：";
        cin >> closeday;
        while (!Tools::ckDateFormat(closeday)) {
            cout << "销户日期格式不合法，请按YYYY-MM-DD重新输入：";
            cin >> closeday;
        }
        pf->data.closeAc(closeday);

        Node<User>* userNode = findUserById(pf->data.getUserId());
        if (userNode != nullptr) {
            userNode->data.removeAcNumber(acnumber);
        }//在销户的同时，将这个账号从user的所属账号列表erase;
        reAcNumbers_m.push_back(acnumber);//同时加入号池；

        addDeal("销户", acnumber, "", 0.0, "销户成功");
        cout << "销户成功，账户信息如下：" << endl;
        pf->data.display();

    }


}

void System::saveAc()const {
    backup("accounts.txt", "accounts_back.txt");
    ofstream fout("accounts.txt");

    //判断文件是否正常打开：
    if (!fout.is_open()) {
        cout << "文件保存失败：无法打开 accounts.txt" << endl;
        return;
    }
    Node<Account>* ph = accounts_m.getHead();
    while (ph != nullptr) {
        string tmp = ph->data.toline();
        fout << tmp << endl;
        ph = ph->next;
    }
    fout.close();
}

void System::loadAc() {
    ifstream fin("accounts.txt");

    //判断打开；
    if (!fin.is_open()) {
        return;
    }
    string line;
    while (getline(fin, line)) {
        if (line.empty()) {
            continue;
        }//避免空行导致后序拆分出错；
        string a[10];
        istringstream iss(line);
        for (int i = 0; i < 10; i++) {
            getline(iss, a[i], '|');
        }//拆分；
        Account newAc{
            a[0],
            a[1],
            a[2],
            a[3],
            a[4],
            a[5],
            a[6],
            a[7],
            stod(a[8]),
            a[9]
        };
        accounts_m.push_back(newAc);

        int acnum_id = stoi(a[0]);
        if (acnum_id >= nextAcNumber) {
            nextAcNumber = acnum_id+1;
        }

    }

    fin.close();
    resumeReAcNumbers();
}

void System::saveUsers() const {
    backup("users.txt", "users_back.txt");
    ofstream fout("users.txt");

    if (!fout.is_open()) {
        cout << "用户信息保存失败：无法打开 users.txt" << endl;
        return;
    }

    Node<User>* p = users_m.getHead();

    while (p != nullptr) {
        fout << p->data.toline() << endl;
        p = p->next;
    }

    fout.close();
}

void System::loadUsers() {
    ifstream fin("users.txt");
    if (!fin.is_open()) {
        return;
    }
    string line;
    while (getline(fin, line)) {
        if (line.empty()) {
            continue;
        }//避免空行；
        istringstream iss(line);

        string f[4];

        for (int i = 0; i < 4; i++) {
            getline(iss, f[i], '|');
        }

        User user(
            f[0], // 身份证号
            f[1], // 姓名
            f[2]  // 密码
        );

        istringstream issnum(f[3]);
        string Acnum_tmp;
        while (getline(issnum, Acnum_tmp, ',')) {
            if (Acnum_tmp.empty()) {
                continue; //防空；
            }
            user.addAcNumber(Acnum_tmp);
        }

        users_m.push_back(user);
    }

    fin.close();
}




void System::queryByName() {
    cout << "请输入要查询的账户姓名：";
    string key;
    cin >> key;
    bool flag = findByAcName(key);
    if (flag) {
        cout << "查询失败，无此账户姓名" << endl;
    }
}



bool System::findByAcName(const string& key) const {
    //不能使用find接口；由于要查找所有同名的装好，所以直接遍历查找；
    Node<Account>* pf = accounts_m.getHead();
    bool flag = 1;
    while (pf != nullptr) {
        if (pf->data.getUserName() == key) {
            if (flag) {
                cout << "查询成功，查询结果如下：" << endl;
                flag = 0;
            }
           
            pf->data.display();
          }
        pf = pf->next;
    }
    return flag;
}

void System::InfoChange() {
    string acnum;
    cout << "请输入要修改的账户账号：" << endl;
    cin >> acnum;
    Node<Account>* pf = findByAcnumber(acnum);
    if (pf == nullptr) {
        cout << "修改失败，该账号不存在。";
        return;
    }
    else if (!pf->data.is_active()) {
        cout << "修改失败，该账号并不是激活状态" << endl;
        return;
    }
    else {
        string name;
        string workplace;
        string phone;
        string address;

        cout << "请输入新的姓名：";
        cin >> name;

        cout << "请输入新的单位：";
        cin >> workplace;

        cout << "请输入新的电话号码：";
        cin >> phone;
        while (!Tools::ckPhoneFormat(phone)) {
            cout << "电话号码格式不合法，请重新输入：";
            cin >> phone;
        }

        cout << "请输入新的地址：";
        cin >> address;

        pf->data.changeInfo(name, phone, workplace, address);
        cout << "修改成功，账号信息现在如下：" << endl;
        pf->data.display();
    }
}

void System::mohuSearch() {
    cout << "请输入搜索关键字 ：" << endl;
    string key;
    cin >> key;
    bool flag = true;
    Node<Account>* pf = accounts_m.getHead();
    while (pf != nullptr) {
        if (pf->data.matchKey(key)) {
            if(flag){
                cout << "查询成功,符合条件的账号如下：" << endl;
                flag = 0;
            }
            pf->data.display();
        }
        pf = pf->next;
    }
    if (flag) {
        cout << "抱歉，无法查询到与该关键词相关的账户" << endl;
    }
}

void System::preciSearch() {
    cout << "请选择精确查询方式：" << endl;
    cout << "1. 按身份证号查询" << endl;
    cout << "2. 按电话号码查询" << endl;
    cout << "3. 按开户日期查询" << endl;

    int choice = Tools::readInt("请选择：");

    string key;
    cout << "请输入查询内容：";
    cin >> key;

    if (choice == 1) {
        while (!Tools::ckIdFormat(key)) {
            cout << "身份证号格式不合法，请重新输入：";
            cin >> key;
        }
    }
    else if (choice == 2) {
        while (!Tools::ckPhoneFormat(key)) {
            cout << "电话号码格式不合法，请重新输入：";
            cin >> key;
        }
    }
    else if (choice == 3) {
        while (!Tools::ckDateFormat(key)) {
            cout << "开户日期格式不合法，请按YYYY-MM-DD重新输入：";
            cin >> key;
        }
    }
    else {
        cout << "选择不合法" << endl;
        return;
    }

    bool found = false;
    Node<Account>* p = accounts_m.getHead();

    while (p != nullptr) {
        bool ok = false;

        if (choice == 1 && p->data.getUserId() == key) {
            ok = true;
        }
        else if (choice == 2 && p->data.getPhone() == key) {
            ok = true;
        }
        else if (choice == 3 && p->data.getOpenDay() == key) {
            ok = true;
        }

        if (ok) {
            if (!found) {
                cout << "查询成功，结果如下：" << endl;
                found = true;
            }
            p->data.display();
        }

        p = p->next;
    }

    if (!found) {
        cout << "查询失败，没有符合条件的账户。" << endl;
    }
}

void System::sortMenu() {
    int choice;

    cout << "请选择排序方式：" << endl;
    cout << "1. 按账号升序排序" << endl;
    cout << "2. 按余额升序排序" << endl;
    cout << "3. 按开户日期升序排序" << endl;
    cout << "4. 按销户日期升序排序" << endl;
    choice = Tools::readInt("请选择：");

    if (choice == 1) {
        auto upsortByAcNum = [](const Account& a, const Account& b) {
            return a.getAcNumber() < b.getAcNumber();
            };

        accounts_m.sort(upsortByAcNum);

        cout << "排序成功，当前账号顺序如下：" << endl;
        Node<Account>* p = accounts_m.getHead();
        while (p != nullptr) {
            cout << "  " << p->data.getAcNumber() << endl;
            p = p->next;
        }
    }
    else if (choice == 2) {
        auto upsortByAcMoney = [](const Account& a, const Account& b) {
            return a.getMoney() < b.getMoney();
            };

        accounts_m.sort(upsortByAcMoney);

        cout << "排序成功，当前账号与余额顺序如下：" << endl;
        Node<Account>* p = accounts_m.getHead();
        while (p != nullptr) {
            cout << "  " << p->data.getAcNumber()
                << "  余额：" << p->data.getMoney() << endl;
            p = p->next;
        }
    }
    else if (choice == 3) {
        auto upsortByOpenDay = [](const Account& a, const Account& b) {
            return a.getOpenDay() < b.getOpenDay();
            };

        accounts_m.sort(upsortByOpenDay);

        cout << "排序成功，当前账号与开户日期顺序如下：" << endl;
        Node<Account>* p = accounts_m.getHead();
        while (p != nullptr) {
            cout << "  " << p->data.getAcNumber()
                << "  开户日期：" << p->data.getOpenDay() << endl;
            p = p->next;
        }
    }
    else if (choice == 4) {
        auto upsortByCloseDay = [](const Account& a, const Account& b) {
            string dayA = a.getCloseDay();
            string dayB = b.getCloseDay();

            if (dayA.empty()) {
                dayA = "9999-99-99"; // 未销户账户没有销户日期，临时设为较大日期，使其排在后面
            }

            if (dayB.empty()) {
                dayB = "9999-99-99"; // 未销户账户没有销户日期，临时设为较大日期，使其排在后面
            }

            return dayA < dayB;
            };

        accounts_m.sort(upsortByCloseDay);

        cout << "排序成功，当前账号与销户日期顺序如下：" << endl;
        Node<Account>* p = accounts_m.getHead();
        while (p != nullptr) {
            cout << "  " << p->data.getAcNumber()
                << "  销户日期：" << p->data.getCloseDay() << endl;
            p = p->next;
        }
    }
    else {
        cout << "选择不合法" << endl;
    }
}
bool System::ckId(const string& id) const {
    Node<Account>* pf =  accounts_m.find([id](const Account& a) {
        return (id == a.getUserId());
        });//复用lambda函数判断输入的身份证号合理性，返回查询的指针；
    return pf != nullptr;
}

void System::showUser() const {
    bool found = false;

    Node<Account>* p = accounts_m.getHead();

    while (p != nullptr) {
        if (p->data.getUserId() == user_id_m) {
            p->data.display();
            found = true;
        }

        p = p->next;
    }

    if (!found) {
        cout << "当前用户名下没有账户。" << endl;
    }
}

bool System::CkCanWatch(const std::string& acnumber) const {
    if (role_m == 1) {
        return true;
    }

    if (role_m == 2) {
        Node<User>* upf = findUserById(user_id_m);//找到当前普通用户的用户类；

        if (upf == nullptr) {
            return false;
        }//防止用户文件损坏或登录状态异常时出现空指针访问；

        return upf->data.hasAcNumber(acnumber);//判断该账号是否属于当前用户；
    }

    return false;
}

void System::showMine() const {
    cout << "当前用户名下账户如下：" << endl;
    Node<User>* upf = findUserById(user_id_m);

    if (upf == nullptr) {
        cout << "当前用户不存在。" << endl;
        return;
    }

    int cnt = upf->data.getAcCnt();

    if (cnt == 0) {
        cout << "当前用户名下没有账户。" << endl;
        return;
    }

    for (int i = 0; i < cnt; i++) {
        string acnumber = upf->data.getAcNumberByIdx(i);

        Node<Account>* pf = findByAcnumber(acnumber);

        if (pf != nullptr) {
            pf->data.display();
        }
    }
}

string System::allocateAcNumber() {
    if (!reAcNumbers_m.empty()) {//如果号池中有号
        string acnumber = reAcNumbers_m[0];
        reAcNumbers_m.erase(reAcNumbers_m.begin());
        return acnumber;
    }

    string nextAcnumberS = to_string(nextAcNumber);
    nextAcNumber++;
    return nextAcnumberS;
}


string System::allocateDealNum() {
    ostringstream oss;
    oss << "D" << setw(6) << setfill('0') << nextDealNum_m;
    nextDealNum_m++;
    return oss.str();
}


std::string System::getTime() const {
    time_t now = time(nullptr);//获取时间戳

    tm localTime;
    localtime_s(&localTime, &now);

    char a[30];
    strftime(a, sizeof(a), "%Y-%m-%d %H:%M:%S", &localTime);

    return string(a);
}
void System::addDeal(
    const std::string& type,
    const std::string& outAcnumber,
    const std::string& inAcnumber,
    double money,
    const std::string& note
) {
    string outUserId = "";
    string inUserId = "";

    Node<Account>* outNode = findByAcnumber(outAcnumber);

    if (outNode != nullptr) {
        outUserId = outNode->data.getUserId();
    }

    if (!inAcnumber.empty()) {
        Node<Account>* inNode = findByAcnumber(inAcnumber);

        if (inNode != nullptr) {
            inUserId = inNode->data.getUserId();
        }
    }

    Deal deal(
        allocateDealNum(),
        type,
        outAcnumber,
        inAcnumber,
        outUserId,
        inUserId,
        money,
        getTime(),
        note
    );

    deals_m.push_back(deal);
}

void System::displayAllDeals() const {
    cout << "全部流水记录如下：" << endl;

    if (deals_m.empty()) {
        cout << "当前没有流水记录。" << endl;
        return;
    }

    Node<Deal>* p = deals_m.getHead();

    while (p != nullptr) {
        p->data.display();
        p = p->next;
    }
}
void System::saveDeals() const {
    backup("deals.txt", "deals_back.txt");
    ofstream fout("deals.txt");

    if (!fout.is_open()) {
        cout << "流水信息保存失败：无法打开 deals.txt" << endl;
        return;
    }
    Node<Deal>* p = deals_m.getHead();

    while (p != nullptr) {
        fout << p->data.toline() << endl;
        p = p->next;
    }

    fout.close();
}

void System::loadDeals() {
    ifstream fin("deals.txt");

    if (!fin.is_open()) {
        return;
    }

    string line;

    while (getline(fin, line)) {
        if (line.empty()) {
            continue;
        }

        istringstream iss(line);
        vector<string> f;
        string tmp;

        while (getline(iss, tmp, '|')) {
            f.push_back(tmp);
        }

        if (f.size() != 9) {
            continue;
        }

        Deal deal(
            f[0],
            f[1],
            f[2],
            f[3],
            f[4],
            f[5],
            stod(f[6]),
            f[7],
            f[8]
        );

        deals_m.push_back(deal);

        //载入的过程要更新 nextDealNum_m，保证新流水号不会和旧流水号重复；
        if (f[0].size() > 1 && f[0][0] == 'D') {
            int num = stoi(f[0].substr(1));

            if (num >= nextDealNum_m) {
                nextDealNum_m = num + 1;
            }
        }
    }

    fin.close();
}

bool System::CkMyDeal(const Deal& deal) const {
    if (role_m == 1) {
        return true;
    }

    if (role_m != 2) {
        return false;
    }

    return deal.getOutUserId() == user_id_m || deal.getInUserId() == user_id_m;
}

void System::displayMyDeals() const {
    cout << "当前用户相关流水如下：" << endl;

    bool flag = false;

    Node<Deal>* p = deals_m.getHead();

    while (p != nullptr) {
        if (CkMyDeal(p->data)) {
            p->data.display();
            flag = true;
        }

        p = p->next;
    }

    if (!flag) {
        cout << "当前用户暂无相关流水。" << endl;
    }
}

void System::backup(const string& filename, const string& backupname) const {
    ifstream fin(filename);
    if (!fin.is_open()) {
        return;
    }

    ofstream fout(backupname);
    if (!fout.is_open()) {
        return;
    }

    string line;

    while (getline(fin, line)) {
        fout << line << endl;
    }

    fin.close();
    fout.close();
}

void System::resumeReAcNumbers() {
    reAcNumbers_m.clear();

    Node<Account>* p = accounts_m.getHead();
    while (p != nullptr) {
        string acnumber = p->data.getAcNumber();
        bool flag1 = false; //判断同账号编号是否存在已经激活的函数（无则进入号池）；
        bool flag2 = false;//是否已经存在在号池中； 

        Node<Account>* q = accounts_m.getHead();

        while (q != nullptr) {
            if (q->data.getAcNumber() == acnumber && q->data.is_active()) {
                flag1 = true;
                break;
            }

            q = q->next;
        }

        for (int i = 0; i < int(reAcNumbers_m.size()); i++) {
            if (reAcNumbers_m[i] == acnumber) {
                flag2 = true;
                break;
            }
        }

        if (!p->data.is_active() && !flag1 && !flag2) {
            reAcNumbers_m.push_back(acnumber);
        }

        p = p->next;
    }
}