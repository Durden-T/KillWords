#include<sstream>
#include<algorithm>

#include"database.h"
#include"menu.h"
#include"user.h"
#include"common.h"


bool cmpWithCount(User* a, User* b);
bool cmpWithExp(User* a, User* b);
bool cmpWithLevel(User* a, User* b);


Database::Database()
{
	//�����ݿ�����ӳ�ʼ��
	Menu::connectWithDatabase(this);
	User::connectWithDatabase(this);

	//��ֹ�ļ��в�����
	CreateDirectoryA("C:\\killWords", NULL);
	CreateDirectoryA("C:\\killWords\\player", NULL);
	CreateDirectoryA("C:\\killWords\\wordMaker", NULL);

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
	playerIn.close();
	wordMakerIn.close();
}

Database::~Database()
{
	update();

	for (User* p : players)
		delete p;

	for (User* p : wordMakers)
		delete p;
}

void Database::playerRank()
{
	if (players.empty())
	{
		cout << "Ŀǰ�޴����ߡ�\n";
		return;
	}

	cout << "********************************************\n";
	cout << "a.���ݴ����� b.���ݾ���ֵ c.���ݵȼ� q.�˳�\n";
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
			cout << "ָ�����,���������롣\n";
			break;
		}

		cout << "********************************************\n";
		cout << "a.���ݴ����� b.���ݾ���ֵ c.���ݵȼ� q.�˳�\n";
		cout << "********************************************\n";
	}
}

void Database::wordMakerRank()
{
	if (wordMakers.empty())
	{
		cout << "Ŀǰ�޳����ߡ�\n";
		return;
	}

	cout << "********************************************\n";
	cout << "a.���ݳ����� b.���ݾ���ֵ c.���ݵȼ� q.�˳�\n";
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
			cout << "ָ�����,���������롣\n";
			break;
		}

		cout << "********************************************\n";
		cout << "a.���ݳ����� b.���ݾ���ֵ c.���ݵȼ� q.�˳�\n";
		cout << "********************************************\n";
	}
}

void Database::update()
{
	ofstream playerFile("C:\\killWords\\player\\playerFile.txt", ios::trunc), wordMakerFile("C:\\killWords\\wordMaker\\wordMakerFile.txt", ios::trunc);
	for (User* t : players)
		t->addToData(playerFile);
	playerFile.close();

	for (User* t : wordMakers)
		t->addToData(wordMakerFile);
	wordMakerFile.close();
}



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