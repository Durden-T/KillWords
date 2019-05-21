#include"user.h"
#include"database.h"
#include"common.h"


Database* User::data = nullptr;



void User::logout()
{
	data->logout(name);
}

void User::query() const
{
	cout << "********************************************" << endl;
	cout << "     请输入要查询的用户名,输入#quit退出。" << endl;
	cout << "********************************************" << endl;

	string name;
	while (cin >> name && name != EXIT)
	{
		string t(data->query(name));
		if (t == EMPTY)
		{
			cout << "用户不存在。" << endl;
			cout << "********************************************" << endl;
			cout << "     请输入要查询的用户名,输入#quit退出。" << endl;
			cout << "********************************************" << endl;
			continue;
		}

		//输出该用户信息
		istringstream s(t);
		char type;
		int count, exp, level;
		s >> count >> exp >> level >> type;
		cout << "用户名:" << name << "\t" << (type == PLAYER ? "闯关数:" : "出题数:") << count << "\t经验值:" << exp << "\t等级:" << level << endl;

		cout << "********************************************" << endl;
		cout << "     请输入要查询的用户名,输入#quit退出。" << endl;
		cout << "********************************************" << endl;
	}
}

void User::rank() const
{
	cout << "********************************************" << endl;
	cout << "        a.闯关者排名 b.出题者排名 q.退出" << endl;
	cout << "********************************************" << endl;

	char c;
	while (cin >> c)
	{
		switch (c)
		{
		case 'a':
			chooseRankBy(PLAYER);
			break;
		case 'b':
			chooseRankBy(WORDMAKER);
			break;
		case 'q':
			return;
			break;
		default:
			cout << "指令错误,请重新输入。" << endl;
			break;
		}

		cout << "********************************************" << endl;
		cout << "        a.闯关者排名 b.出题者排名 q.退出" << endl;
		cout << "********************************************" << endl;
	}
}

void User::chooseRankBy(char type) const
{
	cout << "********************************************" << endl;
	cout << "a.根据" << (type == PLAYER ? "闯关" : "出题") << "数 b.根据经验值 c.根据等级 q.退出" << endl;
	cout << "********************************************" << endl;

	char c;
	while (cin >> c)
	{
		if (c >= 'a' && c <= 'c')
		{
			string t(data->rank(type, c));
			if (t != EMPTY)
			{
				istringstream is(t);
				string name;
				int count, exp, level;
				while (is >> name >> count >> exp >> level)
				{
					cout << "用户名:" << name << "\t" << (type == PLAYER ? "闯关数:" : "出题数:") << count << "\t经验值:" << exp << "\t等级:" << level << endl;
				}
			}
			else
			{
				cout << "当前无" << (type == PLAYER ? "闯关者。" : "出题者。") << endl;
			}

		}
		//用户要求退出
		else if (c == 'q')
		{
			break;
		}
		else
		{
			cout << "输入错误。" << endl;
		}

		cout << "********************************************" << endl;
		cout << "a.根据" << (type == PLAYER ? "闯关" : "出题") << "数 b.根据经验值 c.根据等级 q.退出" << endl;
		cout << "********************************************" << endl;
	}
}

void Player::choice()
{
	cout << "********************************************" << endl;
	cout << "      a.闯关 b.查询 c.查看排行榜 q.退出" << endl;
	cout << "********************************************" << endl;

	char c;
	while (cin >> c)
	{
		switch (c)
		{
		case 'a':
			play();
			break;
		case 'b':
			query();
			break;
		case 'c':
			rank();
			break;
		case 'q':
			logout();
			return;
		default:
			cout << "指令错误,请重新输入。" << endl;
			break;
		}

		cout << "********************************************" << endl;
		cout << "      a.闯关 b.查询 c.查看排行榜 q.退出" << endl;
		cout << "********************************************" << endl;
	}
}

void Player::play()
{
	string ans, word, diffLevel;
	while (true)
	{
		//根据count选择当前关卡难度
		if (count < EASY_COUNT)
		{
			diffLevel = "easy";
			ans = data->getWord(easy);
		}
		else if (count < MEDIUM_COUNT)
		{
			diffLevel = "medium";
			ans = data->getWord(medium);
		}
		else
		{
			diffLevel = "hard";
			ans = data->getWord(hard);
		}

		if (ans == EMPTY)
		{
			cout << "当前" << diffLevel << "难度无单词。" << endl;
			return;
		}

		//清屏
		system("cls");
		cout << "第" << count + 1 << "关,当前难度为" << diffLevel << endl << ans << endl;
		//限时显示单词
		Sleep(DEFAULT_TIME - count * TIME_RATE);


		char c;
		//非阻塞检测键盘输入，若有输入则全部读取，防止用户再能看到单词的时候将单词输入
		while (_kbhit())
		{
			c = _getch();
		}

		system("cls");

		auto start = clock();
		cout << "请输入该单词,输入#quit退出。" << endl;
		if (cin >> word && word != EXIT)
		{
			//记录答题时间
			double duration = (double)(clock() - start) / CLOCKS_PER_SEC;
			//闯关成功
			if (word == ans)
			{
				++count;
				int addExp = EACH_EXP + min(10, count / EXP_COUNT_RATE) / duration;
				exp += addExp;
				//升级
				if (exp > MAX_EXP)
				{
					exp = 0;
					cout << "您已升到" << ++level << "级。\n按下任意键继续。" << endl;
					getchar();
					getchar();
				}
				//刷新用户信息
				data->update(name, count, exp, level);
			}
			//闯关失败
			else
			{
				cout << "闯关失败。该单词为:" << ans << "\n按下任意键继续。" << endl;
				getchar();
				getchar();
			}
		}
		else
			return;
	}
}

void WordMaker::choice()
{
	cout << "********************************************" << endl;
	cout << "      a.出题 b.查询 c.查看排行榜 q.退出" << endl;
	cout << "********************************************" << endl;

	char c;
	while (cin >> c)
	{
		switch (c)
		{
		case 'a':
			addWord();
			break;
		case 'b':
			query();
			break;
		case 'c':
			rank();
			break;
		case 'q':
			logout();
			return;
		default:
			cout << "指令错误,请重新输入。" << endl;
			break;
		}

		cout << "********************************************" << endl;
		cout << "      a.出题 b.查询 c.查看排行榜 q.退出" << endl;
		cout << "********************************************" << endl;
	}
}

void WordMaker::addWord()
{
	cout << "********************************************" << endl;
	cout << "          请输入新单词,输入#quit退出。" << endl;
	cout << "********************************************" << endl;

	string word;
	while (cin >> word && word != EXIT)
	{
		//将输入转化为小写
		for (char& c : word)
			c = tolower(c);

		//添加单词成功
		if (data->addWord(word))
		{
			++count;
			cout << "出题成功。" << endl;

			int addExp = EACH_EXP + min(10, count / EXP_COUNT_RATE);
			exp += addExp;
			//升级
			if (exp > MAX_EXP)
			{
				exp = 0;
				cout << "您已升到" << ++level << "级。" << endl;
			}
			//更新用户信息
			data->update(name, count, exp, level);
		}

		else
		{
			cout << "该单词已存在。" << endl;
		}

		cout << "********************************************" << endl;
		cout << "          请输入新单词,输入#quit退出。" << endl;
		cout << "********************************************" << endl;
	}
}