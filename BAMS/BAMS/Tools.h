#pragma once

#include<string>
class Tools {
public:
    static int readInt(const std::string& hint);//整数读取
    static double readPositiveDouble(const std::string& hint);//正小数读取；
    static bool ckIdFormat(const std::string& id) ; //检查身份证号格式；
    static bool ckPhoneFormat(const std::string& phone); //检查电话号码格式；
    static bool ckDateFormat(const std::string& date) ; //检查日期格式；

private:

};
