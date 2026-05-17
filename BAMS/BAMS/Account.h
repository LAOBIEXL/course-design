#ifndef ACCOUNT_H
#define ACCOUNT_H
#include<string>

class Account {
public:
	Account();//安全默认初始化
	Account(
		const std::string& acnumber,
		const std::string& acname,
		const std::string& id,
		const std::string& workplace,
		const std::string& phone,
		const std::string& address,
		const std::string& openday,
		const std::string& closeday,
		const double money
	);

	const std::string& getAcNumber() const;

	const std::string& getUserName() const;
	const std::string& getUserId() const;
	double getMoney() const;
	const std::string& getStatus() const;
	bool is_active()const;

	void inMoney(const double& m);//存款
	bool outMoney(const double& m);//取款
	void closeAc(const std::string& closeday);

	void display()const;



private:
	std::string acnumber_m; // 账号
	std::string acname_m;// 姓名
	std::string id_m; // 身份证号
	std::string workplace_m; // 单位
	std::string phone_m; // 电话号码
	std::string address_m;// 地址
	std::string openday_m; // 开户日期
	std::string closeday_m;// 销户日期
	double money_m; // 余额
	std::string status_m;      // 账户状态


};

#endif