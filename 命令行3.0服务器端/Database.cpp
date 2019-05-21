#include "Database.h"



Database::Database()
{
	if (sql)
	{
		mysql_real_connect(sql, dbIp, dbUser, dbKey, dbName, 3306, nullptr, 0);
	}
	else
	{
		cout << "�������ݿ�ʧ�ܡ�" << endl;
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
	return (this->*(table[v[0]]))(v);//�ú�����ַ�
}


void Database::spilt(const string& s, vector<string>& v)
{
	//ĩβ�޷ָ��������һ���ո�
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
		//������� > 0
		if (res->row_count != 0)
		{
			auto row = mysql_fetch_row(res);

			//�ж������Ƿ���ȷ
			if (v[2] == row[4])
			{
				//��δ��¼
				if (!hasLogined.count(v[1]))
				{
					//�����¼��¼
					hasLogined.insert(v[1]);
					int bytes = sprintf_s(tmp, "%s %s %s %s", row[1], row[2], row[3], row[5]);
					//��½�ɹ������ص�¼��Ϣ
					ans = string(tmp, bytes);
				}
				else
				{
					//�����ѵ�¼�������ַ�����
					ans = ::hasLogined;
				}
			}
			else
			{
				//�������
				ans = wrongKey;
			}
		}
		//�û���������
		else
		{
			ans = EMPTY;
		}

		mysql_free_result(res);
	}
	else
	{
		cout << "���ݿ����" << endl;
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
		cout << "���ݿ����" << endl;
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
			//ans = ���صĵ���
			ans = row[0];
		}
		//��Ӧ�Ѷ��޵���
		else
		{
			ans = EMPTY;
		}
		mysql_free_result(res);
	}
	else
	{
		cout << "���ݿ����" << endl;
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
			//�����û���Ϣ
			ans = string(tmp, bytes);
		}
		//�û�������
		else
		{
			ans = EMPTY;
		}

		mysql_free_result(res);
	}
	else
	{
		cout << "���ݿ����" << endl;
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
		//Ŀǰ���û�
		else
		{
			ans = EMPTY;
		}

		mysql_free_result(res);
	}
	else
	{
		cout << "���ݿ����" << endl;
		ans = EMPTY;
	}

	return ans;
}


string Database::update(vector<string>& v)
{
	//�����û�����
	sprintf_s(tmp, "update user set `count`=%s,`exp`=%s,`level`=%s where `name`= '%s'", v[2], v[3], v[4], v[1]);
	mysql_real_query(sql, tmp, strlen(tmp));
	return EMPTY;
}

string Database::logout(vector<string>& v)
{
	//ɾ����Ӧ�û��ѵ�¼�ļ�¼
	hasLogined.erase(v[1]);
	return EMPTY;
}
