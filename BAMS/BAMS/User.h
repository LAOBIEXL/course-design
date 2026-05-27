#pragma once

#include <string>
#include <vector>

class User {
public:
	User();//默认构造函数
	User(
		const std::string& userid,
		const std::string& username,
		const std::string& password
	);

	const std::string& getIdNumber() const;
	const std::string& getName() const;

	bool ckPassword(const std::string& password) const;

	std::string toline() const;//转化为一行字符串，便于存入 users.txt

	void display() const;

	void addAcNumber(const std::string& acnumber);//添加该用户名下的账号

	bool hasAcNumber(const std::string& acnumber) const;//判断该用户是否拥有某个账号

	int getAcCnt() const;//获取该用户名下账号数量

	const std::string& getAcNumberByIdx(int idx) const;//根据下标返回账号

	void removeAcNumber(const std::string& acnumber);//账号重新分配，需要把deactive账号从数组中移除；
private:
	std::string userid_m;       // 用户身份标识，这里使用身份证号
	std::string username_m;     // 用户姓名
	std::string password_m;     // 登录密码
	std::vector<std::string> acnumbers_m;// 该用户名下的账号列表
};
