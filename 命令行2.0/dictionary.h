#ifndef  DICTIONARY_H
#define DICTIONARY_H
//[1,5) [5,10),[10,...)


#include"common.h"


class Dictionary
{
public:
	Dictionary();

	~Dictionary();

	//�õ����Ѵ��ڷ���false��������ӳɹ�������true
	bool addWord(const string& word);

	//�����ѶȻ�ȡ���ʣ����ظõ���
	const string& getWord(Type type) const;


private:
	//���ļ��ж�ȡ���ʣ����Ѷȴ����data��
	ofstream file[DIFF_COUNT];
	vector<string> data[DIFF_COUNT];
	//���ٲ��ҵ����Ƿ����
	unordered_set<string> table;
};


#endif

