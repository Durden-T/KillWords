#ifndef COMMON_H
#define COMMON_H


#include<iostream>
#include<fstream>
#include<vector>
#include<unordered_map>
#include<unordered_set>
#include<windows.h>
#include<ctime>
#include<string>
#include<conio.h>


using namespace std;


enum Type { easy, medium, hard, easyLimit = 5, mediumLimit = 10 };
const int DIFF_COUNT = 3;
const int EACH_EXP = 10;
const int MAX_EXP = 100;
const int EASY_COUNT = 10;
const int MEDIUM_COUNT = 50;
const int DEFAULT_TIME = 2000;
const int TIME_RATE = 10;
const int EXP_COUNT_RATE = 10;
const string EXIT("#quit");
const string EMPTY("empty");


#endif
