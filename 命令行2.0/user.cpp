#include"user.h"
#include"database.h"
#include"dictionary.h"
#include"common.h"


//初始化字典
Dictionary User::dict;
Database* User::data = nullptr;


//比较函数
bool cmpWithCount(User* a, User* b)
{
	return a->count > b->count;
}

bool cmpWithExp(User* a, User* b)
{
	return a->exp > b->exp;
}

bool cmpWithLevel(User* a, User* b)
{
	return (a->level > b->level) || (a->level == b->level && a->exp > b->exp);
}


void User::query() const
{
	cout << "********************************************\n";
	cout << "     请输入要查询的用户名,输入#quit退出。\n";
	cout << "********************************************\n";

	string name;
	while (cin >> name && name != EXIT)
	{
		User* t = data->getUser(name);

		if (t)
		{
			cout << '\n';
			t->printInfo();
			cout << '\n';
		}
		else
		{
			cout << "该用户不存在。\n";
		}

		cout << "********************************************\n";
		cout << "     请输入要查询的用户名,输入#quit退出。\n";
		cout << "********************************************\n";
	}
}

void User::queryRank() const
{
	cout << "********************************************\n";
	cout << "        a.闯关者排名 b.出题者排名 q.退出\n";
	cout << "********************************************\n";

	char c;
	while (cin >> c)
	{
		switch (c)
		{
		case 'a':
			data->playerRank();
			break;
		case 'b':
			data->wordMakerRank();
			break;
		case 'q':
			return;
			break;
		default:
			cout << "指令错误,请重新输入。\n";
			break;
		}

		cout << "********************************************\n";
		cout << "        a.闯关者排名 b.出题者排名 q.退出\n";
		cout << "********************************************\n";
	}
}


void Player::choice()
{
	cout << "********************************************\n";
	cout << "      a.闯关 b.查询 c.查看排行榜 q.退出\n";
	cout << "********************************************\n";

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
			queryRank();
			break;
		case 'q':
			return;
		default:
			cout << "指令错误,请重新输入。\n";
			break;
		}

		cout << "********************************************\n";
		cout << "      a.闯关 b.查询 c.查看排行榜 q.退出\n";
		cout << "********************************************\n";
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
			ans = dict.getWord(easy);
		}
		else if (count < MEDIUM_COUNT)
		{
			diffLevel = "medium";
			ans = dict.getWord(medium);
		}
		else
		{
			diffLevel = "hard";
			ans = dict.getWord(hard);
		}

		if (ans == "")
		{
			cout << "当前" << diffLevel << "难度无单词。\n";
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
		cout << "请输入该单词,输入#quit退出。\n";
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
					cout << "您已升到" << ++level << "级。\n按下任意键继续。\n";
					getchar();
					getchar();
				}
			}
			//闯关失败
			else
			{
				cout << "闯关失败。该单词为:" << ans << "\n按下任意键继续。\n";
				getchar();
				getchar();
			}
		}
		//用户要求退出
		else
		{
			return;
		}
	}
}

void WordMaker::choice()
{
	cout << "********************************************\n";
	cout << "      a.出题 b.查询 c.查看排行榜 q.退出\n";
	cout << "********************************************\n";

	char c;
	while (cin >> c)
	{
		switch (c)
		{
		case 'a':
			makeWord();
			break;
		case 'b':
			query();
			break;
		case 'c':
			queryRank();
			break;
		case 'q':
			return;
			break;
		default:
			cout << "指令错误,请重新输入。\n";
			break;
		}

		cout << "********************************************\n";
		cout << "      a.出题 b.查询 c.查看排行榜 q.退出\n";
		cout << "********************************************\n";
	}
}

void WordMaker::makeWord()
{
	cout << "********************************************\n";
	cout << "          请输入新单词,输入#quit退出。\n";
	cout << "********************************************\n";

	string word;
	while (cin >> word && word != EXIT)
	{
		//将输入转化为小写
		for (char& c : word)
			c = tolower(c);

		//添加单词成功
		if (dict.addWord(move(word)))
		{
			++count;
			cout << "出题成功。\n";

			int addExp = EACH_EXP + min(10, count / EXP_COUNT_RATE);
			exp += addExp;
			//升级
			if (exp > MAX_EXP)
			{
				exp = 0;
				cout << "您已升到" << ++level << "级。\n";
			}
		}
		else
		{
			cout << "该单词已存在。\n";
		}

		cout << "********************************************\n";
		cout << "          请输入新单词,输入#quit退出。\n";
		cout << "********************************************\n";
	}
}