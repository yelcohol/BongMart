#pragma once
#include <string>

using namespace std;

class Customer {
private:
	string name;
	bool sex;		//true면 남성, false면 여성
	int age;
	string tel;
	int point;

public:
	Customer(string _name, bool _sex, int _age, string _tel);
	~Customer();

	string get_name();
	string get_sex_s();
	bool get_sex();
	int get_age();
	string get_tel();
	int ger_point();

	void Modify_name(string _name);
	void Modify_sex(bool _sex);
	void Modify_age(int _age);
	void Modify_tel(string _tel);

	bool Check_name(string _name);
	bool Check_tel(string _tel);

	void add_point(int num);
	void sub_point(int num);
	void add_age();

	void print_information();
};
