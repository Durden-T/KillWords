#ifndef COMMON_H
#define COMMON_H


#include<iostream>
#include<fstream>
#include<vector>
#include<unordered_map>
#include<unordered_set>
#include<windows.h>         //Sleep�Լ�����Ŀ¼����
#include<ctime>
#include<string>
#include<conio.h>           //_kbhit() ����������������



using namespace std;

//�Ѷȷּ��Լ��жϵ����Ѷȵĳ��Ƚ���
enum Type { easy, medium, hard, easyLimit = 5, mediumLimit = 10 };
//�Ѷȷּ���������enum��ǿ�ɶ���
const int DIFF_COUNT(3);
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
const string EMPTY("empty");


#endif
