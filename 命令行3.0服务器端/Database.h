#ifndef DATABASE_H
#define DATABASE_H


#include"common.h"


class Database
{
	//��Ա����ָ��
	using fun=string(Database::*) (vector<string>&);

public:
	Database();

	~Database();

	//������ַ�����Ӧ�Ĵ�����
	string command(const string request);

private:
	//����Mysql����
	MYSQL* sql = mysql_init(nullptr);
	char dbUser[32] = "root";
	char dbKey[32] = "123456";
	char dbIp[32] = "localhost";
	char dbName[32] = "test";
	char tmp[1024];

	//�ӵ�¼��
	unordered_set<string> hasLogined;

	//��Ա������
	unordered_map<string, fun> table = { { "��¼", &Database::login }, { "����", &Database::exist }, { "ע��", &Database::_register }, { "ȡ��", &Database::getWord }, { "����", &Database::addWord }, { "��ѯ", &Database::query }, { "����", &Database::rank }, { "����", &Database::update }, { "�ǳ�", &Database::logout } };

	//������ָ����ո�ֿ���д��v
	void spilt(const string& s, vector<string>& v);

	string login(vector<string>& v);

	//�ж��û��Ƿ����
	string exist(vector<string>& v);

	string _register(vector<string>& v);

	string getWord(vector<string>& v);

	string addWord(vector<string>& v);

	string query(vector<string>& v);

	string rank(vector<string>& v);

	//�����û�����
	string update(vector<string>& v);

	//�ǳ������¼��
	string logout(vector<string>& v);
};


#endif