#ifndef SYSTEM_H
#define SYSTEM_H
#include"Account.h"
#include"List.h"
#include<string>

class System {
public:
	void run();
	System(); //银行系统整体构造函数，负责完成编号起点的初始化等；

private:
	int nextAcNumber;//维护下一个账号的编号；
	List<Account> accounts_m; //属于该系统的账户链表；
	Node<Account>* findByAcnumber(const std::string& key) const; //按照账户编号查找
	void displayAllAc()const; //展示所有账号的信息；

	void InitData();

	void mainMenu();

	void queryByAcnumber();//按照账号查询；

	void openAc();//开户
	std::string allocateAcNumber(); //分配账户编号；

	void depositMoney();//存款；

	void outMoney(); //取款；

	void moveMoney(); //转账；

	void closeAc();
};









#endif
