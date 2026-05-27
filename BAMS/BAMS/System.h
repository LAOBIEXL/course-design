#pragma once
#include"Account.h"
#include"List.h"
#include<string>
#include "User.h"
#include "AdminUser.h"
#include "Deal.h"
#include <vector>

class System {
public:
	void run();
	System(); //银行系统整体构造函数，负责完成编号起点的初始化等；

private:
	int nextAcNumber;//维护下一个账号的编号；
	int nextDealNum_m;    // 下一个流水编号


	List<Account> accounts_m; //属于该系统的账户链表；

	List<User> users_m; // 用户链表

	List<Deal> deals_m; //流水链表类；

	Node<Account>* findByAcnumber(const std::string& key) const; //按照账户编号查找

	Node<User>* findUserById(const std::string& id) const; //复用链表find的接口；

	void displayAllAc()const; //展示所有账号的信息；

	void mainMenu();

	void login();//登录界面；
	void adminMenu();//管理员界面；
	void userMenu();//用户界面；

	void queryByAcnumber();//按照账号查询；

	void queryByName();//按照姓名查找
	bool findByAcName(const std::string& key) const;

	void openAc();//开户
	std::string allocateAcNumber(); //分配账户编号；

	void depositMoney();//存款；

	void outMoney(); //取款；

	void moveMoney(); //转账；

	void closeAc();//销户

	void saveAc()const; //将转化好的字符串存入txt;

	void loadAc();//载入账户；

	void saveUsers() const;//将用户账号信息写入txt;

	void loadUsers();//载入账号密码信息；

	void loadDeals(); //载入流水；

	void saveDeals() const; // 保存流水；


	void InfoChange(); //修改账户信息；


	void mohuSearch(); //模糊查找；
	void preciSearch(); //字段精确查询；

	void sortMenu();  //排序界面菜单；

	void showUser() const;//展示普通用户信息；

	int role_m; //权限类型 0未登录，1，管理员 2，普通用户；
	std::string user_id_m; //登录时保存身份证号；
	 
	bool ckId(const std::string& id) const; //核验用于身份验证的身份证号；

	bool CkCanWatch(const std::string& acnumber) const;
	//先区分管理员，管理员赦免后，普通用户因当能够访问自己名下的账户；
	//由于某个人有好几个号，通过权限判断来实现对名下账户的访问权；
	
	void showMine() const; //展示我名下的所有账号；

	AdminUser admin_m;

	std::string allocateDealNum();//获取当前流水号；

	std::string getTime() const;//获取时间；

	void addDeal(
		const std::string& type,
		const std::string& outAcnumber,
		const std::string& inAcnumber,
		double money,
		const std::string& remark
	);//增加流水;

	void displayAllDeals() const;//展示全部流水；

	bool CkMyDeal(const Deal& deal) const;
	void displayMyDeals() const;//展示普通用户流水；

	void backup(const std::string& filename, const std::string& backupname) const; //备份函数；

	//回收

	std::vector<std::string> reAcNumbers_m; //已经被回收的账号池；

	void resumeReAcNumbers(); //重新启动时，恢复reAcnumbers_m;
};
