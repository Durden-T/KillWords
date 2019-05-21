#ifndef MENU_H
#define MENU_H


class Database;


//����¼�˵���ע��˵��Ĺ�ͬ���ܳ������menu����ǰ���߼̳�menu�����ں����ĸ���
class Menu
{
public:
	virtual ~Menu() = default;

	//��ʼ����Database������
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

