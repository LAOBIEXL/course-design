#pragma once
#include "User.h"
#include <string>

class AdminUser :public User {
public:
	AdminUser();
	AdminUser(const std::string& password); //接受管理员密码；
	void display() const;

private:

};