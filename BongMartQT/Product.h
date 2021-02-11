#pragma once
#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>
using namespace std;

class Product {
private:
    string name;                       //��ǰ �̸�
    int price;                       //��ǰ ����
    vector <int>stock;                 //��ǰ ������
    vector <int>valid_date;              //��ǰ ��������
    //int code;                       //��ǰ �ڵ�
    int discount;                    //���� ��ǰ����
    int sell;                       //�󸶳� �ȷȴ���
    //int category;                    //ī�װ���   0:���ڷ� 1:����ǰ 2:���� 3:�н�ƮǪ�� �ʿ��� �߰�
    //int count = 0;                    //�������� �� ������ �󸶳� �ִ���
    //int valid_date;                 //��������
    //int loacation                    //��ġ
public:

    //Constructor
    Product();                       //������

    //Destructor
    ~Product();
    //Setter
    void setname(string);
    void setprice(int);                   //���� ����
    void setstock(int);
    void setvalid_date(int);
    void setdiscount(int);
    void setsell(int);
    //void setcategory(int category);

    //Getter
    string getname();
    int getprice();
    vector<int> getstock();
    vector<int> getvalid_date();
    int getdiscount();
    int getsell();
    //int getcategory();

    //Functions
    void setProduct(string name, int price, vector<int> valid_date, vector<int> stock,  int discount, int sell); // ��ǰ �߰�
    void addstock(int , int);                   //���� �߰�
    int get_allstock();
    void substock(int);                   //���� ����
    void addsell(int);
    void product_discsard(int);           //��ǰ ����
    void set_discount(int);               //��ǰ ���� �߰�
                                 /////////////�ʿ��ϸ� �߰�  �����������������基������������
    /////////////�ʿ��ϸ� �߰�
};
#endif
