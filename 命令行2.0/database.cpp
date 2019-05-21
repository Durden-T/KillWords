#include<sstream>
#include<algorithm>

#include"database.h"
#include"menu.h"
#include"user.h"
#include"common.h"

//声明
bool cmpWithCount(User* a, User* b);
bool cmpWithExp(User* a, User* b);
bool cmpWithLevel(User* a, User* b);


Database::Database()
{
	//对数据库的链接初始化
	Menu::connectWithDatabase(this);
	User::connectWithDatabase(this);

	//防止文件夹不存在
	CreateDirectoryA("C:\\killWords", NULL);
	CreateDirectoryA("C:\\killWords\\player", NULL);
	CreateDirectoryA("C:\\killWords\\wordMaker", NULL);

	//读取文件中用户信息
	ifstream playerIn("C:\\killWords\\player\\playerFile.txt"), wordMakerIn("C:\\killWords\\wordMaker\\wordMakerFile.txt");
	string line, name, key;
	int count, exp, level;
	while (getline(playerIn, line))
	{
		istringstream s(line);
		s >> name >> key >> count >> exp >> level;
		User* t = new Player(name, key, count, exp, level);
		players.push_back(t);
		userTable.emplace(move(name), move(t));
	}

	while (getline(wordMakerIn, line))
	{
		istringstream s(line);
		s >> name >> key >> count >> exp >> level;
		User* t = new WordMaker(name, key, count, exp, level);
		wordMakers.push_back(t);
		userTable.emplace(move(name), move(t));
	}

	//关闭文件流
	playerIn.close();
	wordMakerIn.close();
}

Database::~Database()
{
	//析构时，向文件更新信息
	update();

	//delete 用户
	for (User* p : players)
	{
		delete p;
		p = nullptr;
	}
	for (User* p : wordMakers)
	{
		delete p;
		p = nullptr;
	}
}

void Database::playerRank()
{
	if (players.empty())
	{
		cout << "目前无闯关者。\n";
		return;
	}

	cout << "********************************************\n";
	cout << "a.根据闯关数 b.根据经验值 c.根据等级 q.退出\n";
	cout << "********************************************\n";

	char c;
	while (cin >> c)
	{
		switch (c)
		{
		case 'a':
			rankWithCountAndPrint(players);
			break;
		case 'b':
			rankWithCountAndPrint(players);
			break;
		case 'c':
			rankWithLevelAndPrint(players);
			break;
		case 'q':
			return;
			break;
		default:
			cout << "指令错误,请重新输入。\n";
			break;
		}

		cout << "********************************************\n";
		cout << "a.根据闯关数 b.根据经验值 c.根据等级 q.退出\n";
		cout << "********************************************\n";
	}
}

void Database::wordMakerRank()
{
	if (wordMakers.empty())
	{
		cout << "目前无出题者。\n";
		return;
	}

	cout << "********************************************\n";
	cout << "a.根据出题数 b.根据经验值 c.根据等级 q.退出\n";
	cout << "********************************************\n";

	char c;
	while (cin >> c)
	{
		switch (c)
		{
		case 'a':
			rankWithCountAndPrint(wordMakers);
			break;
		case 'b':
			rankWithCountAndPrint(wordMakers);
			break;
		case 'c':
			rankWithLevelAndPrint(wordMakers);
			break;
		case 'q':
			return;
			break;
		default:
			cout << "指令错误,请重新输入。\n";
			break;
		}

		cout << "********************************************\n";
		cout << "a.根据出题数 b.根据经验值 c.根据等级 q.退出\n";
		cout << "********************************************\n";
	}
}

void Database::update()
{
	//打开输出流
	ofstream playerFile("C:\\killWords\\player\\playerFile.txt", ios::trunc), wordMakerFile("C:\\killWords\\wordMaker\\wordMakerFile.txt", ios::trunc);
	//为每个用户添加信息到文件中
	for (User* t : players)
		t->addToData(playerFile);
	playerFile.close();
	for (User* t : wordMakers)
		t->addToData(wordMakerFile);
	wordMakerFile.close();
}


//简单的排序，可以分开建立排好序的文件，每次更新，注册重新单次插入
void Database::rankWithCountAndPrint(vector<User*>& src)
{
	sort(src.begin(), src.end(), cmpWithCount);
	printUsers(src);
}

void Database::rankWithExpAndPrint(vector<User*>& src)
{
	sort(src.begin(), src.end(), cmpWithExp);
	printUsers(src);
}

void Database::rankWithLevelAndPrint(vector<User*>& src)
{
	sort(src.begin(), src.end(), cmpWithLevel);
	printUsers(src);
}

void Database::printUsers(vector<User*>& src)
{
	cout << '\n';
	for (User* p : src)
		p->printInfo();
	cout << '\n';
}

//增加新用户
void Database::addPlayer(User* t)
{
	players.push_back(t);
	userTable.emplace(t->getName(), t);
}

void Database::addWordMaker(User* t)
{
	wordMakers.push_back(t);
	userTable.emplace(t->getName(), t);
}