#pragma once
#include <string>
class Deal {
public:
    Deal();

    Deal(
        const std::string& dealId,
        const std::string& type,
        const std::string& outAcnumber,
        const std::string& inAcnumber,
        const std::string& outUserId,
        const std::string& inUserId,
        double money,
        const std::string& time,
        const std::string& note
    );

    std::string toline() const;
    void display() const;

    const std::string& getOutAcnumber() const;//提供访问接口，为普通权限用户查询使用；
    const std::string& getInAcnumber() const;
    const std::string& getOutUserId() const;
    const std::string& getInUserId() const;

private:
    std::string dealId_m;      // 流水号
    std::string type_m;         // 开户/存款/取款/转账/销户
    std::string outAcnumber_m; // 转出账号或操作账号
    std::string inAcnumber_m;   // 转入账号，非转账时可为空
    std::string outUserId_m;    // 操作账号对应身份证号
    std::string inUserId_m;     // 转入账号对应身份证号，非转账时可为空
    double money_m;   // 金额
    std::string time_m;  // 操作时间
    std::string note_m;   // 备注

    
};