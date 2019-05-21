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
		cout << "请输入用户名,输入#quit退出。\n";
		cin >> name;
		if (name != EXIT)
		{
			//若该用户存在
			if (data->hasUser(name))
			{
				cout << "请输入密码。\n";
				cin >> inputKey;
				//密码正确
				if (inputKey == data->getKey(name))
				{
					cout << "登录成功。\n\n";
					break;
				}
				else
				{
					cout << "密码错误。\n";
				}
			}
			//用户不存在
			else
			{
				cout << "用户名不存在。\n";
			}
		}
		//用户要求退出
		else
		{
			return;
		}
	} while (true);

	User* user = data->getUser(name);
	//进入选择界面
	user->choice();
}

void RegisterMenu::_register() const
{
	cout << "请输入用户名,输入#quit退出。\n";
	string name, keyword1, keyword2;
	while (cin >> name)
	{
		if (name != EXIT)
		{
			if (!data->hasUser(name))
			{
				break;
			}
			//用户已存在
			else
			{
				cout << "用户名已存在。\n请输入用户名,输入#quit退出。\n";
			}
		}
		else
		{
			return;
		}
	}

	//设置密码
	do
	{
		cout << "请输入密码。\n";
		cin >> keyword1;
		cout << "请重复密码。\n";
		cin >> keyword2;
		if (keyword1 == keyword2)
		{
			break;
		}
		else
		{
			cout << "两次密码不一致,请重新设置密码。\n";
		}
	} while (true);

	char c;
	//选择用户类型
	do {
		cout << "您想成为：\na.闯关者\tb.出题者\n";
		cin >> c;
		if (c == 'a')
		{
			cout << "注册成功。\n\n";
			data->addPlayer(new Player(name, keyword1));
			break;
		}
		else if (c == 'b')
		{
			cout << "注册成功。\n\n";
			data->addWordMaker(new WordMaker(name, keyword1));
			break;
		}
	} while (true);
}

