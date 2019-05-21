#ifndef DATABASE_H
#define DATABASE_H


#include"user.h"
#include"common.h"


class Database
{
public:
	Database();

	~Database();

	bool hasUser(const string& name) const;

	User* getUser(const string& name);

	const string& getKey(const string& name) const;

	void addPlayer(User* t);

	void addWordMaker(User* t);

	void playerRank();

	void wordMakerRank();

	void update();

private:
	vector<User*> players, wordMakers;
	unordered_map<string, User*> userTable;
	void rankWithCountAndPrint(vector<User*>& src);
	void rankWithExpAndPrint(vector<User*>& src);
	void rankWithLevelAndPrint(vector<User*>& src);
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
