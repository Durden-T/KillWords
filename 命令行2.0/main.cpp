#include"menu.h"
#include"database.h"
#include"common.h"


int main()
{
	Database data;
	LoginMenu loginMenu;
	RegisterMenu registerMenu;
	cout << "********************************************\n";
	cout << "                单词消除游戏\n";
	cout << "          a.登录  b.注册  q.退出\n";
	cout << "********************************************\n";

	char c;
	while (cin >> c)
	{
		switch (c)
		{
		case 'a':			
			loginMenu.login();
			break;

		case 'b':
			registerMenu._register();
			break;

		case 'q':
			return 0;

		default:
			cout << "指令错误,请重新输入。\n";
			break;
		}

		cout << "********************************************\n";
		cout << "                单词消除游戏\n";
		cout << "          a.登录  b.注册  q.退出\n";
		cout << "********************************************\n";
	}
}