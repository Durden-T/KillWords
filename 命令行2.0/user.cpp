#include"user.h"
#include"database.h"
#include"dictionary.h"
#include"common.h"


Dictionary User::dict;
Database* User::data = nullptr;


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
			break;
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

		system("cls");
		cout << "第" << count + 1 << "关,当前难度为" << diffLevel << endl << ans << endl;
		Sleep(DEFAULT_TIME - count * TIME_RATE);


		char c;//防止用户输入
		while (_kbhit())
		{
			c = _getch();
		}

		system("cls");

		auto start = clock();
		cout << "请输入该单词,输入#quit退出。\n";
		if (cin >> word && word != EXIT)
		{
			double duration = (double)(clock() - start) / CLOCKS_PER_SEC;
			if (word == ans)
			{
				++count;
				int addExp = EACH_EXP + min(10, count / EXP_COUNT_RATE) / duration;
				if ((exp += addExp) > MAX_EXP)
				{
					exp = 0;
					cout << "您已升到" << ++level << "级。\n按下任意键继续。\n";
					getchar();
					getchar();
				}
			}
			else
			{
				cout << "闯关失败。该单词为:" << ans << "\n按下任意键继续。\n";
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
		for (char& c : word)
			c = tolower(c);

		if (dict.addWord(move(word)))
		{
			++count;
			cout << "出题成功。\n";

			int addExp = EACH_EXP + min(10, count / EXP_COUNT_RATE);
			if ((exp += addExp) > MAX_EXP)
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