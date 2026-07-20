#pragma once
#include<string>

class Account {
public:
	Account();//无参初始化
	Account(
		const std::string& acnumber,
		const std::string& acname,
		const std::string& id,
		const std::string& workplace,
		const std::string& phone,
		const std::string& address,
		const std::string& openday,
		const std::string& closeday,
		const double money,
		const std::string& status = "Active"
	);

	const std::string& getAcNumber() const;

	const std::string& getUserName() const;
	const std::string& getUserId() const;
	const std::string& getPhone() const;
	const std::string& getOpenDay() const;
	const std::string& getCloseDay() const;
	double getMoney() const;
	const std::string& getStatus() const;
	bool is_active()const;

	void inMoney(const double& m);//存款
	bool outMoney(const double& m);//取款
	void closeAc(const std::string& closeday);

	void display()const;

	std::string toline()const; //将账户信息转化为用"|"分隔的字符串；

	void changeInfo( //账户信息修改；
		const std::string& name,
		const std::string& phone,
		const std::string& workp,
		const std::string& address
	);

	bool matchKey(const std::string& key) const; //关键词匹配，为模糊查找功能模块；

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
