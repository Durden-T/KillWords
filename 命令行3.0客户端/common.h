#ifndef COMMON_H
#define COMMON_H


#define _WIN32_WINNT 0x0601

#include<iostream>
#include<string>
#include<sstream>
#include<cctype>
#include<boost/asio.hpp>     //boost::asio�����̿�
#include<ctime>
#include<conio.h>            //_kbhit() ����������������

using namespace std;
using namespace boost::asio;


//�Ѷȷּ��Լ��жϵ����Ѷȵĳ��Ƚ���
enum diffType { easy, medium, hard, easyLimit = 5, mediumLimit = 10 };
//ÿ�صĻ�������
const int EACH_EXP(10);
//�ﵽMAX_EXP����
const int MAX_EXP(100);
//���س�����ӦCOUNT�������ؿ��Ѷ�
const int EASY_COUNT(10);
const int MEDIUM_COUNT(50);
//Ĭ�ϵĵ�����ʾʱ��
const int DEFAULT_TIME(2000);
//������ʾʱ�亯����ϵ��
const int TIME_RATE(10);
//��þ��麯����ϵ��
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
