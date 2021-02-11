#include "Staff.h"
#include "Calendar.h"
#include <string.h>
using namespace std;


Staff::Staff() {
}

Staff::~Staff() {
	//동적할당한 메모리들 free해주기
}

Staff staff1[100];	//get_schedule에서 필요한 객체.
Staff staff2[30];	//sort_schedule에서 필요한 객체.
					//최대 직원 수: 30
					//진짜 중요한 객체는 staff2 객체이다.

//현재 시간 리턴

//화면 출력
void Staff::result() {
	int input;
	if (checker) {
		get_schedule();
		sort_schedule();
		checker = false;
	}
	cout << "-숫자키 1 -  출근 체크" << endl;
	cout << "-숫자키 2 -  퇴근 체크" << endl;
	cout << "-숫자키 3 -  직원 월급 명세서" << endl;
	cout << "-숫자키 4 -  직원 추가" << endl;
	cout << "-숫자키 5 -  직원 삭제" << endl;
	cout << "숫자를 입력하세요: ";
	cin >> input;
	int staff_num, schedule_num;
	switch (input) {
	case 1:
		print_schedule_for_start();
		cout << "직원 번호 입력: ";
		cin >> staff_num;
		cout << "직원 스케줄 번호 입력: ";
		cin >> schedule_num;
		set_work_start(staff_num-1, schedule_num-1);
		cout << staff2[staff_num-1].new_name <<"님, 출근 처리되었습니다."<< endl;
		Sleep(3000);
		break;

	case 2:
		print_schedule_for_end();
		cout << "직원 번호 입력: ";
		cin >> staff_num;
		cout << "직원 스케줄 번호 입력: ";
		cin >> schedule_num;
		set_work_end(staff_num-1, schedule_num-1);
		cout << staff2[staff_num-1].new_name << "님, 퇴근 처리되었습니다." << endl;
		Sleep(3000);
		break;

	case3:
		cout << "매월 1일이 되면 staff_pay 파일로 만들어집니다. 매월 1일에 확인해주세요" << endl;
		if (calendar.returnTime().at(2) == 1) {				//한 달이 지나면(매월 1일이 되면)

			cout << "한 달이 지났습니다. 월급을 출력하겠습니다.\n" << endl;
			calculate_work_time();				//일한 시간 계산.
			set_negligence();
			message_negligence();			//근무태만횟수를 출력한다.
			pay();								//월급출력.
			upgrade_pay_hour();					//시급인상을 고려한다.

			clear_staff();						//스태프 정보 초기화.
		}
		Sleep(3000);
		break;

	case 4:
		print_all();
		add_staff();
		break;
	case 5:
		print_all();
		delete_staff();	
		break;
	default:
		break;
	}

	if (calendar.returnTime().at(2) == 1) {				//한 달이 지나면(매월 1일이 되면)

		cout << "한 달이 지났습니다. 월급을 출력하겠습니다.\n" << endl;
		calculate_work_time();				//일한 시간 계산.
		set_negligence();
		message_negligence();		//근무태만횟수를 출력한다.
		pay();								//월급출력.
		upgrade_pay_hour();					//시급인상을 고려한다.

		clear_staff();						//스태프 정보 초기화.
	}

}

// 스태프 정보 초기화
void Staff::clear_staff() {
	for (int i = 0; i < num_staff; i++) {
		this->pay_month, holiday_pay, long_pay = 0;

		this->negligence = 0;
	}

}



//출근 시간 set
void Staff::set_work_start(int staff_num, int schedule_num) {
	staff2[staff_num].sch2[schedule_num].cur_work_start = calendar.returnTime();
}

//퇴근시간 set
void Staff::set_work_end(int staff_num, int schedule_num) {
	staff2[staff_num].sch2[schedule_num].cur_work_end = calendar.returnTime();
}

//근무 태만 횟수 set
void Staff::set_negligence() {
	for (int i = 0; num_staff; i++)
		for (int j = 0; j < 30; j++) {
			//조기퇴근
			if ((staff2[i].sch2[j].work_end_hour - staff2[i].sch2[j].cur_work_end.at(4) > 0) || ((staff2[i].sch2[j].work_end_hour - staff2[i].sch2[j].cur_work_end.at(4) == 0) && (staff2[i].sch2[j].work_end_min - staff2[i].sch2[j].cur_work_end.at(5)) > 0))
				staff2[i].negligence++;
			//지각
			if ((staff2[i].sch2[j].cur_work_start.at(4) - staff2[i].sch2[j].work_start_hour > 0) || ((staff2[i].sch2[j].cur_work_start.at(4) - staff2[i].sch2[j].work_start_hour == 0) && (staff2[i].sch2[j].cur_work_start.at(5) - staff2[i].sch2[j].work_start_min) > 0))
				staff2[i].negligence++;
		}
}


