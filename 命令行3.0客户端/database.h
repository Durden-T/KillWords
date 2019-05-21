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

	//�ж��û��Ƿ���ڣ����ڷ���true�����򷵻�false
	bool hasUser(const string& name);

	void _register(const string& name, const string& key, char type);

	//�����ѶȻ�ȡ���ʣ����ظõ���
	const string getWord(diffType type);

	//�õ����Ѵ��ڷ���false��������ӳɹ�������true
	bool addWord(const string& word);

	//���ظ��û���Ϣ
	const string query(const string& name);

	//����������������û���Ϣ
	const string rank(char type, char rankBy);

	//�����û�����
	void update(const string& name, int count, int exp, int level);

	void logout(const string& name);

protected:
	Database();

	~Database() = default;


private:
	//socket����
	io_service service;
	ip::udp::endpoint ep{ ip::address::from_string("127.0.0.1"), 6666 };
	//�������������������Ϣ
	string status;
	//���ܷ���������Ϣ�Ļ�����
	char buff[1024];
	//��������Ϊ�������send�����У���status���͸����������������������ص���Ϣ�ٴδ���status
	void send();
};

#endif