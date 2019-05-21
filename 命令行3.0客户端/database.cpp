#include"database.h"
#include"menu.h"
#include"user.h"
#include"common.h"


Database::Database()
{
	Menu::connectWithDatabase(this);
	User::connectWithDatabase(this);
}


const string Database::login(const string& name, const string& key)
{
	status = "��¼ " + name + ' ' + key;
	send();
	return status;
}

bool Database::hasUser(const string& name)
{
	status = "���� " + name;
	send();
	return status == EXIST;
}

void Database::_register(const string& name, const string& key, char type)
{
	status = "ע�� " + name + ' ' + key + ' ' + type;
	send();
}

const string Database::getWord(diffType type)
{
	string t;
	if (type == easy)
		t = "easy";
	else if (type == medium)
		t = "medium";
	else
		t = "difficult";
	status = "ȡ�� " + t;
	send();
	return status;
}

bool Database::addWord(const string& word)
{
	status = "���� " + word;
	send();
	return status == EMPTY;
}

const string Database::query(const string& name)
{
	status = "��ѯ " + name;
	send();
	return status;

}

const string Database::rank(char type, char rankBy)
{
	if (rankBy == rankByCount)
	{
		status = "���� a ";
	}
	else if (rankBy == rankByExp)
	{
		status = "���� b ";
	}
	else
	{
		status = "���� c ";
	}
	status += type;
	send();
	return status;
}

void Database::update(const string& name, int count, int exp, int level)
{
	status = "���� " + name + ' ' + to_string(count) + ' ' + to_string(exp) + ' ' + to_string(level);
	send();
}

void Database::logout(const string& name)
{
	status = "�ǳ� " + name;
	send();
}


void Database::send()
{
	try
	{
		ip::udp::socket sock(service, ip::udp::endpoint(ip::udp::v4(), 0));
		sock.send_to(buffer(status), ep);
		int bytes = sock.receive(buffer(buff));
		status = string(buff, bytes);
		sock.close();
	}
	catch (boost::system::system_error e)
	{
		cout << e.code() << "\t���ӷ�����ʧ�ܡ�" << endl;
		exit(-1);
	}

}