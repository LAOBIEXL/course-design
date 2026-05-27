#define _CRT_SECURE_NO_WARNINGS
#include "AdminUser.h"
#include <iostream>
using namespace std;

AdminUser::AdminUser()
    : User("admin", "超级管理员", "123456") //user类构造函数；
{}

AdminUser::AdminUser(const std::string& password)
    : User("admin", "超级管理员", password)
{}

void AdminUser::display() const {
    cout << "----------------------------------------" << endl;
    cout << "管理员账号：admin" << endl;
    cout << "管理员姓名：超级管理员" << endl;
    cout << "----------------------------------------" << endl;
}

