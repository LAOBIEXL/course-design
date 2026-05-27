#include "Deal.h"
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

Deal::Deal() {
    dealId_m = "";
    type_m = "";
    outAcnumber_m = "";
    inAcnumber_m = "";
    outUserId_m = "";
    inUserId_m = "";
    money_m = 0.0;
    time_m = "";
    note_m = "";
}

Deal::Deal(
    const std::string& dealId,
    const std::string& type,
    const std::string& outAcnumber,
    const std::string& inAcnumber,
    const std::string& outUserId,
    const std::string& inUserId,
    double money,
    const std::string& time,
    const std::string& note
)
    : dealId_m(dealId),
    type_m(type),
    outAcnumber_m(outAcnumber),
    inAcnumber_m(inAcnumber),
    outUserId_m(outUserId),
    inUserId_m(inUserId),
    money_m(money),
    time_m(time),
    note_m(note)
{}

string Deal::toline() const {
    ostringstream oss;

    oss << dealId_m << "|"
        << type_m << "|"
        << outAcnumber_m << "|"
        << inAcnumber_m << "|"
        << outUserId_m << "|"
        << inUserId_m << "|"
        << fixed << setprecision(2) << money_m << "|"
        << time_m << "|"
        << note_m;

    return oss.str();
}

void Deal::display() const {
    cout << "----------------------------------------" << endl;
    cout << "流水号：" << dealId_m << endl;
    cout << "类型：" << type_m << endl;
    cout << "操作账号：" << outAcnumber_m << endl;
    cout << "操作人身份证号：" << outUserId_m << endl;

    if (!inAcnumber_m.empty()) {
        cout << "对方账号：" << inAcnumber_m << endl;
    }

    if (!inUserId_m.empty()) {
        cout << "对方身份证号：" << inUserId_m << endl;
    }

    cout << "金额：" << fixed << setprecision(2) << money_m << endl;
    cout << "时间：" << time_m << endl;
    cout << "备注：" << note_m << endl;
    cout << "----------------------------------------" << endl;
}

const std::string& Deal::getOutAcnumber() const {
    return outAcnumber_m;
}

const std::string& Deal::getInAcnumber() const {
    return inAcnumber_m;
}

const std::string& Deal::getOutUserId() const {
    return outUserId_m;
}

const std::string& Deal::getInUserId() const {
    return inUserId_m;
}
