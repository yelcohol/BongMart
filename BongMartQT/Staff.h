#pragma once

#include "Calendar.h"

using namespace std;
class Staff {
private:

    int num_schedule_temp=0;	// ������ ��
    int num_schedule=0;			// �� ������ �Ҵ��Ǵ� ��¥ ������ ��.
    int num_staff;				// ���� ��
                                // �޸��忡�� �����͸� �о��� ���� void get_schedule(string filename) �޼ҵ带 ����. �����Ǵ� �迭���ڴ� num_schedule_temp.
                                // �Էµ� staff1[num_schedule_temp]
    char* new_name;				// �����̸�
    int pay_hour=8350;				// �ñ�

    typedef struct staff_schedule {
        int work_year;			// ������ ���� "��"
        int work_month;			// ������ ���� "��"
        int work_day;			// ������ ���� "��"
        int work_start_hour;	// ������ ���� "��"
        int work_start_min;		// ������ ���� "��"
        int work_end_hour;		// ������ ���� "��"
        int work_end_min;		// ������ ���� "��"
        double work_time_day;	// �Ϸ� ���� ���� �ð�
        vector<int> cur_work_start_time;	//���� ������ �ð�
        vector<int> cur_work_end_time;		//���� ������ �ð�
    }Staff_schedule;

    Staff_schedule sch;
    Staff_schedule sch2[100];	// staff2 �迭�Ǵ� ������.


    int negligence = 0;		// �ٹ� �¸� Ƚ�� (����, ���� ���� Ƚ��)

    int long_pay=0;						//��������
    int holiday_pay=0;					//���ϼ���
    int pay_month=0;						//����

public:
    Staff();
    // startday - ���� ������(��,��,��) �� �־��ֱ�!
    // ���� ���� �⺻������ ������ ������ �ð� �־��ֱ�! - work_start_time, work_end_time
    ~Staff();
    // ���� �Ҵ��� �޸��� ���� free���ֱ�!

    void clear_staff();
    vector<int> returnTime();					// ���� �ð� ����

    void set_work_start(int staff_num, int schedule_num);							//���� ���� �ð� set
    void set_work_end(int staff_num, int schedule_num);								//���� ���� �ð� set
    void set_negligence();															// �ٹ��¸�Ƚ�� set

    void calculate_work_time();		// �� �� ���� �ð� ����


    void get_schedule(string filename);		// �޸������κ��� �������� �������� �޴´�.
    void sort_schedule();					// �������� �������� �����Ѵ�.


    void add_staff();						// ���� �߰�: ���� �̸� �Է¹���.
    void delete_staff();					// ���� ����

    void edit_working_staff();				// Ư�� ���� ���ϴ� ���� ��ü, ��Ÿ (������ ���� ��ü�� work_day_week�迭 ����)


    void upgrade_pay_hour();				// �ñ� �λ�, startday, negligence �����ؼ�

    void message_negligence();				// ����, �������� �޸������� ����. �̸��� �Բ�



    void pay();								// ��������, ���ϼ��� ����
                                            // ��������
                                            // ���޸���������


    //void paystub();							// ���� ������(���� �ʱ�ȭ �Ǵ°� �����ؼ� ���� ���ؾ��� , ���� �����صδ� ����, �ؽ�Ʈ ���Ϸ� ����)
                                            // (�����ֳ� �������� �Ǿ��ٰ� ���󰡸� �ȵ�, �ؽ�Ʈ���Ϸ� �����صε簡)

    void print_all();						// ��ü ���� ���� ����, �� ������ �����ϸ� �� ������ ���� ������ ��������! (��ü�� print�޼ҵ� ȣ��)
    int get_num_staff();
    Staff get_staff2(int);
    char* get_new_name();
    int get_pay_hour();

    //
};


