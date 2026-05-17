#include "System.h"
#include "Account.h"
#include"List.h"
#include <iostream>
#include<string>
using namespace std;

System::System() :nextAcNumber(100001) {};

void System::run() {
    InitData();
    mainMenu();

}

//主菜单操作
void System::mainMenu() {
    int choice = -1;

    while (choice != 0) {
        cout << "\n================ 银行账户管理系统 ================" << endl;
        cout << "1. 浏览全部账户" << endl;
        cout << "2. 按账号查询账户" << endl;
        cout << "3. 开户" << endl;
        cout << "4. 存款" << endl;
        cout << "5. 取款" << endl;
        cout << "0. 退出系统" << endl;
        cout << "请选择：";

        cin >> choice;

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
        case 0:
            cout << "系统已退出。" << endl;
            break;
        default:
            cout << "输入错误，请重新选择。" << endl;
            break;
        }
    }
}

void System::displayAllAc() const {
    cout << "一下是全部账号的信息：" << endl;
    if (accounts_m.empty()) cout << "本系统无任何账号" << endl;
    else {
        Node<Account>* p = accounts_m.getHead();
        while (p != nullptr) {
            p->data.display();
            p = p->next;
        }

    }
}

Node<Account>* System::findByAcnumber(const std::string& key) const {
    return accounts_m.find([key](const Account& a) {
        return key == a.getAcNumber();
        });
}

void System::InitData() {
    //Account a1(
    //    "100001",
    //    "王明",
    //    "330102200501010011",
    //    "浙江工业大学",
    //    "13800000001",
    //    "杭州市拱墅区",
    //    "2026-05-16",
    //    "",
    //    5000.0
    //);

    //accounts_m.push_back(a1);

    //Account a2(
    //    "100002",
    //    "李华",
    //    "330102200502020022",
    //    "某科技公司",
    //    "13800000002",
    //    "杭州市西湖区",
    //    "2026-05-17",
    //    "",
    //    1200.0
    //);

    //Account a3(
    //    "100003",
    //    "王芳",
    //    "330102200503030033",
    //    "某银行",
    //    "13800000003",
    //    "杭州市上城区",
    //    "2026-05-18",
    //    "",
    //    3000.0
    //);

    //accounts_m.push_back(a2);
    //accounts_m.push_back(a3);
}


void System::queryByAcnumber() {
    string key;
    cout << "请输入要查询的账号：";
    cin >> key;
    Node<Account>* result = findByAcnumber(key);
    if (result != nullptr) {
        cout << "查找成功" << endl;
        result->data.display();
    }
    else {
        cout << "查找失败，没有该账号。" << endl;
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

    cout << "请输入单位：";
    cin >> workplace;

    cout << "请输入电话号码：";
    cin >> phone;

    cout << "请输入地址：";
    cin >> address;

    cout << "请输入开户日期：";
    cin >> openday;
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
    cout << "开户成功！系统自动分配账号为：" << acnumber << endl;
}

string System::allocateAcNumber() {
    string nextAcnumberS = to_string(nextAcNumber);
    nextAcNumber++;
    return nextAcnumberS;
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
    else {
        cout << "请你输入要存入的款项金额：";
        double dep;
        cin >> dep;
        if (dep <= 0) {
            cout << "存款失败：金额必须大于 0。" << endl;
            return;
        }
        else {
            pf->data.inMoney(dep);
            cout << "存款成功，当前账户信息如下：" << endl;
            pf->data.display();
        }

    }

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
    else {
        cout << "请你输入要取出的款项金额：";
        double om;
        cin >> om;
        if (om <= 0) {
            cout << "取款失败：金额必须大于 0。" << endl;
            return;
        }
        else if(om > pf->data.getMoney()) {
            cout << "取款失败：余额不足。" << endl;
        }
        else {
            pf->data.outMoney(om);
            cout << "取款成功，当前账户信息如下：" << endl;
            pf->data.display();
        }
    }
}