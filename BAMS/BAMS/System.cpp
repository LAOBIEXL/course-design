#include "System.h"
#include "Account.h"
#include"List.h"
#include <iostream>
#include<string>
#include<fstream>
#include<sstream>
using namespace std;

System::System() :nextAcNumber(100001) {};

void System::run() {
    loadAc();
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
        cout << "6. 转账" << endl;
        cout << "7. 销户" << endl;
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
        case 6:
            moveMoney();
            break;
        case 7:
            closeAc();
            break;
        case 0:
            saveAc();
            cout << "账户信息已保存。" << endl;
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
    else if (!pf->data.is_active()) {
        cout << "存款失败：该账户已销户，不能继续存款。" << endl;
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
    else if (!pf->data.is_active()) {
        cout << "取款失败：该账户已销户，不能继续取款。" << endl;
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
        else if (!pf->data.outMoney(om)) {
            cout << "取款失败：余额不足。" << endl;
        }
        else {
            cout << "取款成功，当前账户信息如下：" << endl;
            pf->data.display();
        }
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
    cout << "请输入转账金额：";
    double mon;
    cin >> mon;

    if (mon <= 0) {
        cout << "转账失败：金额必须大于 0。" << endl;
        return;
    }
    else if (!pfo->data.outMoney(mon)) {
        cout << "转账失败：转出账户余额不足。" << endl;
        return;
    }
    else {
        pfi->data.inMoney(mon);
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
        pf->data.closeAc(closeday);
        cout << "销户成功，账户信息如下：" << endl;
        pf->data.display();

    }


}

void System::saveAc()const {
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

}
