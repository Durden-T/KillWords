#ifndef  DICTIONARY_H
#define DICTIONARY_H
//[1,5) [5,10),[10,...)


#include"common.h"


class Dictionary
{
public:
	Dictionary();

	~Dictionary();

	bool addWord(const string& word);

	const string& getWord(Type type) const;


private:
	ofstream file[DIFF_COUNT];
	vector<string> data[DIFF_COUNT];
	unordered_set<string> table;
};


#endif

