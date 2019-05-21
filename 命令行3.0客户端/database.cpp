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
	status = "登录 " + name + ' ' + key;
	send();
	return status;
}

bool Database::hasUser(const string& name)
{
	status = "存在 " + name;
	send();
	return status == EXIST;
}

void Database::_register(const string& name, const string& key, char type)
{
	status = "注册 " + name + ' ' + key + ' ' + type;
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
	status = "取词 " + t;
	send();
	return status;
}

bool Database::addWord(const string& word)
{
	status = "出题 " + word;
	send();
	return status == EMPTY;
}

const string Database::query(const string& name)
{
	status = "查询 " + name;
	send();
	return status;

}

const string Database::rank(char type, char rankBy)
{
	if (rankBy == rankByCount)
	{
		status = "排行 a ";
	}
	else if (rankBy == rankByExp)
	{
		status = "排行 b ";
	}
	else
	{
		status = "排行 c ";
	}
	status += type;
	send();
	return status;
}

void Database::update(const string& name, int count, int exp, int level)
{
	status = "更新 " + name + ' ' + to_string(count) + ' ' + to_string(exp) + ' ' + to_string(level);
	send();
}

void Database::logout(const string& name)
{
	status = "登出 " + name;
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
		cout << e.code() << "\t连接服务器失败。" << endl;
		exit(-1);
	}

}