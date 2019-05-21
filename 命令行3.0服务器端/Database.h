#ifndef DATABASE_H
#define DATABASE_H


#include"common.h"


class Database
{
	//成员函数指针
	using fun=string(Database::*) (vector<string>&);

public:
	Database();

	~Database();

	//将命令分发给对应的处理函数
	string command(const string request);

private:
	//连接Mysql所需
	MYSQL* sql = mysql_init(nullptr);
	char dbUser[32] = "root";
	char dbKey[32] = "123456";
	char dbIp[32] = "localhost";
	char dbName[32] = "test";
	char tmp[1024];

	//加登录锁
	unordered_set<string> hasLogined;

	//成员函数表
	unordered_map<string, fun> table = { { "登录", &Database::login }, { "存在", &Database::exist }, { "注册", &Database::_register }, { "取词", &Database::getWord }, { "出题", &Database::addWord }, { "查询", &Database::query }, { "排行", &Database::rank }, { "更新", &Database::update }, { "登出", &Database::logout } };

	//将命令按分隔符空格分开，写入v
	void spilt(const string& s, vector<string>& v);

	string login(vector<string>& v);

	//判断用户是否存在
	string exist(vector<string>& v);

	string _register(vector<string>& v);

	string getWord(vector<string>& v);

	string addWord(vector<string>& v);

	string query(vector<string>& v);

	string rank(vector<string>& v);

	//更新用户数据
	string update(vector<string>& v);

	//登出，解登录锁
	string logout(vector<string>& v);
};


#endif