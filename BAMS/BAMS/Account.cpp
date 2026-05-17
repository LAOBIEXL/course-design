#include"Account.h"
#include<iostream>
#include<iomanip>
using namespace std;

Account::Account() {//安全初始化
	acnumber_m = "";
	acname_m = "";
	id_m = "";
	workplace_m = "";
	phone_m = "";
	address_m = "";
	openday_m = "";
	closeday_m = "";
	money_m = 0;
	status_m = "Active";
}

Account::Account(
	const std::string& acnumber,
	const std::string& acname,
	const std::string& id,
	const std::string& workplace,
	const std::string& phone,
	const std::string& address,
	const std::string& openday,
	const std::string& closeday,
	const double money
):
	acname_m(acname),
	acnumber_m(acnumber),
	id_m(id),
	workplace_m(workplace),
	phone_m(phone),
	address_m(address),
	openday_m(openday),
	closeday_m(closeday),
	money_m(money),
	status_m("Active")
{}

const string& Account::getAcNumber() const {
	return acnumber_m;
}

const string& Account::getUserName() const {
	return acname_m;
}

const string& Account::getUserId()  const {
	return id_m;
}

double Account::getMoney() const {
	return money_m;
}

const string& Account::getStatus() const {
	return status_m;
}

bool Account::is_active() const{
	return status_m == "Active" ? 1 : 0;
}

void Account::inMoney(const double& m) {
	if (m > 0) {
		money_m += m;
	}
}

bool Account::outMoney(const double& m) {
	if (money_m >= 0 && m > 0) {
		if (money_m >= m)
		{
			money_m -= m;
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

void Account::closeAc(const string& closeday) {
	closeday_m = closeday;
	status_m = "Deactive";
}

void Account::display()const {
	cout << "----------------------------------------" << endl;
	cout << "账号：" << acnumber_m << endl;
	cout << "姓名：" << acname_m << endl;
	cout << "身份证号：" << id_m << endl;
	cout << "单位：" << workplace_m << endl;
	cout << "电话：" << phone_m << endl;
	cout << "地址：" << address_m << endl;
	cout << "开户日期：" << openday_m << endl;
	cout << "销户日期：" << closeday_m << endl;
	cout << "余额：" << fixed << setprecision(2) << money_m << endl;
	cout << "状态：" << status_m << endl;
	cout << "----------------------------------------" << endl;
}
