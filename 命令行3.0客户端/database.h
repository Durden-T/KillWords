#ifndef DATABASE_H
#define DATABASE_H


#include"user.h"
#include"common.h"


class Database
{
public:
	static Database& Instance()//Singleton method
	{
		static Database Instance;
		return Instance;
	}

	const string login(const string& name, const string& key);

	//判断用户是否存在，存在返回true，否则返回false
	bool hasUser(const string& name);

	void _register(const string& name, const string& key, char type);

	//根据难度获取单词，返回该单词
	const string getWord(diffType type);

	//该单词已存在返回false，否则添加成功，返回true
	bool addWord(const string& word);

	//返回该用户信息
	const string query(const string& name);

	//返回排序过的所有用户信息
	const string rank(char type, char rankBy);

	//更新用户数据
	void update(const string& name, int count, int exp, int level);

	void logout(const string& name);

protected:
	Database();

	~Database() = default;


private:
	//socket所需
	io_service service;
	ip::udp::endpoint ep{ ip::address::from_string("127.0.0.1"), 6666 };
	//保存与服务器交互的信息
	string status;
	//接受服务器的信息的缓存区
	char buff[1024];
	//将发送行为抽出放在send函数中，将status发送给服务器，并将服务器返回的信息再次存入status
	void send();
};

#endif