#include"menu.h"
#include"user.h"
#include"database.h"
#include"common.h"


Database* Menu::data = nullptr;


void LoginMenu::login() const
{
	User* user = nullptr;
	string name, key;

	do
	{
		cout << "�������û���,����#quit�˳���" << endl;
		cin >> name;
		if (name != EXIT)
		{

			cout << "���������롣" << endl;
			cin >> key;
			//����������͵�¼�����������Ϣ����buf��
			string buff(data->login(name, key));

			if (buff == EMPTY)
			{
				cout << "�û������ڡ�" << endl;
			}
			else if (buff == wrongKey)
			{
				cout << "�������" << endl;
			}
			else if (buff == hasLogined)
			{
				cout << "���û��ѵ�¼��" << endl;
			}
			else
			{
				cout << "��½�ɹ���" << endl;

				istringstream s(buff);
				int count, exp, level;
				char type;
				s >> count >> exp >> level >> type;
				if (type == PLAYER)
					user = new Player(name, key, count, exp, level);
				else
					user = new WordMaker(name, key, count, exp, level);
				break;
			}
		}
		//�û������˳�
		else
		{
			break;
		}
	} while (true);

	//��½�ɹ�
	if (user)
	{
		//����ѡ�����
		user->choice();
		//���delete user
		delete user;
		user = nullptr;
	}
}

void RegisterMenu::_register() const
{
	char c;
	string name, keyword1, keyword2;

	do
	{
		cout << "�������û���,����#quit�˳���" << endl;
		if (cin >> name && name != EXIT)
		{
			//�û��Ѵ���
			if (data->hasUser(name))
			{
				cout << "�û��Ѵ��ڡ�" << endl;
				continue;
			}
			//��������
			do
			{
				cout << "���������롣" << endl;
				cin >> keyword1;
				cout << "���ظ����롣" << endl;
				cin >> keyword2;

				if (keyword1 == keyword2)
				{
					break;
				}
				else
				{
					cout << "�������벻һ��,�������������롣" << endl;
				}
			} while (true);
			//�����û�����
			do
			{
				cout << "�����Ϊ��\na.������\tb.������" << endl;
				cin >> c;
				if (c == 'a')
				{
					cout << "ע��ɹ���" << endl;
					data->_register(name, keyword1, PLAYER);
					return;
				}
				else if (c == 'b')
				{
					cout << "ע��ɹ���" << endl;
					data->_register(name, keyword1, WORDMAKER);
					return;
				}
				else
				{
					cout << "�������" << endl;
				}

			} while (true);
		}
		//�û������˳�
		else
		{
			break;
		}

	} while (true);
}

