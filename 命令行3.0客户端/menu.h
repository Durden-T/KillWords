#ifndef MENU_H
#define MENU_H


class Database;


//将登录菜单和注册菜单的共同功能抽出放入menu，让前两者继承menu，便于后续的更新
class Menu
{
public:
	virtual ~Menu() = default;

	//初始化与Database的连接
	static void connectWithDatabase(Database* _data);

protected:
	static Database* data;
};


class LoginMenu :public Menu
{
public:
	void login() const;
};


class RegisterMenu :public Menu
{
public:
	void _register() const;
};


inline void Menu::connectWithDatabase(Database* _data)
{
	data = _data;
}


#endif

