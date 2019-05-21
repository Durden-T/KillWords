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
		cout << "请输入用户名,输入#quit退出。" << endl;
		cin >> name;
		if (name != EXIT)
		{

			cout << "请输入密码。" << endl;
			cin >> key;
			//向服务器发送登录命令，将返回信息存在buf中
			string buff(data->login(name, key));

			if (buff == EMPTY)
			{
				cout << "用户不存在。" << endl;
			}
			else if (buff == wrongKey)
			{
				cout << "密码错误。" << endl;
			}
			else if (buff == hasLogined)
			{
				cout << "该用户已登录。" << endl;
			}
			else
			{
				cout << "登陆成功。" << endl;

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
		//用户输入退出
		else
		{
			break;
		}
	} while (true);

	//登陆成功
	if (user)
	{
		//进入选择界面
		user->choice();
		//最后delete user
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
		cout << "请输入用户名,输入#quit退出。" << endl;
		if (cin >> name && name != EXIT)
		{
			//用户已存在
			if (data->hasUser(name))
			{
				cout << "用户已存在。" << endl;
				continue;
			}
			//设置密码
			do
			{
				cout << "请输入密码。" << endl;
				cin >> keyword1;
				cout << "请重复密码。" << endl;
				cin >> keyword2;

				if (keyword1 == keyword2)
				{
					break;
				}
				else
				{
					cout << "两次密码不一致,请重新设置密码。" << endl;
				}
			} while (true);
			//设置用户类型
			do
			{
				cout << "您想成为：\na.闯关者\tb.出题者" << endl;
				cin >> c;
				if (c == 'a')
				{
					cout << "注册成功。" << endl;
					data->_register(name, keyword1, PLAYER);
					return;
				}
				else if (c == 'b')
				{
					cout << "注册成功。" << endl;
					data->_register(name, keyword1, WORDMAKER);
					return;
				}
				else
				{
					cout << "输入错误。" << endl;
				}

			} while (true);
		}
		//用户输入退出
		else
		{
			break;
		}

	} while (true);
}

