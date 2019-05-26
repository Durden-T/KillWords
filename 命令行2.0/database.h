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

	//�ж��û��Ƿ���ڣ����ڷ���true�����򷵻�false
	bool hasUser(const string& name) const;

	User* getUser(const string& name);

	const string& getKey(const string& name) const;

	void addPlayer(User* t);

	void addWordMaker(User* t);

	//����������������û���Ϣ
	void playerRank();

	void wordMakerRank();

	//��������
	void update();

protected://singleton
	Database();

	~Database();

private:
	//���ļ��ж�ȡ�û���Ϣ,����players,wordMakers
	vector<User*> players, wordMakers;
	//���ٶ�λ�û�����ȡ�û�ָ��
	unordered_map<string, User*> userTable;
	//����ʵ�ֲ��֣����ݲ�ͬ��Ҫ�����в���ӡ
	void rankWithCountAndPrint(vector<User*>& src);
	void rankWithExpAndPrint(vector<User*>& src);
	void rankWithLevelAndPrint(vector<User*>& src);
	//��ӡvector���û���Ϣ
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
