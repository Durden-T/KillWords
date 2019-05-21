#ifndef  DICTIONARY_H
#define DICTIONARY_H
//[1,5) [5,10),[10,...)


#include"common.h"


class Dictionary
{
public:
	Dictionary();

	~Dictionary();

	//该单词已存在返回false，否则添加成功，返回true
	bool addWord(const string& word);

	//根据难度获取单词，返回该单词
	const string& getWord(Type type) const;


private:
	//从文件中读取单词，按难度存放在data中
	ofstream file[DIFF_COUNT];
	vector<string> data[DIFF_COUNT];
	//快速查找单词是否存在
	unordered_set<string> table;
};


#endif

