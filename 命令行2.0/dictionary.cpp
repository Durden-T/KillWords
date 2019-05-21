#include"dictionary.h"
#include"common.h"


Dictionary::Dictionary()
{
	srand(time(NULL));
	//��ֹ�ļ��в�����
	CreateDirectoryA("C:\\killWords\\dictionary", NULL);

	string buf;
	//���ֵ��ļ������ѶȻ�������
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

	//������ɣ��򿪸��Ѷȵ��������Ϊ��ӵ�����׼��
	file[easy].open("C:\\killWords\\dictionary\\dictEasy.txt", ios::app);
	file[medium].open("C:\\killWords\\dictionary\\dictMedium.txt", ios::app);
	file[hard].open("C:\\killWords\\dictionary\\dictHard.txt", ios::app);
}

Dictionary::~Dictionary()
{
	//�ر������
	file[easy].close();
	file[medium].close();
	file[hard].close();
}

bool Dictionary::addWord(const string& word)
{
	//�Ѱ����õ���
	if (table.count(word))
		return false;

	table.insert(word);

	//Ϊ�õ����ж��Ѷȣ������Ӧ�Ѷȵ��ֵ�
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
	//��ӳɹ�
	return true;
}

const string& Dictionary::getWord(Type type) const
{
	//��ȡ��Ӧ�Ѷȵ��ֵ�
	auto& d = data[type];
	//���ǿգ��������һ����
	return d.empty() ? EMPTY : d[rand() % d.size()];
}