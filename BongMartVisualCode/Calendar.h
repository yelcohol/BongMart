#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <conio.h>
#include <time.h>
#include <Windows.h>
#define MAX_STR 100
#pragma warning (disable:4996)

using namespace std;




class Calendar {
private:
	char str_month[13][10] = { "00000","January","Febuary","March","April","May","June","July","August","September","October","Nobember","December" };
	time_t curr_sec;
	struct tm* curr_time;


	typedef struct s_schedule {
		//int sch_year;
		//int sch_month;
		string sch_type;						// a = ���� ������ , b = ������ + ��� , c = ��縸 , d = �����ϸ� , e = �� �� �˸�(��Ÿ,���� �� / �̰��� ui �� �����ؼ� ǥ���Ұ�!)
		int sch_day;
		int sch_start_hour;
		int sch_start_min;
		int sch_end_hour;
		int sch_end_min;
		char sch_note[MAX_STR];
		//char* sch_note;
	}Schedule;

	Schedule schedule[10][11][13];		//2019�� ~ 2029����� ������ ���� ����!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	int num_sch[11][13];
	int year, month, day, wday, hour, minute;

	bool powerCal = false;


public:
	Calendar();
	~Calendar();

	void reset_curr_time();


	void scheduleRead(string filename);
	void scheduleWrite();

	int dayMonthLimit(int mon);

	void drawDay(int day_week_1);

	void compareDay();

	void keyInput(int key_input);

	void drawCalender();

	int D_day(int d_year, int d_month, int d_day);


	vector<int> returnTime();
	//void deletePast();

	void PowerCalON();
	bool checkPowerCal();
	// �޷��� ����ϴ� Ŭ����, �⺻������ �޷¿��� ������ �߰�, ����, ������ �� �ְ� �װ͵��� ������ ���Ϸ� �����
	// �˹ٻ����� ��� ������ ����(��Ÿ��), ������ ���űⰣ�� 1���Ŀ� ���� ����, ������(������) ǥ�� ��� �߰�!!
	// ���� �߿��� �ð��κ��� Clock Ŭ������ ������ �Ǿ���

	//calendar.c ���� ���� ��
	

};