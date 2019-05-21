#ifndef COMMON_H
#define COMMON_H


#include<iostream>
#include<fstream>
#include<vector>
#include<unordered_map>
#include<unordered_set>
#include<windows.h>         //Sleep以及创建目录函数
#include<ctime>
#include<string>
#include<conio.h>           //_kbhit() 非阻塞检测键盘输入



using namespace std;

//难度分级以及判断单词难度的长度界限
enum Type { easy, medium, hard, easyLimit = 5, mediumLimit = 10 };
//难度分级数，利用enum增强可读性
const int DIFF_COUNT(3);
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
const string EMPTY("empty");


#endif
