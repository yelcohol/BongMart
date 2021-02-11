#include "Customer.h"
#include <iostream>

#define PRINT_POINT_ERROR cout << "포인트가 부족합니다.";

//Constructor
Customer::Customer(string _name, bool _sex, int _age, string _tel) {
	this->name = _name;
	this->sex = _sex;
	this->age = _age;
	this->tel = _tel;
	this->point = 0;
}

//Destructor
Customer::~Customer() {
	//동적 할당 해제
}

string Customer::get_name() {
	return this->name;
}
string Customer::get_sex_s() {
	if (this->sex) return "Male";
	else return "Female";
}
bool Customer::get_sex() {
	return this->sex;
}
int Customer::get_age() {
	return this->age;
}
string Customer::get_tel() {
	return this->tel;
}
int Customer::ger_point() {
	return this->point;
}

void Customer::Modify_name(string _name) {
	this->name = _name;
}
void Customer::Modify_sex(bool _sex) {
	this->sex = _sex;
}
void Customer::Modify_age(int _age) {
	this->age = _age;
}
void Customer::Modify_tel(string _tel) {
	this->tel = _tel;
}

bool Customer::Check_name(string _name) {
	if (name == _name) return true;
	else return false;
}
bool Customer::Check_tel(string _tel) {
	int count = 0;
	for (int index = 0; index < 4; index++)
		if (tel[index] == _tel[index]) count++;
	if (count == 4) return true;
	else return false;
}

void Customer::add_point(int num) {
	this->point += num;
}
void Customer::sub_point(int num) {
	if (this->point < num) PRINT_POINT_ERROR
	else this->point -= num;
}
void Customer::add_age() {
	this->age++;
}

void Customer::print_information() {
	//나중에 구현
}