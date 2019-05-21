#include"dictionary.h"
#include"common.h"


Dictionary::Dictionary()
{
	srand(time(NULL));
	//防止文件夹不存在
	CreateDirectoryA("C:\\killWords\\dictionary", NULL);

	string buf;
	//打开字典文件，按难度缓存起来
	ifstream dictIn("C:\\killWords\\dictionary\\dictEasy.txt");
	while (dictIn >> buf)
	{
		table.insert(buf);
		data[easy].emplace_back(move(buf));
	}
	dictIn.close();

	dictIn.open("C:\\killWords\\dictionary\\dictMedium.txt");
	while (dictIn >> buf)
	{
		table.insert(buf);
		data[medium].emplace_back(move(buf));
	}
	dictIn.close();

	dictIn.open("C:\\killWords\\dictionary\\dictHard.txt");
	while (dictIn >> buf)
	{
		table.insert(buf);
		data[hard].emplace_back(move(buf));
	}
	dictIn.close();

	//输入完成，打开各难度的输出流，为添加单词做准备
	file[easy].open("C:\\killWords\\dictionary\\dictEasy.txt", ios::app);
	file[medium].open("C:\\killWords\\dictionary\\dictMedium.txt", ios::app);
	file[hard].open("C:\\killWords\\dictionary\\dictHard.txt", ios::app);
}

Dictionary::~Dictionary()
{
	//关闭输出流
	file[easy].close();
	file[medium].close();
	file[hard].close();
}

bool Dictionary::addWord(const string& word)
{
	//已包含该单词
	if (table.count(word))
		return false;

	table.insert(word);

	//为该单词判断难度，放入对应难度的字典
	if (word.size() < easyLimit)
	{
		data[easy].push_back(word);
		file[easy] << word << ' ';
	}
	else if (word.size() < mediumLimit)
	{
		data[medium].push_back(word);
		file[medium] << word << ' ';
	}
	else
	{
		data[hard].push_back(word);
		file[hard] << word << ' ';
	}
	//添加成功
	return true;
}

const string& Dictionary::getWord(Type type) const
{
	//获取对应难度的字典
	auto& d = data[type];
	//若非空，随机返回一个词
	return d.empty() ? EMPTY : d[rand() % d.size()];
}