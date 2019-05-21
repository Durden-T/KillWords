#ifndef MENU_H
#define MENU_H


class Database;


class Menu
{
public:
	virtual ~Menu() = default;

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

