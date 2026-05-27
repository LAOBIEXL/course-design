#include "Tools.h"
#include <iostream>
#include <limits>

using namespace std;

int Tools::readInt(const string& hint) {
    int value;

    while (true) {
        cout << hint;

        if (cin >> value) {
            // 成功读取后清空本行剩余内容，避免多余输入影响下一次读取
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }

        cout << "输入错误，请输入整数。" << endl;
        cin.clear(); // 重置 cin 的错误状态
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 清空当前输入行
    }
}

double Tools::readPositiveDouble(const std::string& hint) {
    double value;

    while (true) {
        cout << hint;

        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (value > 0) {
                return value;
            }

            cout << "输入错误，金额必须大于 0。" << endl;
        }
        else {
            cout << "输入错误，请输入数字金额。" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}


bool Tools::ckIdFormat(const string& id) {
    if (id.size() != 18) {
        return false;
    }

    for (int i = 0; i < 17; i++) {
        if (id[i] < '0' || id[i] > '9') {
            return false;
        }
    }

    char last = id[17];
    if (!((last >= '0' && last <= '9') || last == 'X' || last == 'x')) {
        return false;
    }

    return true;
}

bool Tools::ckPhoneFormat(const string& phone){
    if (phone.size() != 11) {
        return false;
    }

    for (int i = 0; i < 11; i++) {
        if (phone[i] < '0' || phone[i] > '9') {
            return false;
        }
    }

    return true;
}

bool Tools::ckDateFormat(const string& date)  {
    if (date.size() != 10) {
        return false;
    }

    if (date[4] != '-' || date[7] != '-') {
        return false;
    }

    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) {
            continue;
        }

        if (date[i] < '0' || date[i] > '9') {
            return false;
        }
    }

    int month = stoi(date.substr(5, 2));
    int day = stoi(date.substr(8, 2));

    if (month < 1 || month > 12) {
        return false;
    }

    if (day < 1 || day > 31) {
        return false;
    }

    return true;
}