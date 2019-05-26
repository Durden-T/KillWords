#ifndef DATABASE_H
#define DATABASE_H


#include"user.h"
#include"common.h"


class Database
{
public:
	static Database& getInstance()//singleton
	{
		static Database Instance;
		return Instance;
	}

	//判断用户是否存在，存在返回true，否则返回false
	bool hasUser(const string& name) const;

	User* getUser(const string& name);

	const string& getKey(const string& name) const;

	void addPlayer(User* t);

	void addWordMaker(User* t);

	//返回排序过的所有用户信息
	void playerRank();

	void wordMakerRank();

	//更新数据
	void update();

protected://singleton
	Database();

	~Database();

private:
	//从文件中读取用户信息,存入players,wordMakers
	vector<User*> players, wordMakers;
	//快速定位用户，获取用户指针
	unordered_map<string, User*> userTable;
	//排行实现部分，根据不同的要求排行并打印
	void rankWithCountAndPrint(vector<User*>& src);
	void rankWithExpAndPrint(vector<User*>& src);
	void rankWithLevelAndPrint(vector<User*>& src);
	//打印vector中用户信息
	void printUsers(vector<User*>& src);
};


inline bool Database::hasUser(const string& name) const
{
	return userTable.count(name);
}

inline User* Database::getUser(const string& name)
{
	return userTable[name];
}

inline const string& Database::getKey(const string& name) const
{
	return userTable.at(name)->getKey();
}


#endif
