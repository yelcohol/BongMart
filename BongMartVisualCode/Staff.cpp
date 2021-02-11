#include "Staff.h"
#include "Calendar.h"
#include <string.h>
using namespace std;


Staff::Staff() {
}

Staff::~Staff() {
	//�����Ҵ��� �޸𸮵� free���ֱ�
}

Staff staff1[100];	//get_schedule���� �ʿ��� ��ü.
Staff staff2[30];	//sort_schedule���� �ʿ��� ��ü.
					//�ִ� ���� ��: 30
					//��¥ �߿��� ��ü�� staff2 ��ü�̴�.

//���� �ð� ����

//ȭ�� ���
void Staff::result() {
	int input;
	if (checker) {
		get_schedule();
		sort_schedule();
		checker = false;
	}
	cout << "-����Ű 1 -  ��� üũ" << endl;
	cout << "-����Ű 2 -  ��� üũ" << endl;
	cout << "-����Ű 3 -  ���� ���� ����" << endl;
	cout << "-����Ű 4 -  ���� �߰�" << endl;
	cout << "-����Ű 5 -  ���� ����" << endl;
	cout << "���ڸ� �Է��ϼ���: ";
	cin >> input;
	int staff_num, schedule_num;
	switch (input) {
	case 1:
		print_schedule_for_start();
		cout << "���� ��ȣ �Է�: ";
		cin >> staff_num;
		cout << "���� ������ ��ȣ �Է�: ";
		cin >> schedule_num;
		set_work_start(staff_num-1, schedule_num-1);
		cout << staff2[staff_num-1].new_name <<"��, ��� ó���Ǿ����ϴ�."<< endl;
		Sleep(3000);
		break;

	case 2:
		print_schedule_for_end();
		cout << "���� ��ȣ �Է�: ";
		cin >> staff_num;
		cout << "���� ������ ��ȣ �Է�: ";
		cin >> schedule_num;
		set_work_end(staff_num-1, schedule_num-1);
		cout << staff2[staff_num-1].new_name << "��, ��� ó���Ǿ����ϴ�." << endl;
		Sleep(3000);
		break;

	case3:
		cout << "�ſ� 1���� �Ǹ� staff_pay ���Ϸ� ��������ϴ�. �ſ� 1�Ͽ� Ȯ�����ּ���" << endl;
		if (calendar.returnTime().at(2) == 1) {				//�� ���� ������(�ſ� 1���� �Ǹ�)

			cout << "�� ���� �������ϴ�. ������ ����ϰڽ��ϴ�.\n" << endl;
			calculate_work_time();				//���� �ð� ���.
			set_negligence();
			message_negligence();			//�ٹ��¸�Ƚ���� ����Ѵ�.
			pay();								//�������.
			upgrade_pay_hour();					//�ñ��λ��� ����Ѵ�.

			clear_staff();						//������ ���� �ʱ�ȭ.
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

	if (calendar.returnTime().at(2) == 1) {				//�� ���� ������(�ſ� 1���� �Ǹ�)

		cout << "�� ���� �������ϴ�. ������ ����ϰڽ��ϴ�.\n" << endl;
		calculate_work_time();				//���� �ð� ���.
		set_negligence();
		message_negligence();		//�ٹ��¸�Ƚ���� ����Ѵ�.
		pay();								//�������.
		upgrade_pay_hour();					//�ñ��λ��� ����Ѵ�.

		clear_staff();						//������ ���� �ʱ�ȭ.
	}

}

// ������ ���� �ʱ�ȭ
void Staff::clear_staff() {
	for (int i = 0; i < num_staff; i++) {
		this->pay_month, holiday_pay, long_pay = 0;

		this->negligence = 0;
	}

}



//��� �ð� set
void Staff::set_work_start(int staff_num, int schedule_num) {
	staff2[staff_num].sch2[schedule_num].cur_work_start = calendar.returnTime();
}

//��ٽð� set
void Staff::set_work_end(int staff_num, int schedule_num) {
	staff2[staff_num].sch2[schedule_num].cur_work_end = calendar.returnTime();
}

//�ٹ� �¸� Ƚ�� set
void Staff::set_negligence() {
	for (int i = 0; num_staff; i++)
		for (int j = 0; j < 30; j++) {
			//�������
			if ((staff2[i].sch2[j].work_end_hour - staff2[i].sch2[j].cur_work_end.at(4) > 0) || ((staff2[i].sch2[j].work_end_hour - staff2[i].sch2[j].cur_work_end.at(4) == 0) && (staff2[i].sch2[j].work_end_min - staff2[i].sch2[j].cur_work_end.at(5)) > 0))
				staff2[i].negligence++;
			//����
			if ((staff2[i].sch2[j].cur_work_start.at(4) - staff2[i].sch2[j].work_start_hour > 0) || ((staff2[i].sch2[j].cur_work_start.at(4) - staff2[i].sch2[j].work_start_hour == 0) && (staff2[i].sch2[j].cur_work_start.at(5) - staff2[i].sch2[j].work_start_min) > 0))
				staff2[i].negligence++;
		}
}


// �� �� ���� �ð� ���
void Staff::calculate_work_time() {	//�ش罺������ȣ, �ش罺�����ǽ����ٹ�ȣ
	for (int staff_num = 0; staff_num < num_staff; staff_num++) {
		for (int schedule_num = 0; schedule_num < 30; schedule_num++) {
			//������ �ش� �����ٿ� ���� �ð� ���
			staff2[staff_num].sch2[schedule_num].work_time_day = ((staff2[staff_num].sch2[schedule_num].work_end_hour - staff2[staff_num].sch2[schedule_num].work_start_hour) * 60 + staff2[staff_num].sch2[schedule_num].work_end_min - staff2[staff_num].sch2[schedule_num].work_start_min) / 60.0;

			if (staff2[staff_num].sch2[schedule_num].work_time_day >= 8)	//8�ð� �̻� ���ϸ�
				staff2[staff_num].sch2[schedule_num].work_time_day = -1;	//1�ð��� �޽Ľð�

			else if (staff2[staff_num].sch2[schedule_num].work_time_day >= 4)	//4�ð� �̻� 8�ð� �̸� ���ϸ�
				staff2[staff_num].sch2[schedule_num].work_time_day = -0.5;	//30���� �޽Ľð�
		}
	}
}

//staff_schedule �ؽ�Ʈ���Ϸκ��� ������������ �ޱ�.
void Staff::get_schedule() {

	ifstream readFile;
	readFile.open("staff_schedule.txt");		//staff ���   
	         
	//staff2�� ���� ����.
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

//staff �̸��� �ް�, ������ ����
void Staff::sort_schedule() {
	ifstream readFile;
	readFile.open("staff_list.txt");		//staff ���

	//staff2�� ���� ����.
	if (readFile.is_open()) {
		while (!readFile.eof()) {
			char tmp[256];
			readFile.getline(tmp, 256);
			strcpy(staff2[num_staff].new_name,tmp);
			this->num_staff++;
		}
	}

	readFile.close();

	//staff2�� ������ ����
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


//���� �߰�
void Staff::add_staff() {
	char add_staff_name[20];
	cout << "���ο� ������ �̸��� �Է��ϼ��� : ";
	cin >> add_staff_name;

	ofstream writeFile("staff_list.txt", ios::app);		//staff ���
	writeFile << add_staff_name << endl;			//txt ���Ͽ� ���� �̸� �߰�
	strcpy(staff2[num_staff].new_name,add_staff_name);		//staff2 �迭�� �����̸� �߰�
	num_staff++;										//staff_name ����

	writeFile.close();

}

//���� ����
void Staff::delete_staff() {
	int delete_num;
	print_all();		//������� ��ü ������.

	cout << "������ ���� ��ȣ�� �Է��ϼ��� : ";
	cin >> delete_num;
	this->num_staff--;

	// ����
	// 1. ���¿� 2. �̻��� 3. �̱��� 4. ���¿�
	// 2���� ����. 2���� ������ staff2[1]�̴�. ����, delete_num-1�� ���� �����ؾ� �Ѵ�.
	// num_staff�� 3�̴�. ���� 4���� staff[3] ����Ǿ� ����.
	// staff2[1]=staff[2]//���¿� �̱��� �̱��� ���¿�
	// staff2[2]=staff[3]//���¿� �̱��� ���¿� ���¿�
	for (int i = delete_num; i < num_staff; i++) {
		staff2[i - 1] = staff2[i];
	}
}

// Ư�� ���� ���ϴ� ���� ��ü, ��Ÿ (������ ���� ��ü�� work_day_week�迭 ����)
void Staff::edit_working_staff() {

}

// negligence�� �Ѵ޵��� ������ 200�� �λ�.
void Staff::upgrade_pay_hour() {
	for (int i = 0; i < num_staff; i++)
		if (staff2[i].negligence == 0)			//negligence Ƚ���� ���ٸ�
			staff2[i].pay_hour += 200;		//�ñ� 200�� �λ�
}



void Staff::message_negligence() {
	ofstream File("staff_negligence.txt", ios::out);		//staff negligence ���.
	set_negligence();
	for (int i = 0; i < num_staff; i++) {
		File << staff2[i].new_name << " �ٹ� �¸� Ƚ��: " << staff2[i].negligence << endl;			//txt ���Ͽ� ���� �̸��� �ٹ��¸�Ƚ�� ���.	
	}
	File.close();
}


// ���� (�ϳ� ������!)
//���޼��� (�޽Ľð� �����ϴ°͵� ����ؼ�! , �� �ָ��� �� �� ���� ���� �ð� �ʱ�ȭ �ǹǷ� �޿��� �� �� ����ؼ� �׾ư� �ʿ� ����)
//, �߰�����, �߰�����(����, �߼� ��) ���
//�޽Ľð� - 4�ð��̻��̸� 30�� 0.5�ð� , 8�ð� �̻��̸� 1�ð� - ������� 8�ð��ٹ��� 1�ð� �޽��ϹǷ� 7�ð� ���Ѱ����� ���!
//�� Ŭ���� ����, �ű⼭ ���� �پ��
//����, �ܾ��� ���ڶ� ���, �˸��� �ְ� �̷�, 2�־ȿ� ����� - ���ϳ��Ҵٰ� �˷��ְ�
void Staff::pay() {
	ofstream file;
	file.open("staff_pay.txt", ios::app);		//staff pay ���

	for (int i = 0; i < num_staff; i++) {

		if (num_staff > 5) {					// ������ 5�� �̻��̸� �������, ���ϼ���
			for (int j = 0; j < 20; j++) {

				//�Ϸ翡 ���� �ð��� 8�ð� �ʰ��� �������
				//��������� �⺻ �ñ��� 0.5��
				if (staff2[i].sch2[j].work_day > 8) {
					staff2[i].long_pay += (int)((staff2[i].sch2[j].work_day - 8) * staff2[i].pay_hour * 0.5);
				}

				//���ϼ����� ���Ͽ� 8�ð� ���Ϸ� �ٹ��ϸ� �⺻ �ñ��� 0.5��
				//���ϼ����� ���Ͽ� 8�ð� �ʰ��Ͽ� �ٹ��ϸ� �⺻ �ñ��� 1��
				if (staff2[i].sch2[j].cur_work_start.at(3) == 0) {		//���Ͽ� ���Ͽ��ٸ�
					if (staff2[i].sch2[j].work_time_day > 8)
						staff2[i].holiday_pay += (int)((staff2[i].sch2[j].work_day - 8) * staff2[i].pay_hour * 1.0);
					else
						staff2[i].holiday_pay += (int)((staff2[i].sch2[j].work_day - 8) * staff2[i].pay_hour * 0.5);
				}
				staff2[i].pay_month += (staff2[i].sch2[j].work_day) * staff2[i].pay_hour;
			}
			//���� ���
			staff2[i].pay_month += staff2[i].long_pay + staff2[i].holiday_pay;

			file << staff2[i].new_name << "���� ��������� " << staff2[i].long_pay << "���Դϴ�." << endl;	//���Ͽ� ���
			file << staff2[i].new_name << "���� ���ϼ����� " << staff2[i].holiday_pay << "���Դϴ�." << endl;	//���Ͽ� ���
			file << staff2[i].new_name << "���� ������ " << staff2[i].pay_month << "���Դϴ�." << endl;		//���Ͽ� ���

		}
	}


	file.close();


}


void Staff::print_all() {						// ��ü ���� ��� ���
	for (int i = 0; i < num_staff-1; i++) {
		cout << i + 1 << ". " << staff2[i].new_name;	//���� �̸�
		cout << " �ñ�: " << staff2[i].pay_hour << endl;		//���� �ñ�
	}
}


void Staff::print_schedule_for_start() {
	for (int i = 0; i < num_staff-1; i++) {
		cout << i + 1 << ". " << staff2[i].new_name << endl;	//���� �̸�
		for (int j = 0; j < 30; j++) {
			if (staff2[i].sch2[j].work_year == 0)
				break;
			//���� ������
			cout << "    ("<<j + 1 << ") " << staff2[i].sch2[j].work_year << "�� " << staff2[i].sch2[j].work_month << "�� " << staff2[i].sch2[j].work_day << "�� " << staff2[i].sch2[j].work_start_hour << "�� " << staff2[i].sch2[j].work_start_min << "��" << endl;
			
		}
		
	}

}

void Staff::print_schedule_for_end() {
	for (int i = 0; i < num_staff-1; i++) {
		cout << i + 1 << ". " << staff2[i].new_name << endl;	//���� �̸�
		for (int j = 0; j < 30; j++) {
			if (staff2[i].sch2[j].work_year == 0)
				break;
			//���� ������
			cout << j + 1 << ". " << staff2[i].sch2[j].work_year << "�� " << staff2[i].sch2[j].work_month << "�� " << staff2[i].sch2[j].work_day << "�� " << staff2[i].sch2[j].work_end_hour << "�� " << staff2[i].sch2[j].work_end_min << "��" << endl;
		}
	}
}

