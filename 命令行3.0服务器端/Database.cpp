#include "Database.h"



Database::Database()
{
	if (sql)
	{
		mysql_real_connect(sql, dbIp, dbUser, dbKey, dbName, 3306, nullptr, 0);
	}
	else
	{
		cout << "连接数据库失败。" << endl;
		exit(-1);
	}
}

Database::~Database()
{
	mysql_close(sql);
}


string Database::command(const string request)
{
	vector<string> v;
	spilt(request, v);
	return (this->*(table[v[0]]))(v);//用函数表分发
}


void Database::spilt(const string& s, vector<string>& v)
{
	//末尾无分隔符，添加一个空格
	string source = s + ' ';
	string t;
	for (char c : source)
	{
		if (c == ' ')
		{
			v.emplace_back(t);
			t.clear();
		}
		else
		{
			t += c;
		}
	}
}

string Database::login(vector<string>& v)
{
	string ans;

	sprintf_s(tmp, "select * from user where name = '%s'", v[1]);
	if (!mysql_real_query(sql, tmp, strlen(tmp)))
	{
		auto res = mysql_store_result(sql);
		//若结果数 > 0
		if (res->row_count != 0)
		{
			auto row = mysql_fetch_row(res);

			//判断密码是否正确
			if (v[2] == row[4])
			{
				//若未登录
				if (!hasLogined.count(v[1]))
				{
					//插入登录记录
					hasLogined.insert(v[1]);
					int bytes = sprintf_s(tmp, "%s %s %s %s", row[1], row[2], row[3], row[5]);
					//登陆成功，返回登录信息
					ans = string(tmp, bytes);
				}
				else
				{
					//返回已登录（常量字符串）
					ans = ::hasLogined;
				}
			}
			else
			{
				//密码错误
				ans = wrongKey;
			}
		}
		//用户名不存在
		else
		{
			ans = EMPTY;
		}

		mysql_free_result(res);
	}
	else
	{
		cout << "数据库错误。" << endl;
		ans = EMPTY;
	}
	return ans;
}

string Database::exist(vector<string>& v)
{
	string ans;

	sprintf_s(tmp, "select * from user where name = '%s'", v[1]);
	if (!mysql_real_query(sql, tmp, strlen(tmp)))
	{
		auto res = mysql_store_result(sql);
		ans = res->row_count != 0 ? EXIST : EMPTY;
		mysql_free_result(res);
	}

	else
	{
		cout << "数据库错误。" << endl;
		ans = EMPTY;
	}

	return ans;
}

string Database::_register(vector<string>& v)
{
	sprintf_s(tmp, "insert into user values('%s',0,0,0,'%s','%s')", v[1], v[2], v[3]);
	mysql_real_query(sql, tmp, strlen(tmp));
	return EMPTY;
}

string Database::getWord(vector<string>& v)
{
	string ans;

	if (v[1][0] == 'e')
	{
		sprintf_s(tmp, "select * from `dict` where size<5 order by rand() limit 1");
	}
	else if (v[1][0] == 'm')
	{
		sprintf_s(tmp, "select * from `dict` where size>=5 and size<10 order by rand() limit 1");
	}
	else
	{
		sprintf_s(tmp, "select * from `dict` where size>=10 order by rand() limit 1");
	}


	if (!mysql_real_query(sql, tmp, strlen(tmp)))
	{
		auto res = mysql_store_result(sql);
		if (res->row_count != 0)
		{
			auto row = mysql_fetch_row(res);
			//ans = 返回的单词
			ans = row[0];
		}
		//对应难度无单词
		else
		{
			ans = EMPTY;
		}
		mysql_free_result(res);
	}
	else
	{
		cout << "数据库错误。" << endl;
		ans = EMPTY;
	}

	return ans;
}

string Database::addWord(vector<string>& v)
{
	string ans;
	sprintf_s(tmp, "insert into dict (word,size) values('%s',%d)", v[1], v[1].size());
	ans = !mysql_real_query(sql, tmp, strlen(tmp)) ? EMPTY : EXIST;
	return ans;
}

string Database::query(vector<string>& v)
{
	string ans;
	sprintf_s(tmp, "select * from user where name = '%s'", v[1]);

	if (!mysql_real_query(sql, tmp, strlen(tmp)))
	{
		auto res = mysql_store_result(sql);
		if (res->row_count != 0)
		{
			auto row = mysql_fetch_row(res);
			int bytes = sprintf_s(tmp, "%s %s %s %s", row[1], row[2], row[3], row[5]);
			//返回用户信息
			ans = string(tmp, bytes);
		}
		//用户不存在
		else
		{
			ans = EMPTY;
		}

		mysql_free_result(res);
	}
	else
	{
		cout << "数据库错误。" << endl;
		ans = EMPTY;
	}

	return ans;
}

string Database::rank(vector<string>& v)
{
	string ans;

	if (v[1] == "a")
	{

		sprintf_s(tmp, "select * from user where type = '%s' order by count desc", v[2]);
	}
	else if (v[1] == "b")
	{
		sprintf_s(tmp, "select * from user where type = '%s' order by exp desc", v[2]);
	}
	else
	{
		sprintf_s(tmp, "select * from user where type = '%s' order by level desc", v[2]);
	}


	if (!mysql_real_query(sql, tmp, strlen(tmp)))
	{
		auto res = mysql_store_result(sql);
		if (res->row_count != 0)
		{
			MYSQL_ROW row;
			while (row = mysql_fetch_row(res))
			{
				int bytes = sprintf_s(tmp, "%s %s %s %s ", row[0], row[1], row[2], row[3]);
				ans += string(tmp, bytes);
			}
		}
		//目前无用户
		else
		{
			ans = EMPTY;
		}

		mysql_free_result(res);
	}
	else
	{
		cout << "数据库错误。" << endl;
		ans = EMPTY;
	}

	return ans;
}


string Database::update(vector<string>& v)
{
	//更新用户数据
	sprintf_s(tmp, "update user set `count`=%s,`exp`=%s,`level`=%s where `name`= '%s'", v[2], v[3], v[4], v[1]);
	mysql_real_query(sql, tmp, strlen(tmp));
	return EMPTY;
}

string Database::logout(vector<string>& v)
{
	//删除对应用户已登录的记录
	hasLogined.erase(v[1]);
	return EMPTY;
}
