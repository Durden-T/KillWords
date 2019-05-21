#ifndef USER_H
#define USER_H
//һ���˺�ֻ��ע��Ϊ�����߻������֮һ


#include"common.h"


class Database;


class User
{
public:
	User(string& _name, string& _key, int _count = 0, int _exp = 0, int _level = 1) :name(_name), key(_key), count(_count), exp(_exp), level(_level) {}

	virtual ~User() = default;

	//��ʼ����Database������
	static void connectWithDatabase(Database* _data);

	//ѡ�񴳹�/���� /��ѯ/�鿴����
	virtual void choice() = 0;

	//�ǳ�ʱ����������͵ǳ���Ϣ�����¼��
	void logout();

	void query() const;

	//�ṩ�˵����棬ʵ�ʹ���ί�и�chooseRankBy
	void rank() const;


protected:
	string name;
	string key;
	int count;
	int exp;
	int level;
	static Database* data;

	//ѡ������ʽ
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