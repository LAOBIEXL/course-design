#define _CRT_SECURE_NO_WARNINGS
#include "User.h"
#include <iostream>
#include <sstream>

using namespace std;

User::User() {
    userid_m = "";
    username_m = "";
    password_m = "";
}

User::User(
    const std::string& userid,
    const std::string& username,
    const std::string& password
) : userid_m(userid),
    username_m(username),
    password_m(password)
{ }

const string& User::getIdNumber() const {
    return userid_m;
}

const string& User::getName() const {
    return username_m;
}

bool User::ckPassword(const string& password) const {
    return password_m == password;
}

string User::toline() const {
    ostringstream oss;

    oss << userid_m << "|"
        << username_m << "|"
        << password_m << "|";

    for (int i = 0; i < int(acnumbers_m.size()); i++) {
        if (i > 0) {
            oss << ",";
        }
        oss << acnumbers_m[i];
    }

    return oss.str();
}

void User::display() const {
    cout << "----------------------------------------" << endl;
    cout << "身份证号：" << userid_m << endl;
    cout << "姓名：" << username_m << endl;

    cout << "名下账号：";
    if (acnumbers_m.empty()) {
        cout << "无";
    }
    else {
        for (int i = 0; i < int(acnumbers_m.size()); i++) {
            if (i > 0) {
                cout << ", ";
            }
            cout << acnumbers_m[i];
        }
    }
    cout << endl;

    cout << "----------------------------------------" << endl;
}

void User::addAcNumber(const std::string& acnumber) {
    if (hasAcNumber(acnumber)) {
        return;
    }//防止重复添加同一账号

    acnumbers_m.push_back(acnumber);
}

bool User::hasAcNumber(const std::string& acnumber) const {
    for (int i = 0; i < int(acnumbers_m.size()); i++) {
        if (acnumbers_m[i] == acnumber) {
            return true;
        }
    }
    return false;
}

int User::getAcCnt() const {
    return int(acnumbers_m.size());
}

const std::string& User::getAcNumberByIdx(int idx) const {
    return acnumbers_m[idx];
}

void User::removeAcNumber(const std::string& acnumber) {
    for (int i = 0; i < int(acnumbers_m.size()); i++) {
        if (acnumbers_m[i] == acnumber) {
            acnumbers_m.erase(acnumbers_m.begin() + i);
            return;
        }
    }
}
