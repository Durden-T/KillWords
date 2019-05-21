#ifndef USER_H
#define USER_H
//一个账号只能注册为闯关者或出题者之一


#include"common.h"


class Database;


class User
{
public:
	User(string& _name, string& _key, int _count = 0, int _exp = 0, int _level = 1) :name(_name), key(_key), count(_count), exp(_exp), level(_level) {}

	virtual ~User() = default;

	//初始化与Database的连接
	static void connectWithDatabase(Database* _data);

	//选择闯关/出题 /查询/查看排行
	virtual void choice() = 0;

	//登出时向服务器发送登出信息，解登录锁
	void logout();

	void query() const;

	//提供菜单界面，实际功能委托给chooseRankBy
	void rank() const;


protected:
	string name;
	string key;
	int count;
	int exp;
	int level;
	static Database* data;

	//选择排序方式
	void chooseRankBy(char type) const;

};


class Player : public User
{
public:
	using User::User;

	void choice() override;

	void play();
};

class WordMaker : public User
{
public:
	using User::User;

	void choice() override;

	void addWord();
};


inline void User::connectWithDatabase(Database* _data)
{
	data = _data;
}


#endif