#ifndef USER_H
#define USER_H
//一个账号只能注册为闯关者或出题者之一


#include"common.h"


class Database;
class Dictionary;


class User
{
	friend bool cmpWithCount(User* a, User* b);
	friend bool cmpWithExp(User* a, User* b);
	friend bool cmpWithLevel(User* a, User* b);

public:
	User(string& _name, string& _key, int _count = 0, int _exp = 0, int _level = 1) :name(_name), key(_key), count(_count), exp(_exp), level(_level) {}

	virtual ~User() {}

	static void connectWithDatabase(Database* _data);

	const string& getName() const;

	const string& getKey() const;

	virtual void printInfo() const = 0;

	void addToData(ofstream& file) const;

	virtual void choice() = 0;

	void query() const;

	void queryRank() const;


protected:
	string name;
	string key;
	int count;
	int exp;
	int level;
	static Dictionary dict;
	static Database* data;
};


class Player : public User
{
public:
	using User::User;

	void printInfo() const override;

	void choice() override;

	void play();
};

class WordMaker : public User
{
public:
	using User::User;

	void printInfo() const override;

	void choice() override;

	void makeWord();
};


inline void User::connectWithDatabase(Database* _data)
{
	data = _data;
}

inline const string& User::getName() const
{
	return name;
}

inline const string& User::getKey() const
{
	return key;
}

inline void User::addToData(ofstream& file) const
{
	file << name << ' ' << key << ' ' << count << ' ' << exp << ' ' << level << '\n';
}


inline void Player::printInfo() const
{
	cout << "用户名:" << name << "\t闯关者\t闯关数:" << count << "\t经验值:" << exp << "\t等级:" << level << '\n';
}


inline void WordMaker::printInfo() const
{
	cout << "用户名:" << name << "\t出题者\t闯关数:" << count << "\t经验值:" << exp << "\t等级:" << level << '\n';
}


#endif