#pragma once
#include <vector>
#include <iostream>
#include "Calendar.h"
using namespace std;

class Staff {
private:
	bool checker = true;
	int num_schedule_temp = 0;	// 스케줄 수
	int num_schedule = 0;		// 각 직원에 할당되는 진짜 스케줄 수.
	int num_staff;				// 직원 수	
								// 메모장에서 데이터를 읽어올 때는 void get_schedule(string filename) 메소드를 쓴다. 사용되는 배열인자는 num_schedule_temp.	
								// 입력된 staff1[num_schedule_temp]
	char new_name[10];				// 직원이름
	int pay_hour = 8350;				// 시급

	typedef struct staff_sch {
		int work_year;			// 계약상 출근 "년"
		int work_month;			// 계약상 출근 "월"
		int work_day;			// 계약상 출근 "일"
		int work_start_hour;	// 계약상 출근 "시"
		int work_start_min;		// 계약상 출근 "분"
		int work_end_hour;		// 계약상 퇴근 "시"
		int work_end_min;		// 계약상 퇴근 "분"
		double work_time_day;	// 하루 동안 일한 시간
		vector<int> cur_work_start;	//실제 출근한 시간
		vector<int> cur_work_end;	//실제 퇴근한 시간
	}Staff_schedule;

	Staff_schedule sch;
	Staff_schedule sch2[100];	// staff2 배열되는 스케줄.


	int negligence = 0;		// 근무 태만 횟수 (지각, 조기 퇴근 횟수)

	int long_pay = 0;						//연장수당
	int holiday_pay = 0;					//휴일수당
	int pay_month = 0;						//월급

	Calendar calendar;

public:
	Staff();
	// startday - 업무 시작일(연,월,일) 값 넣어주기!
	// 요일 별로 기본적으로 계약한 출퇴근 시간 넣어주기! - work_start_time, work_end_time
	~Staff();
	
	// 동적 할당된 메모리 전부 free해주기!

	void clear_staff();

	void result();

	void set_work_start(int staff_num, int schedule_num);							//실제 출근 시간 set
	void set_work_end(int staff_num, int schedule_num);								//실제 퇴근 시간 set
	void set_negligence();															// 근무태만횟수 set

	void calculate_work_time();		// 그 날 일한 시간 계산


	void get_schedule();		// 메모장으로부터 직원들의 스케줄을 받는다.
	void sort_schedule();					// 직원들의 스케줄을 정리한다.	


	void add_staff();						// 직원 추가: 직원 이름 입력받음.
	void delete_staff();					// 직원 삭제

	void edit_working_staff();				// 특정 날에 일하는 직원 교체, 대타 (각각의 직원 객체의 work_day_week배열 수정)


	void upgrade_pay_hour();				// 시급 인상, startday, negligence 고려해서

	void message_negligence();				// 지각, 조기퇴근 메모장으로 출력. 이름과 함께



	void pay();								// 연장수당, 휴일수당 계산
											// 파일출력
											// 월급명세서대용


	//void paystub();							// 월급 명세서(매주 초기화 되는거 고려해서 계산 잘해야함 , 계속 저장해두는 기능, 텍스트 파일로 출력)
											// (다음주나 다음달이 되었다고 날라가면 안됨, 텍스트파일로 저장해두든가)

	void print_all();						// 전체 직원 목록 출력, 한 직원을 선택하면 그 직원의 세부 정보가 나오도록! (객체의 print메소드 호출)

	void print_schedule_for_start();
	void print_schedule_for_end();

	//
};


