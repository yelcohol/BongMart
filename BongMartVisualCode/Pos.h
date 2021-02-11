#pragma once
#include <iostream>
#include <string.h>
#include <string>
#include <vector>
#include <Windows.h>
#include <time.h>
#include <iomanip>
#include <fstream>

#include "Staff.h"
#include "Product.h"
#include "Calendar.h"
#include "Transaction.h"
#include "Customer.h"

using namespace std;
//�� �м�
typedef struct {
	int age;
	bool sex;
	char time[5];
} history_information;
//�� �м�
class POS {
private:

	

	string rep_name;                     //��ǥ�� �̸�
	string store_name;                     //���� �̸�
	string phone_num;                     //��ȭ��ȣ
	string address;                        //���� �ּ�
	int total_money = 0;                  //������ �� �ݾ�
	int cash[8] = { 0, };                       //50000��, 10000��, 5000��, 1000��, 500��, 100��, 50��, 10���� ����
	int card_money = 0;                     //ī�� �Ѿ�

	//edited by Sangyun
	int discount_money = 0;                  //���� �ݾ�(2+1��)
	int get_money;                          //���� �ݾ�
	int change;                           //�Ž�����



	//Customer customer;                  // �� ����
	vector<Product> product;

	vector<int> purchase;
	vector<int> purchase_num;
	int sum_purchase = 0;


	Staff staff;
	//Staff staff;

	Transaction transaction;//////////�¿�

	Calendar calendar;

	bool powerPos = false;

public:
	POS(string rep_name, string store_name, string phone_num, string address);

	~POS();

	int get_index();

	void save_history(history_information _history, int index);
	void search_history(vector<history_information> history, int lage, int rage, bool _sex);
	void print_history(int num);
	void check_history();

	void new_customer();
	void search_tel(vector<Customer> customers, vector<Customer> good_customers, string _tel);
	vector <Customer> make_customers(vector <Customer> customers);

	void productRead(const char* filename);
	void productWrite(const char* filename);

	void mainMenu();

	void set_total_money();
	void set_total_cash(int* set_cash);
	void input_total_cash();
	void set_rep_name(string rep_name);
	void set_store_name(string store_name);
	void set_phone_num(string phone_num);
	void set_address(string address);
	void check_cash();      //���� ����
	void modify_cash();
	void add_total_cash();                        //���� �߰� �Ա�
	void sub_total_cash();                        //���� �߰� ���
	void reset_sell();
	void print_product_list();
	void modify_product();
	void add_stock();
	void sub_stock();
	void add_product();
	void sub_product();
	void add_transaction();                        //�ŷ����� ���� �ؽ�Ʈ ���Ͽ� ����? (�ŷ����� ���, ������ ����Ҷ� ���, �м�)
	//void print_transactional_table();              //�ŷ����� ���   �ؽ�Ʈ ���� ���?
	//void transactionRead(string filename);
	void input_buy_product();
	void calculate_cash_buy(int q);
	void modify_discount();
	string discount_string(int dis);
	void trash_product_clear();
	//void transactionWrite();
	//void print_receipt();                        //������ ���
	//void receiptRead(string filename);
							//void cash_receipt
								  /////////////�ʿ��ϸ� �߰�






	void calendarON();




	bool checkPowerPos();
};