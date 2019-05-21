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
	cout << "     ������Ҫ��ѯ���û���,����#quit�˳���\n";
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
			cout << "���û������ڡ�\n";
		}

		cout << "********************************************\n";
		cout << "     ������Ҫ��ѯ���û���,����#quit�˳���\n";
		cout << "********************************************\n";
	}
}

void User::queryRank() const
{
	cout << "********************************************\n";
	cout << "        a.���������� b.���������� q.�˳�\n";
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
			cout << "ָ�����,���������롣\n";
			break;
		}

		cout << "********************************************\n";
		cout << "        a.���������� b.���������� q.�˳�\n";
		cout << "********************************************\n";
	}
}


void Player::choice()
{
	cout << "********************************************\n";
	cout << "      a.���� b.��ѯ c.�鿴���а� q.�˳�\n";
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
			cout << "ָ�����,���������롣\n";
			break;
		}

		cout << "********************************************\n";
		cout << "      a.���� b.��ѯ c.�鿴���а� q.�˳�\n";
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
			cout << "��ǰ" << diffLevel << "�Ѷ��޵��ʡ�\n";
			return;
		}

		system("cls");
		cout << "��" << count + 1 << "��,��ǰ�Ѷ�Ϊ" << diffLevel << endl << ans << endl;
		Sleep(DEFAULT_TIME - count * TIME_RATE);


		char c;//��ֹ�û�����
		while (_kbhit())
		{
			c = _getch();
		}

		system("cls");

		auto start = clock();
		cout << "������õ���,����#quit�˳���\n";
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
					cout << "��������" << ++level << "����\n���������������\n";
					getchar();
					getchar();
				}
			}
			else
			{
				cout << "����ʧ�ܡ��õ���Ϊ:" << ans << "\n���������������\n";
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
	cout << "      a.���� b.��ѯ c.�鿴���а� q.�˳�\n";
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
			cout << "ָ�����,���������롣\n";
			break;
		}

		cout << "********************************************\n";
		cout << "      a.���� b.��ѯ c.�鿴���а� q.�˳�\n";
		cout << "********************************************\n";
	}
}

void WordMaker::makeWord()
{
	cout << "********************************************\n";
	cout << "          �������µ���,����#quit�˳���\n";
	cout << "********************************************\n";

	string word;
	while (cin >> word && word != EXIT)
	{
		for (char& c : word)
			c = tolower(c);

		if (dict.addWord(move(word)))
		{
			++count;
			cout << "����ɹ���\n";

			int addExp = EACH_EXP + min(10, count / EXP_COUNT_RATE);
			if ((exp += addExp) > MAX_EXP)
			{
				exp = 0;
				cout << "��������" << ++level << "����\n";
			}
		}
		else
		{
			cout << "�õ����Ѵ��ڡ�\n";
		}

		cout << "********************************************\n";
		cout << "          �������µ���,����#quit�˳���\n";
		cout << "********************************************\n";
	}
}