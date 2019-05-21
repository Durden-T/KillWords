#include"menu.h"
#include"database.h"
#include"common.h"


int main()
{
	//获取实例
	Database& data = Database::Instance();

	cout << "********************************************" << endl;
	cout << "                单词消除游戏" << endl;
	cout << "          a.登录  b.注册  q.退出" << endl;
	cout << "********************************************" << endl;

	char c;
	while (cin >> c)
	{
		switch (c)
		{
		case 'a':
		{
			LoginMenu loginMenu;
			loginMenu.login();
			break;
		}
		case 'b':
		{
			RegisterMenu registerMenu;
			registerMenu._register();
			break;
		}
		case 'q':
			return 0;

		default:
			cout << "指令错误,请重新输入。" << endl;
			break;
		}

		cout << "********************************************" << endl;
		cout << "                单词消除游戏" << endl;
		cout << "          a.登录  b.注册  q.退出" << endl;
		cout << "********************************************" << endl;
	}
	return 0;
}