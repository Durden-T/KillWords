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
	cout << "     ������Ҫ��ѯ���û���,����#quit�˳���" << endl;
	cout << "********************************************" << endl;

	string name;
	while (cin >> name && name != EXIT)
	{
		string t(data->query(name));
		if (t == EMPTY)
		{
			cout << "�û������ڡ�" << endl;
			cout << "********************************************" << endl;
			cout << "     ������Ҫ��ѯ���û���,����#quit�˳���" << endl;
			cout << "********************************************" << endl;
			continue;
		}

		//������û���Ϣ
		istringstream s(t);
		char type;
		int count, exp, level;
		s >> count >> exp >> level >> type;
		cout << "�û���:" << name << "\t" << (type == PLAYER ? "������:" : "������:") << count << "\t����ֵ:" << exp << "\t�ȼ�:" << level << endl;

		cout << "********************************************" << endl;
		cout << "     ������Ҫ��ѯ���û���,����#quit�˳���" << endl;
		cout << "********************************************" << endl;
	}
}

void User::rank() const
{
	cout << "********************************************" << endl;
	cout << "        a.���������� b.���������� q.�˳�" << endl;
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
			cout << "ָ�����,���������롣" << endl;
			break;
		}

		cout << "********************************************" << endl;
		cout << "        a.���������� b.���������� q.�˳�" << endl;
		cout << "********************************************" << endl;
	}
}

void User::chooseRankBy(char type) const
{
	cout << "********************************************" << endl;
	cout << "a.����" << (type == PLAYER ? "����" : "����") << "�� b.���ݾ���ֵ c.���ݵȼ� q.�˳�" << endl;
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
					cout << "�û���:" << name << "\t" << (type == PLAYER ? "������:" : "������:") << count << "\t����ֵ:" << exp << "\t�ȼ�:" << level << endl;
				}
			}
			else
			{
				cout << "��ǰ��" << (type == PLAYER ? "�����ߡ�" : "�����ߡ�") << endl;
			}

		}
		//�û�Ҫ���˳�
		else if (c == 'q')
		{
			break;
		}
		else
		{
			cout << "�������" << endl;
		}

		cout << "********************************************" << endl;
		cout << "a.����" << (type == PLAYER ? "����" : "����") << "�� b.���ݾ���ֵ c.���ݵȼ� q.�˳�" << endl;
		cout << "********************************************" << endl;
	}
}

void Player::choice()
{
	cout << "********************************************" << endl;
	cout << "      a.���� b.��ѯ c.�鿴���а� q.�˳�" << endl;
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
			cout << "ָ�����,���������롣" << endl;
			break;
		}

		cout << "********************************************" << endl;
		cout << "      a.���� b.��ѯ c.�鿴���а� q.�˳�" << endl;
		cout << "********************************************" << endl;
	}
}

void Player::play()
{
	string ans, word, diffLevel;
	while (true)
	{
		//����countѡ��ǰ�ؿ��Ѷ�
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
			cout << "��ǰ" << diffLevel << "�Ѷ��޵��ʡ�" << endl;
			return;
		}

		//����
		system("cls");
		cout << "��" << count + 1 << "��,��ǰ�Ѷ�Ϊ" << diffLevel << endl << ans << endl;
		//��ʱ��ʾ����
		Sleep(DEFAULT_TIME - count * TIME_RATE);


		char c;
		//���������������룬����������ȫ����ȡ����ֹ�û����ܿ������ʵ�ʱ�򽫵�������
		while (_kbhit())
		{
			c = _getch();
		}

		system("cls");

		auto start = clock();
		cout << "������õ���,����#quit�˳���" << endl;
		if (cin >> word && word != EXIT)
		{
			//��¼����ʱ��
			double duration = (double)(clock() - start) / CLOCKS_PER_SEC;
			//���سɹ�
			if (word == ans)
			{
				++count;
				int addExp = EACH_EXP + min(10, count / EXP_COUNT_RATE) / duration;
				exp += addExp;
				//����
				if (exp > MAX_EXP)
				{
					exp = 0;
					cout << "��������" << ++level << "����\n���������������" << endl;
					getchar();
					getchar();
				}
				//ˢ���û���Ϣ
				data->update(name, count, exp, level);
			}
			//����ʧ��
			else
			{
				cout << "����ʧ�ܡ��õ���Ϊ:" << ans << "\n���������������" << endl;
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
	cout << "      a.���� b.��ѯ c.�鿴���а� q.�˳�" << endl;
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
			cout << "ָ�����,���������롣" << endl;
			break;
		}

		cout << "********************************************" << endl;
		cout << "      a.���� b.��ѯ c.�鿴���а� q.�˳�" << endl;
		cout << "********************************************" << endl;
	}
}

void WordMaker::addWord()
{
	cout << "********************************************" << endl;
	cout << "          �������µ���,����#quit�˳���" << endl;
	cout << "********************************************" << endl;

	string word;
	while (cin >> word && word != EXIT)
	{
		//������ת��ΪСд
		for (char& c : word)
			c = tolower(c);

		//��ӵ��ʳɹ�
		if (data->addWord(word))
		{
			++count;
			cout << "����ɹ���" << endl;

			int addExp = EACH_EXP + min(10, count / EXP_COUNT_RATE);
			exp += addExp;
			//����
			if (exp > MAX_EXP)
			{
				exp = 0;
				cout << "��������" << ++level << "����" << endl;
			}
			//�����û���Ϣ
			data->update(name, count, exp, level);
		}

		else
		{
			cout << "�õ����Ѵ��ڡ�" << endl;
		}

		cout << "********************************************" << endl;
		cout << "          �������µ���,����#quit�˳���" << endl;
		cout << "********************************************" << endl;
	}
}