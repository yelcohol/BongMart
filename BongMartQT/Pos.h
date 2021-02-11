#pragma once
#include <iostream>
#include <string.h>
#include <string>
#include <vector>
#include <windows.h>
#include <time.h>
#include <popdialog.h>
//#include "Customer.h"
#include "Product.h"
#include "Calendar.h"
#include <nostock.h>
#include<fstream>
#include<iomanip>
#include<Staff.h>

using namespace std;

typedef struct {
    int age;
    bool sex;
    char time[5];
} history_information;

class POS {
private:
    string rep_name;                     //��ǥ�� �̸�
    string store_name;                     //���� �̸�
    string phone_num;                     //��ȭ��ȣ
    string address;                        //���� �ּ�
    int total_money;                  //������ �� �ݾ�
    int total_cash;                       //50000��, 10000��, 5000��, 1000��, 500��, 100��, 50��, 10���� ����
    int card_money;                     //ī�� �Ѿ�
    vector<string> trans;

    //edited by Sangyun
    int flag = 0;                  //���� �ݾ�(2+1��)
    int get_money;                          //���� �ݾ�
    int change;                           //�Ž�����


    //Customer customer;                  // ���� ����
    vector<Product> product;

    vector<int> purchase;
    vector<int> purchase_num;
    vector<int> purchase_disc;

    int sum_purchase = 0;

    Calendar calendar;

    bool powerPos = false;



public:

    POS(string rep_name, string store_name, string phone_num, string address);

    ~POS();
    void set_card_money(int);
    void save_history(history_information _history, int index);
    void search_history(vector<history_information> history, int lage, int rage, bool _sex);
    void print_history(int num);
    void check_history();

    void productRead(const char* filename);
    void productWrite(const char* filename);

    void mainMenu();

    void set_total_money();
    void set_total_cash(int);
    void input_total_cash(int);
    void set_rep_name(string rep_name);
    void set_store_name(string store_name);
    void set_phone_num(string phone_num);
    void set_address(string address);
    void check_cash();      //���� ����
    void modify_cash();
    void add_total_cash(int);                        //���� �߰� �Ա�
    void sub_total_cash(int);                        //���� �߰� ����
    void print_product_list();
    void modify_product();
    void add_stock(int,int,int);
    void sub_stock(int,int);
    void add_product(string, int, int, int, int);
    void sub_product(int);
    void add_transaction(string);                        //�ŷ����� ���� �ؽ�Ʈ ���Ͽ� ����? (�ŷ����� ����, ������ �����Ҷ� ����, �м�)
    void print_transactional_table();              //�ŷ����� ����   �ؽ�Ʈ ���� ����?


    void calcul(int);
    void cardcal();
    void input_buy_product(string);
    vector<int> get_purchase();
    vector<int> get_purchase_num();
    vector<Product> get_product();
    void clear_purchvec();              //purch, purch_num 둘다 clear
    vector<int> get_purchase_disc();
    int get_change();
    int get_total_money();
    int get_total_cash();
    int get_sum_purchase();
    void clear_things();
    void set_flag(int);
    int get_flag();
    void erase_purch(int);
    void inc_purch_num(int);
    void dec_purch_num(int);
    POS get_pos();



    string discount_string(int dis);
    void trash_product_clear();
    void print_receipt();                        //������ ����
                            //void cash_receipt



                                  /////////////�ʿ��ϸ� �߰�






    void calendarON();




    bool checkPowerPos();
};