// 그 날 일한 시간 계산
void Staff::calculate_work_time() {	//해당스태프번호, 해당스태프의스케줄번호
	for (int staff_num = 0; staff_num < num_staff; staff_num++) {
		for (int schedule_num = 0; schedule_num < 30; schedule_num++) {
			//스태프 해당 스케줄에 일한 시간 계산
			staff2[staff_num].sch2[schedule_num].work_time_day = ((staff2[staff_num].sch2[schedule_num].work_end_hour - staff2[staff_num].sch2[schedule_num].work_start_hour) * 60 + staff2[staff_num].sch2[schedule_num].work_end_min - staff2[staff_num].sch2[schedule_num].work_start_min) / 60.0;

			if (staff2[staff_num].sch2[schedule_num].work_time_day >= 8)	//8시간 이상 일하면
				staff2[staff_num].sch2[schedule_num].work_time_day = -1;	//1시간은 휴식시간

			else if (staff2[staff_num].sch2[schedule_num].work_time_day >= 4)	//4시간 이상 8시간 미만 일하면
				staff2[staff_num].sch2[schedule_num].work_time_day = -0.5;	//30분은 휴식시간
		}
	}
}

//staff_schedule 텍스트파일로부터 직원스케줄을 받기.
void Staff::get_schedule() {

	ifstream readFile;
	readFile.open("staff_schedule.txt");		//staff 목록   
	         
	//staff2에 직원 정렬.
	if (readFile.is_open()) { 
		while (!readFile.eof()) {
			char inputLine[100] = { 0, };
			readFile.getline(inputLine, 100);

			string r_type;

			r_type = strtok(inputLine, "/");
			staff1[num_schedule_temp].sch.work_year = atoi(strtok(NULL, "/"));
			staff1[num_schedule_temp].sch.work_month = atoi(strtok(NULL, "/"));
			staff1[num_schedule_temp].sch.work_day = atoi(strtok(NULL, "/"));
			staff1[num_schedule_temp].sch.work_start_hour = atoi(strtok(NULL, "/"));
			staff1[num_schedule_temp].sch.work_start_min = atoi(strtok(NULL, "/"));
			staff1[num_schedule_temp].sch.work_end_hour = atoi(strtok(NULL, "/"));
			staff1[num_schedule_temp].sch.work_end_min = atoi(strtok(NULL, "/"));
			strcpy(staff1[num_schedule_temp].new_name, strtok(NULL, "/"));
			this->num_schedule_temp++;
		}
	}
	readFile.close();
}

//staff 이름을 받고, 스케줄 정리
void Staff::sort_schedule() {
	ifstream readFile;
	readFile.open("staff_list.txt");		//staff 목록

	//staff2에 직원 정렬.
	if (readFile.is_open()) {
		while (!readFile.eof()) {
			char tmp[256];
			readFile.getline(tmp, 256);
			strcpy(staff2[num_staff].new_name,tmp);
			this->num_staff++;
		}
	}

	readFile.close();

	//staff2에 스케줄 정렬
	for (int i = 0; i < num_staff; i++) {
		for (int j = 0; j < num_schedule_temp; j++) {
			if (!strcmp(staff2[i].new_name, staff1[j].new_name)) {
				staff2[i].sch2[num_schedule] = staff1[j].sch;
				this->num_schedule++;
			}
		}
		this->num_schedule = 0;
	}
}


//직원 추가
void Staff::add_staff() {
	char add_staff_name[20];
	cout << "새로운 직원의 이름을 입력하세요 : ";
	cin >> add_staff_name;

	ofstream writeFile("staff_list.txt", ios::app);		//staff 목록
	writeFile << add_staff_name << endl;			//txt 파일에 직원 이름 추가
	strcpy(staff2[num_staff].new_name,add_staff_name);		//staff2 배열에 직원이름 추가
	num_staff++;										//staff_name 증가

	writeFile.close();

}

//직원 삭제
void Staff::delete_staff() {
	int delete_num;
	print_all();		//직원목록 전체 보여줌.

	cout << "삭제할 직원 번호를 입력하세요 : ";
	cin >> delete_num;
	this->num_staff--;

	// 예시
	// 1. 이태운 2. 이상윤 3. 이기태 4. 김태우
	// 2번을 삭제. 2번은 실제로 staff2[1]이다. 따라서, delete_num-1된 값을 삭제해야 한다.
	// num_staff는 3이다. 아직 4번은 staff[3] 저장되어 있음.
	// staff2[1]=staff[2]//이태운 이기태 이기태 김태우
	// staff2[2]=staff[3]//이태운 이기태 김태우 김태우
	for (int i = delete_num; i < num_staff; i++) {
		staff2[i - 1] = staff2[i];
	}
}

// 특정 날에 일하는 직원 교체, 대타 (각각의 직원 객체의 work_day_week배열 수정)
void Staff::edit_working_staff() {

}

