#include"menu.h"
#include"user.h"
#include"database.h"
#include"common.h"


Database* Menu::data = nullptr;


void LoginMenu::login() const
{
	string name, inputKey;
	do
	{
		cout << "�������û���,����#quit�˳���\n";
		cin >> name;
		if (name != EXIT)
		{
			if (data->hasUser(name))
			{
				cout << "���������롣\n";
				cin >> inputKey;
				if (inputKey == data->getKey(name))
				{
					cout << "��¼�ɹ���\n\n";
					break;
				}
				else
				{
					cout << "�������\n";
				}
			}
			else
			{
				cout << "�û��������ڡ�\n";
			}
		}
		else
		{
			return;
		}
	} while (true);

	User* user = data->getUser(name);

	user->choice();
}

void RegisterMenu::_register() const
{
	cout << "�������û���,����#quit�˳���\n";
	string name, keyword1, keyword2;
	while (cin >> name)
	{
		if (name != EXIT)
		{
			if (!data->hasUser(name))
			{
				break;
			}
			else
			{
				cout << "�û����Ѵ��ڡ�\n�������û���,����#quit�˳���\n";
			}
		}
		else
		{
			return;
		}
	}

	do
	{
		cout << "���������롣\n";
		cin >> keyword1;
		cout << "���ظ����롣\n";
		cin >> keyword2;
		if (keyword1 == keyword2)
		{
			break;
		}
		else
		{
			cout << "�������벻һ��,�������������롣\n";
		}
	} while (true);

	char c;
	do {
		cout << "�����Ϊ��\na.������\tb.������\n";
		cin >> c;
		if (c == 'a')
		{
			cout << "ע��ɹ���\n\n";
			data->addPlayer(new Player(name, keyword1));
			break;
		}
		else if (c == 'b')
		{
			cout << "ע��ɹ���\n\n";
			data->addWordMaker(new WordMaker(name, keyword1));
			break;
		}
	} while (true);
}

