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
		string sch_type;						// a = 직원 스케쥴 , b = 공휴일 + 행사 , c = 행사만 , d = 공휴일만 , e = 그 외 알림(대타,월급 등 / 이것은 ui 더 강조해서 표시할것!)
		int sch_day;
		int sch_start_hour;
		int sch_start_min;
		int sch_end_hour;
		int sch_end_min;
		char sch_note[MAX_STR];
		//char* sch_note;
	}Schedule;

	Schedule schedule[10][11][13];		//2019년 ~ 2029년까지 스케쥴 저장 가능!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
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
	// 달력을 담당하는 클래스, 기본적으로 달력에다 일정을 추가, 삭제, 수정할 수 있고 그것들은 별도의 파일로 저장됨
	// 알바생들의 모든 일정을 관리(대타도), 보건증 갱신기간인 1년후에 일정 생성, 공휴일(설날등) 표기 기능 추가!!
	// 일정 중에서 시간부분은 Clock 클래스와 연결이 되야함

	//calendar.c 파일 참고 ㅎ
	

};