// negligence가 한달동안 없으면 200원 인상.
void Staff::upgrade_pay_hour() {
	for (int i = 0; i < num_staff; i++)
		if (staff2[i].negligence == 0)			//negligence 횟수가 없다면
			staff2[i].pay_hour += 200;		//시급 200원 인상
}



void Staff::message_negligence() {
	ofstream File("staff_negligence.txt", ios::out);		//staff negligence 목록.
	set_negligence();
	for (int i = 0; i < num_staff; i++) {
		File << staff2[i].new_name << " 근무 태만 횟수: " << staff2[i].negligence << endl;			//txt 파일에 직원 이름과 근무태만횟수 출력.	
	}
	File.close();
}


// 월급 (꽤나 어려울듯!)
//주휴수당 (휴식시간 제외하는것도 고려해서! , 매 주마다 한 주 동안 일한 시간 초기화 되므로 급여를 매 주 계산해서 쌓아갈 필요 있음)
//, 야간수당, 추가수당(설날, 추석 등) 계산
//휴식시간 - 4시간이상이면 30분 0.5시간 , 8시간 이상이면 1시간 - 예를들어 8시간근무면 1시간 휴식하므로 7시간 일한것으로 계산!
//돈 클래스 참조, 거기서 돈이 줄어듬
//만약, 잔액이 모자랄 경우, 알림을 주고 미룸, 2주안에 줘야함 - 몇일남았다고 알려주고
void Staff::pay() {
	ofstream file;
	file.open("staff_pay.txt", ios::app);		//staff pay 목록

	for (int i = 0; i < num_staff; i++) {

		if (num_staff > 5) {					// 직원이 5인 이상이면 연장수당, 휴일수당
			for (int j = 0; j < 20; j++) {

				//하루에 일한 시간이 8시간 초과면 연장수당
				//연장수당은 기본 시급의 0.5배
				if (staff2[i].sch2[j].work_day > 8) {
					staff2[i].long_pay += (int)((staff2[i].sch2[j].work_day - 8) * staff2[i].pay_hour * 0.5);
				}

				//휴일수당은 휴일에 8시간 이하로 근무하면 기본 시급의 0.5배
				//휴일수당은 휴일에 8시간 초과하여 근무하면 기본 시급의 1배
				if (staff2[i].sch2[j].cur_work_start.at(3) == 0) {		//휴일에 일하였다면
					if (staff2[i].sch2[j].work_time_day > 8)
						staff2[i].holiday_pay += (int)((staff2[i].sch2[j].work_day - 8) * staff2[i].pay_hour * 1.0);
					else
						staff2[i].holiday_pay += (int)((staff2[i].sch2[j].work_day - 8) * staff2[i].pay_hour * 0.5);
				}
				staff2[i].pay_month += (staff2[i].sch2[j].work_day) * staff2[i].pay_hour;
			}
			//월급 계산
			staff2[i].pay_month += staff2[i].long_pay + staff2[i].holiday_pay;

			file << staff2[i].new_name << "님의 연장수당은 " << staff2[i].long_pay << "원입니다." << endl;	//파일에 출력
			file << staff2[i].new_name << "님의 휴일수당은 " << staff2[i].holiday_pay << "원입니다." << endl;	//파일에 출력
			file << staff2[i].new_name << "님의 월급은 " << staff2[i].pay_month << "원입니다." << endl;		//파일에 출력

		}
	}


	file.close();


}


void Staff::print_all() {						// 전체 직원 목록 출력
	for (int i = 0; i < num_staff-1; i++) {
		cout << i + 1 << ". " << staff2[i].new_name;	//직원 이름
		cout << " 시급: " << staff2[i].pay_hour << endl;		//직원 시급
	}
}


void Staff::print_schedule_for_start() {
	for (int i = 0; i < num_staff-1; i++) {
		cout << i + 1 << ". " << staff2[i].new_name << endl;	//직원 이름
		for (int j = 0; j < 30; j++) {
			if (staff2[i].sch2[j].work_year == 0)
				break;
			//직원 스케줄
			cout << "    ("<<j + 1 << ") " << staff2[i].sch2[j].work_year << "년 " << staff2[i].sch2[j].work_month << "월 " << staff2[i].sch2[j].work_day << "일 " << staff2[i].sch2[j].work_start_hour << "시 " << staff2[i].sch2[j].work_start_min << "분" << endl;
			
		}
		
	}

}

void Staff::print_schedule_for_end() {
	for (int i = 0; i < num_staff-1; i++) {
		cout << i + 1 << ". " << staff2[i].new_name << endl;	//직원 이름
		for (int j = 0; j < 30; j++) {
			if (staff2[i].sch2[j].work_year == 0)
				break;
			//직원 스케줄
			cout << j + 1 << ". " << staff2[i].sch2[j].work_year << "년 " << staff2[i].sch2[j].work_month << "월 " << staff2[i].sch2[j].work_day << "일 " << staff2[i].sch2[j].work_end_hour << "시 " << staff2[i].sch2[j].work_end_min << "분" << endl;
		}
	}
}

