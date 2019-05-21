#ifndef COMMON_H
#define COMMON_H


#define _WIN32_WINNT 0x0601

#include<iostream>
#include<string>
#include<sstream>
#include<cctype>
#include<boost/asio.hpp>     //boost::asio网络编程库
#include<ctime>
#include<conio.h>            //_kbhit() 非阻塞检测键盘输入

using namespace std;
using namespace boost::asio;


//难度分级以及判断单词难度的长度界限
enum diffType { easy, medium, hard, easyLimit = 5, mediumLimit = 10 };
//每关的基础经验
const int EACH_EXP(10);
//达到MAX_EXP升级
const int MAX_EXP(100);
//闯关超过对应COUNT后提升关卡难度
const int EASY_COUNT(10);
const int MEDIUM_COUNT(50);
//默认的单词显示时间
const int DEFAULT_TIME(2000);
//单词显示时间函数的系数
const int TIME_RATE(10);
//获得经验函数的系数
const int EXP_COUNT_RATE(10);
const string EXIT("#quit");
const string EXIST("exist");
const string EMPTY("empty");
const string wrongKey("wrongkey");
const string hasLogined("hasLogined");
const char PLAYER('0');
const char WORDMAKER('1');
const char rankByCount('a');
const char rankByExp('b');
const char rankByLevel('c');


#endif
