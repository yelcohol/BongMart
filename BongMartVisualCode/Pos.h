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
//고객 분석
typedef struct {
	int age;
	bool sex;
	char time[5];
} history_information;
//고객 분석
class POS {
private:

	

	string rep_name;                     //대표자 이름
	string store_name;                     //가게 이름
	string phone_num;                     //전화번호
	string address;                        //가게 주소
	int total_money = 0;                  //포스기 총 금액
	int cash[8] = { 0, };                       //50000원, 10000원, 5000원, 1000원, 500원, 100원, 50원, 10원권 개수
	int card_money = 0;                     //카드 총액

	//edited by Sangyun
	int discount_money = 0;                  //할인 금액(2+1등)
	int get_money;                          //받은 금액
	int change;                           //거스름돈



	//Customer customer;                  // 고객 정보
	vector<Product> product;

	vector<int> purchase;
	vector<int> purchase_num;
	int sum_purchase = 0;


	Staff staff;
	//Staff staff;

	Transaction transaction;//////////태운

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
	void check_cash();      //시재 점검
	void modify_cash();
	void add_total_cash();                        //현금 중간 입금
	void sub_total_cash();                        //현금 중간 출금
	void reset_sell();
	void print_product_list();
	void modify_product();
	void add_stock();
	void sub_stock();
	void add_product();
	void sub_product();
	void add_transaction();                        //거래내역 저장 텍스트 파일에 저장? (거래내역 출력, 영수증 출력할때 사용, 분석)
	//void print_transactional_table();              //거래내역 출력   텍스트 파일 출력?
	//void transactionRead(string filename);
	void input_buy_product();
	void calculate_cash_buy(int q);
	void modify_discount();
	string discount_string(int dis);
	void trash_product_clear();
	//void transactionWrite();
	//void print_receipt();                        //영수증 출력
	//void receiptRead(string filename);
							//void cash_receipt
								  /////////////필요하면 추가






	void calendarON();




	bool checkPowerPos();
};