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
	string name;                       //제품 이름
	int price;                       //제품 가격
	vector <int>stock;                 //제품 재고량
	vector <int>valid_date;              //제품 유통기한
	//int code;                       //제품 코드
	int discount;                    //행사 상품여부
	int sell;                       //얼마나 팔렸는지
	//int category;                    //카테고리   0:과자류 1:유제품 2:음료 3:패스트푸드 필요시 추가
	//int count = 0;                    //유통기한 별 재고가 얼마나 있는지 
	//int valid_date;                 //유통기한
	//int loacation                    //위치
public:

	//Constructor
	Product();                       //생성자 

	//Destructor
	~Product();
	//Setter
	void setname(string);
	void setprice(int);                   //가격 설정
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
	void setProduct(string name, int price, vector<int> valid_date, vector<int> stock,  int discount, int sell); // 물품 추가 
	void addstock(int , int);                   //재고 추가
	int get_allstock();
	int substock(int);                   //재고 감소
	void addsell(int);
	void product_discsard(int);           //물품 폐기
	void set_discount(int);               //물품 행사 추가
								 /////////////필요하면 추가  등등등등등등등등드읃으드으드드으
	/////////////필요하면 추가
};
#endif
